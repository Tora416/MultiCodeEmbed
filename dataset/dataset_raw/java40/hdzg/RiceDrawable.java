package wyf.ytl.entity;

import static wyf.ytl.tool.ConstantUtil.DIALOG_BTN_HEIGHT;
import static wyf.ytl.tool.ConstantUtil.DIALOG_BTN_SPAN;
import static wyf.ytl.tool.ConstantUtil.DIALOG_BTN_START_X;
import static wyf.ytl.tool.ConstantUtil.DIALOG_BTN_START_Y;
import static wyf.ytl.tool.ConstantUtil.DIALOG_BTN_WIDTH;
import static wyf.ytl.tool.ConstantUtil.DIALOG_BTN_WORD_LEFT;
import static wyf.ytl.tool.ConstantUtil.DIALOG_BTN_WORD_UP;
import static wyf.ytl.tool.ConstantUtil.DIALOG_START_Y;
import static wyf.ytl.tool.ConstantUtil.DIALOG_WORD_SIZE;
import static wyf.ytl.tool.ConstantUtil.FARMING;

import java.io.Serializable;


import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.view.MotionEvent;
import android.view.View;

public class RiceDrawable extends MyMeetableDrawable implements Serializable{
    String dialogMessage[] = {//对话框的提示信息，第一个是可以狩猎，第二个是不可以狩猎显示的
            "此处稻香扑鼻，一片丰收的气象。是否收水稻？预计消耗体力xx，收获yy石粮食。",
            "此处是个好稻田，怎奈人困马乏，体力不足，只好改日再来！"
        };
        int result;//记录英雄可以获得的收益
        Hero tempHero;//临时记录英雄
        int status;//状态，0：显示是否伐木的选择对话框，1：显示不能伐木的提示对话框
    
        
    public RiceDrawable(){}
        
    public RiceDrawable(Bitmap bmpSelf,Bitmap bmpDialogBack,Bitmap bmpDialogButton,boolean meetable,int width,int height,int col,int row,
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
        Skill skill = hero.heroSkill.get(FARMING);//获得英雄的伐木技能
        result = skill.calculateResult();
        if(result == -1){//体力值不够了
            status = 1;
            showString = dialogMessage[status];
        }
        else{//如果体力值够
            status = 0;
            showString = dialogMessage[status];
            showString = showString.replaceAll("xx", skill.strengthCost+"");//替换消耗体力的字符串
            showString = showString.replaceFirst("yy", result+"");//替换掉预计收获金钱数的字符串
        }
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
                case 0://有稻子可收时玩家确认伐木
                    tempHero.heroSkill.get(FARMING).useSkill(result);
                    break;
                case 1://无稻子可收时玩家确认放弃
                    break;
                }
                recoverGame();
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
    }
}
