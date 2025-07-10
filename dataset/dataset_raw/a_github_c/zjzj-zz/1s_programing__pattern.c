#include <drawlib.h>
#include <math.h>

void dl_hexagon(int x, int y ,int z){

dl_line(15+x , 8+y , 25+x , 8+y ,DL_RGB(100-z,125,20+z),3);
dl_line(25+x , 8+y , 35+x , 16+y ,DL_RGB(100-z,125,20+z),3);
dl_line(35+x , 16+y , 25+x , 25+y ,DL_RGB(100-z,125,20+z),3);
dl_line(25+x , 25+y , 15+x, 25+y ,DL_RGB(100-z,125,20+z),3);
dl_line(15+x , 25+y , 5+x , 16+y ,DL_RGB(100-z,125,20+z),3);
dl_line(5+x , 16+y , 15+x , 8+y ,DL_RGB(100-z,125,20+z),3);

}

int main(void) {
    int i , q;

    dl_initialize(1.0);
  
    for (i = 0; i < 13; i++) {
                dl_hexagon(-i*i+400 , i*13 , i*30);
                dl_hexagon(i*i+150 , i*13 , i*30);
                dl_hexagon(-i*i+500 , i*13 , i*17);
                dl_hexagon(i*i+50 , i*13 , i*17);
                dl_circle(13*cos(M_PI/6*i)+150, 13*sin(M_PI/6*i)+300, 7, DL_RGB(200-i*15 , 200+i*i , 30*i*i), 1 , 1);
                dl_circle(29*cos(M_PI/6*i)+150, 29*sin(M_PI/6*i)+300, 10, DL_RGB(200-i*15 , 200+i*i , 30*i*i), 1 , 1);
                dl_circle(56*cos(M_PI/6*i)+150, 56*sin(M_PI/6*i)+300, 18, DL_RGB(200-i*15 , 200+i*i , 30*i*i), 1 , 1);
                dl_circle(100*cos(M_PI/6*i)+150, 100*sin(M_PI/6*i)+300, 27, DL_RGB(200-i*15 , 200+i*i , 30*i*i), 1 , 1);
  }
        for (q = 0; q < 51; q++) {
                dl_circle(50*cos(M_PI*q/25)+500, 50*sin(M_PI*q/25)+300, 50, DL_RGB(50 , 250-q*q , 10), 3 , 0);
  }
    while (1) {
        dl_wait(1.0);
  } 

    return 0;
}

