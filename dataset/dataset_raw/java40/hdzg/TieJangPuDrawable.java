package wyf.ytl.entity;
/*
 * 提高武力
 */
import static wyf.ytl.tool.ConstantUtil.*;

import java.io.Serializable;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.view.MotionEvent;
import android.view.View;

public class TieJangPuDrawable extends MyMeetableDrawable implements Serializable{
    String [] dialogMessage={//对话框显示文字
            "前方是一个铁匠铺，是否让将军们在此修理自己的武器装备？预计消耗金钱1500。",
            "大军来到一个铁匠铺，不过你的金钱太少了，铁匠没有理睬你。",
            "xx将军在铁匠铺打造了一套新铠甲，防御提高了yy点。",
            "xx将军在铁匠铺忙了大半天，什么也没捞着。"
        };
    int cost = 1500;//花费
    int status=-1;//状态位，为0表示显示是否进去，为1表示显示不能进去,为2表示显示培训结果，3
    int powerIncrement = 3;//每次最多增加3点
    
    public TieJangPuDrawable(){}
    
    public TieJangPuDrawable(Bitmap bmpSelf,Bitmap bmpDialogBack,Bitmap bmpDialogButton,boolean meetable,int width,int height,int col,int row,
            int refCol,int refRow,int [][] noThrough,
            int [][] meetableMatrix) {
        super(bmpSelf, col, row, width, height, refCol, refRow, noThrough, meetable,
                meetableMatrix, bmpDialogBack, bmpDialogButton);
    }

    @Override
    public void drawDialog(Canvas canvas, Hero hero) {
        String showString = null;//需要显示到对话框中的字符串
        tempHero = hero;
        //先画背景
        canvas.drawBitmap(bmpDialogBack, 0, DIALOG_START_Y, null);
        //设置初始状态位
        if(status == -1){
            if(tempHero.getTotalMoney() < cost){//金钱不够了
                status = 1;
            }
            else{//如果金钱还够
                status = 0;
            }           
        }
        showString = dialogMessage[status];//确定要显示的字符串
        drawString(canvas, showString);
        //画按钮确定按钮
        canvas.drawBitmap(bmpDialogButton, DIALOG_BTN_START_X, DIALOG_BTN_START_Y, null);       
        Paint paint = new Paint();
        paint.setARGB(255, 42, 48, 103);
        paint.setAntiAlias(true);
        paint.setTypeface(Typeface.create((Typeface)null,Typeface.ITALIC));
        paint.setTextSize(18);
        canvas.drawText("确定",
                DIALOG_BTN_START_X+DIALOG_BTN_WORD_LEFT,
                DIALOG_BTN_START_Y+DIALOG_WORD_SIZE+DIALOG_BTN_WORD_UP,
                paint
                );
        //画取消按钮
        if(status == 0){//查看是否需要画第二个取消按钮
            canvas.drawBitmap(bmpDialogButton, DIALOG_BTN_START_X+DIALOG_BTN_SPAN, DIALOG_BTN_START_Y, null);
            canvas.drawText("取消", 
                    DIALOG_BTN_START_X+DIALOG_BTN_SPAN+DIALOG_BTN_WORD_LEFT, 
                    DIALOG_BTN_START_Y+DIALOG_WORD_SIZE+DIALOG_BTN_WORD_UP,
                    paint
                    );
        }       
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        int x = (int)event.getX();
        int y = (int)event.getY();
        if(event.getAction() == MotionEvent.ACTION_DOWN){
            if(x>DIALOG_BTN_START_X && x<DIALOG_BTN_START_X+DIALOG_BTN_WIDTH
                    && y>DIALOG_BTN_START_Y && y<DIALOG_BTN_START_Y+DIALOG_BTN_HEIGHT){//点下的是确定键
                switch(status){
                case 0://有钱进时玩家确认进
                    tempHero.setTotalMoney(tempHero.getTotalMoney() - cost);//交钱
                    upgradeGeneralPower();//随机挑选一个将军升级武力
                    break;
                case 1://无钱进时玩家确认放弃
                case 2://已经进要出来
                case 3://学习失败
                    recoverGame();
                    break;
                }               
            }
            else if(x>DIALOG_BTN_START_X+DIALOG_BTN_SPAN && x<DIALOG_BTN_START_X+DIALOG_BTN_SPAN+DIALOG_BTN_WIDTH
                    && y>DIALOG_BTN_START_Y && y<DIALOG_BTN_START_Y+DIALOG_BTN_HEIGHT){//点下的是取消键
                recoverGame();
            }           
        }
        return true;
    }
    //方法：返还监听器，回复游戏状态
    public void recoverGame(){
        tempHero.father.setOnTouchListener(tempHero.father);//返还监听器
        tempHero.father.setCurrentDrawable(null);//置空记录引用的变量
        tempHero.father.setStatus(0);//重新设置GameView为待命状态
        tempHero.father.gvt.setChanging(true);//骰子转起来
        status = -1;//状态复位
    }
    //方法：随机增加将军的武力
    public void upgradeGeneralPower(){
        int size = tempHero.generalList.size();
        int r = (int)(Math.random()*100)%size;//随机算出哪位将军属性提高
        General g = tempHero.generalList.get(r);        
        int increment = (int)(Math.random()*(powerIncrement+1));//随机获取增量
        if(increment == 0){//如果什么都没学会
            status = 3;
            dialogMessage[3] = dialogMessage[3].replaceFirst("xx", g.getName());//替换对话框的文字
        }
        else{//如果学有所成
            status = 2;
            g.setDefend(g.getDefend()+increment);//增加英雄属性
            dialogMessage[2] = dialogMessage[2].replaceFirst("xx", g.getName());//替换对话框的文字
            dialogMessage[2] = dialogMessage[2].replaceFirst("yy", increment+"");//替换对话框的文字         
        }
    }
}
