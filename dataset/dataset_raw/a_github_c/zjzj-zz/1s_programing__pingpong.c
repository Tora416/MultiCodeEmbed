#include <drawlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

void reflect (float *vx, float *vy, int y, int bary, int barh) {
  float hity = fabs((float)(y - bary) / (barh / 2));
  float weight = 0.75 * hity + 0.75;
  
  *vx *= -1.0 * weight;
  *vy *= weight;
}

int main(void) {
  float wait_time = 0.01;

  int barw = 20, barh = 150;
  int bardy = 50;
  int bardx = 200;
  int bar1ix = 70, bar2ix = DL_WIDTH - 70;
  int bar1x = bar1ix, bar1y = DL_HEIGHT / 2;
  int bar1kup = 'w', bar1kdown = 's', bar1ka = 'e';
  int bar2x = bar2ix, bar2y = DL_HEIGHT / 2;
  int bar2kup = 'i', bar2kdown = 'k', bar2ka = 'u';

  int br = 15;
  float bvx = 4.0, bvy = 2.0;
  int bx = DL_WIDTH / 2, by = DL_HEIGHT / 2;

  int score1 = 0, score2 = 0;
  int score1changed = 0;
  int score2changed = 0;
  int sx = DL_WIDTH / 2 - 120, sy = 50;
  char sscore[] = "   :   ";

  int t, k, x, y;
  
  dl_initialize(1.0);
  
  while (1) {
    while (dl_get_event(&t, &k, &x, &y)) {
      if (t == DL_EVENT_KEY) {
        if (k == bar1kup)
          bar1y -= bardy;
        else if (k == bar1kdown)
          bar1y += bardy;
        else if (k == bar1ka) {
          if (bar1x > bar1ix) 
            bar1x = bar1ix;
          else
            bar1x += bardx;
        } else if (k == bar2kup)
          bar2y -= bardy;
        else if (k == bar2kdown)
          bar2y += bardy;
        else if (k == bar2ka) {
          if (bar2x < bar2ix) 
            bar2x = bar2ix;
          else
            bar2x -= bardx;
        }
      }
    }
    if (bar1y - barh / 2 < 0)
      bar1y = barh / 2;
    if (bar1y + barh / 2 > DL_HEIGHT)
      bar1y = DL_HEIGHT - barh / 2;
    if (bar2y - barh / 2 < 0)
      bar2y = barh / 2;
    if (bar2y + barh / 2 > DL_HEIGHT)
      bar2y = DL_HEIGHT - barh / 2;

    bx += bvx;
    if (bx - br <= 0 || bx + br >= DL_WIDTH) 
      bvx *= -1;
      by += bvy;
    if (by - br <= 0) {
      by = br + 1;
      bvy *= -1;
    } else if (by + br >= DL_HEIGHT) {
      by = DL_HEIGHT - br - 1;
      bvy *= -1;
    }

    if (by > bar1y - barh / 2 && by < bar1y + barh / 2) {
      if (bvx < 0 && bx - br <= bar1x + barw / 2 && bx - br >= bar1x - barw / 2
            || bvx > 0 && bx + br >= bar1x - barw / 2 && bx + br <= bar1x + barw / 2) {
        reflect (&bvx, &bvy, by, bar1y, barh);
      }
    }
    if (by > bar2y - barh / 2 && by < bar2y + barh / 2) {
      if (bvx < 0 && bx - br <= bar2x + barw / 2 && bx - br >= bar2x - barw / 2
        || bvx > 0 && bx + br >= bar2x - barw / 2 && bx + br <= bar2x + barw / 2) {
        reflect (&bvx, &bvy, by, bar2y, barh);
      }
    }

        score1changed = 0;
        score2changed = 0;

    if (bx - br <= 0) {
      score2++;
      bx = bar1x + barw + 1;
      by = bar1y;
      bvx = 4.0;
      bvy = 2.0;
      score2changed = 1;
    }
    if (bx + br >= DL_WIDTH) {
      score1++;
      bx = bar2x - barw - 1;
      by = bar2y;
      bvx = -4.0;
      bvy = 2.0;
      score1changed = 1;
    }
    if(score1 > 999)
      score1 = 999;
    if(score2 > 999)
      score2 = 999;
      
    
    if (score1changed) {
dl_text("+1POINT",100,50,1.0,DL_C("red"),2);
sleep(1);
if (score1>=7){
 dl_text(sscore,sx,sy,2.0,DL_C("white"),2);
 dl_text("RED WINNER!",0,300,2.5,DL_C("red"),2);
 dl_resume();
 sleep(3);
 exit(0);
}
            
    }
    if (score2changed) {
dl_text("+1POINT",450,50,1.0,DL_C("green"),2);
sleep(1);
if (score2>=7){
 dl_text(sscore,sx,sy,2.0,DL_C("white"),2);
 dl_text("GREEN WINNER!",0,300,2.0,DL_C("green"),2);
 dl_resume();
 sleep(3);
 exit(0);
}
            
        }  
          
    dl_stop();
    dl_clear(DL_C("black"));
    dl_rectangle(bar1x - barw / 2, bar1y - barh / 2,
         bar1x + barw / 2, bar1y + barh / 2, DL_C("red"), 1, 1);
    dl_rectangle(bar2x - barw / 2, bar2y - barh / 2,
         bar2x + barw / 2, bar2y + barh / 2, DL_C("green"), 1, 1);
    dl_circle(bx, by, br, DL_C("blue"), 1, 1);
    sprintf(sscore, "%3d:%d", score1, score2);
    dl_text(sscore, sx, sy, 2.0, DL_C("white"), 2);
    dl_resume();

    dl_wait(wait_time);
  }

  return 0;
}
