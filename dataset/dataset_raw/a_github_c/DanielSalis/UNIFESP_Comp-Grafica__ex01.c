#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float up = 0.0;
float right = 0.0;

void point(){
    glColor3f(0.0, 0.0, 1.0); 
    glPointSize(5.0f); 
    glBegin(GL_POINTS);
        glVertex2f(0.0+up,0.0+right);
    glEnd();
}

void desenha()
{
    glClearColor(0, 0, 0, 0); 
    glClear(GL_COLOR_BUFFER_BIT);
    point();
    glFlush();
}


void mouse(int botao, int estado, int x, int y)
{
    float mx = x;
    float my = y;
    float ox = (mx / 200 - 1.0);
    float oy = -(my / 200 - 1.0);

    switch (botao)
    {
    case GLUT_LEFT_BUTTON:
        if (estado == GLUT_DOWN){
            printf("x = %f, y = %f\n", ox, oy);
            up = ox;
            right = oy;
            point();
        }
        break;

    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 400);

    glutCreateWindow("Exercicio 01");
    glutDisplayFunc(desenha);

    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}