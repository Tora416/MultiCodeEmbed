#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float tx = 0.0;
float ty = 0.0;
float theta = 5.0;
float thetaBraco = 1.0;
float thetaPerna = 1.0;

void circulo()
{
  int i;
  float angulo = 0.0;
  glBegin(GL_POLYGON);
  for (i = 0; i <= 6; i++)
  {
    angulo = 2 * M_PI * i / 6;
    glVertex2f(0.04 * cos(angulo), 0.04 * sin(angulo));
  }
  glEnd();
}

void quadrado(float x, float y)
{
  glBegin(GL_POLYGON);
  glVertex2f(-0.2 + x, 0.8 + y);
  glVertex2f(-0.4 + x, 0.6 + y);
  glVertex2f(0.2 + x, 0.8 + y);
  glVertex2f(0.4+ x, 0.6 + y);
  glEnd();
}

void triangulo(float x1, float y1, float x2, float y2, float x3, float y3)
{
  glBegin(GL_TRIANGLES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
  glEnd();
}

void retangulo()
{
  glBegin(GL_POLYGON);
  glVertex2f(-0.4, -0.4);
  glEnd();
}

void display_function()
{
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  
  glPushMatrix();
    
    glColor3f(1.0, 1.0, 1.0);
    glRectf(-0.1, 0.8, 0.1, 0.6);
  glPopMatrix();

  
  glPushMatrix();
    glTranslatef(-0.06 , 0.75 , 0.0);
    
    glColor3f(1.0, 0, 0);
    circulo();
  glPopMatrix();

  
  glPushMatrix();
    glTranslatef(0.06, 0.75, 0.0);
    
    glColor3f(1.0, 0, 0);
    circulo();
  glPopMatrix();

  
  glPushMatrix();
    
    
    glColor3f(0, 0, 1);
    triangulo(0.0,0.73, -0.05,0.68, 0.05,0.68);
  glPopMatrix();

  
  glPushMatrix();
    
    
    glColor3f(1, 0.5, 0.5);
    glRectf(-0.05, 0.64, 0.05, 0.62);
  glPopMatrix();

  
  glPushMatrix();
  glTranslatef(-0.2, 0.45, 0);
  glRotatef(thetaBraco, 0.0, 0.0, 1.0);
  glColor3f(1, 0.1, 1);
  glRectf(-0.4, 0.05, 0.2, -0.05);
  glPopMatrix();

  
  glPushMatrix();
  glTranslatef(0.20, 0.45, 0);
  glRotatef(-thetaBraco, 0.0, 0.0, 1.0);
  glColor3f(1, 0.1, 1);
  glRectf(-0.2, 0.05, 0.4, -0.05);
  glPopMatrix();

  
  glPushMatrix();
    glTranslatef(0.0, 0.2, 0);
    glColor3f(0.0, 1.0, 0.0);
    glRectf(-0.2, 0.4, 0.2, -0.4);
  glPopMatrix();

  
  glPushMatrix();
    glTranslatef(0.1, -0.2, 0);
    glColor3f(0.0, 1.0, 0.0);
    glRotatef(thetaPerna, 0.0, 0.0, 1.0);
    glRectf(-0.05, 0.3, 0.05, -0.3);
  glPopMatrix();

  
  glPushMatrix();
    glTranslatef(-0.1, -0.2, 0);
    glColor3f(0.0, 1.0, 0.0);
    glRotatef(-thetaPerna, 0.0, 0.0, 1.0);
    glRectf(-0.05, 0.3, 0.05, -0.3);
  glPopMatrix();

  glFlush();
}

void tecladoEspecial(int tecla, int x, int y)
{
  switch (tecla)
  {
  case GLUT_KEY_RIGHT:
    printf("%f\n", thetaPerna);
    if (thetaPerna > -6.000000)
    {
      thetaPerna -= 7.0;
    }
    break;

  case GLUT_KEY_LEFT:
    printf("%f\n", thetaPerna);
    if (thetaPerna <= +84.0000)
    {
      thetaPerna += 7.0;
    }
    break;
  
  case GLUT_KEY_UP:
    printf("%f\n", thetaBraco);
    if (thetaBraco >= -84.0000)
    {
      thetaBraco -= 7.0;
    }
    break;
  
  case GLUT_KEY_DOWN:
    printf("%f\n", thetaBraco);
    if (thetaBraco < 22.000000)
    {
      thetaBraco += 7.0;
    }
    break;
  
  default:
    break;
  }
  glutPostRedisplay();
}

void init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(1.0, 1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  
}

int main(int argc, char **argv)
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(50, 100);
  glutInitWindowSize(400, 400);
  glutInit(&argc, argv);
  glutCreateWindow("Transformações Geométricas - Translação");
  init();
  glutDisplayFunc(display_function);
  glutSpecialFunc(tecladoEspecial);
  glutMainLoop();
  return 0;
}