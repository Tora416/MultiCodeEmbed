#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float tx = 0.0;
float ty = 0.0;

void circulo()
{
  int i;
  float angulo = 0.0;
  glBegin(GL_POLYGON);
  for (i = 0; i <= 50; i++)
  {
    angulo = 2 * M_PI * i / 50.0;
    glVertex2f(0.15 * cos(angulo), 0.15 * sin(angulo));
  }
  glEnd();
}

void quadrado(float x, float y){
  glBegin(GL_POLYGON);
    glVertex2f(-0.2+x, 0.2+y);
    glVertex2f(0.2+x, 0.2+y);
    glVertex2f(0.2+x, -0.2+y);
    glVertex2f(-0.2+x, -0.2+y);
  glEnd();
}

void retangulo(){
  glBegin(GL_POLYGON);
  glVertex2f(-0.05, -0.05);
  glVertex2f(0.05, -0.05);
  glVertex2f(0.05, -0.95);
  glVertex2f(-0.05, -0.95);
  glEnd();
}

void display_function()
{
  
  
  
  
  

  
  
  
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glColor3f(1.0, 1.0, 1.0);
  circulo();

  glColor3f(1.0, 1.0, 1.0);
  retangulo();

  glTranslatef(tx, ty, 0.0);
  
  glColor3f(0.5, 1.0, 0.5);
  quadrado(0.3, 0.3);

  glColor3f(1.0, 1.0, 0.0);
  quadrado(-0.3, 0.3);

  glColor3f(1.0, 0.0, 1.0);
  quadrado(0.3, -0.3);

  glColor3f(1.0, 0.0, 0.0);
  quadrado(-0.3, -0.3);

  glFlush();
}

void tecladoEspecial(int tecla, int x, int y)
{
  switch (tecla)
  {
  case GLUT_KEY_RIGHT:
    tx += 0.05;
    break;
  case GLUT_KEY_LEFT:
    tx -= 0.05;
    break;
  case GLUT_KEY_UP:
    ty += 0.05;
    break;
  case GLUT_KEY_DOWN:
    ty -= 0.05;
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