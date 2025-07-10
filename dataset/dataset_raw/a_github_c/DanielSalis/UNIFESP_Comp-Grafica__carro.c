#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float tx = 0.0;
float ty = 0.0;
float theta = 5.0;

void circulo()
{
  int i;
  float angulo = 0.0;
  glBegin(GL_POLYGON);
  for (i = 0; i <= 8; i++)
  {
    angulo = 2 * M_PI * i / 8;
    glVertex2f(0.125 * cos(angulo), 0.125 * sin(angulo));
  }
  glEnd();

}

void quadrado(float x, float y)
{
  glBegin(GL_POLYGON);
  glVertex2f(-0.2 + x, 0.2 + y);
  glVertex2f(0.2 + x, 0.2 + y);
  glVertex2f(0.2 + x, -0.2 + y);
  glVertex2f(-0.2 + x, -0.2 + y);
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
    glTranslatef(-0.35+tx, 0+ty, 0.0);
    glRotatef(theta, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    circulo();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.35+tx, 0+ty, 0.0);
    glRotatef(theta, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 0);
    circulo();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0+tx, 0.32+ty, 0);
    glColor3f(0.0, 1.0, 0.0);
    glRectf(-0.4, 0.2, 0.4, -0.2);
  glPopMatrix();

  glFlush();
}

void tecladoEspecial(int tecla, int x, int y)
{
  switch (tecla)
  {
  case GLUT_KEY_RIGHT:
    tx += 0.05;
    theta -= 8.0;
    break;
  case GLUT_KEY_LEFT:
    tx -= 0.05;
    theta += 8.0;
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