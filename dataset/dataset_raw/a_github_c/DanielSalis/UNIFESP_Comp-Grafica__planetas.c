#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct BMPImagem
{
    int   width;
    int   height;
    char *data;
}BMPImage;

#define MAX_NO_TEXTURES 6

GLuint texture_id[MAX_NO_TEXTURES];

char* filenameArray[MAX_NO_TEXTURES] = {
        "earthTexture.bmp",
        "surface1.bmp",
        "surface2.bmp",
        "surface3.bmp",
        "surface4.bmp",
        "surface7.bmp"
};

GLUquadricObj *obj;

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
float angulo = 20.0;

double phi = 0.0;
double theta = 0.0;
double r = 0.5;
int n = 450;
int texture_index = 0;

double s1 = 2.5;
double s2 = 2.5;

double rt = 0.25;
double Rt = 0.75;

int stop = 0;
float cameraY=0.5;

void getBitmapImageData( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
        printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
        printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
        printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    fseek( pFile, 24, SEEK_CUR );

    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
    {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i+2];
        pImage->data[i+2] = charTemp;
    }
}

void CarregaTexturas()
{
    BMPImage textura;

    glGenTextures(MAX_NO_TEXTURES, texture_id);
                                
    int i;
    for ( i=0; i<MAX_NO_TEXTURES; i++ ) {
        getBitmapImageData( filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }
}

void initTexture (void)
{

    glEnable ( GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    CarregaTexturas();

}

void lightning(){
    GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

    GLfloat light1_pos[] = {-2.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1,GL_SPECULAR, white);
    GLfloat direction[] = {1.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45.0f);          
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.1f);             

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void init(void)
{
    glEnable ( GL_COLOR_MATERIAL );
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 2.0, 6.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 2.0, 8.0);
    glViewport(0, 0, 700, 700);

    lightning();
}

void desenhaEsferaComTextura(){
     obj = gluNewQuadric();
     gluQuadricTexture(obj,GL_TRUE);
     gluSphere(obj,0.1,50,50);
}

void esferaQuadrica(){
    int i,j;
    glClear(GL_COLOR_BUFFER_BIT);
    for(i=0;i<n;i++){
        glBegin(GL_POINTS);
            for(j=0;j<n;j++){
                glVertex3f(r*cos(phi)*cos(theta),r*cos(phi)*sin(theta),r*sin(phi));
                phi = phi + (2*M_PI)/n;
            }
        glEnd();
        phi = 0.0;
        theta = theta+(2*M_PI)/n;
    }
}

void desenhaPlanetaCentral(){
    glPushMatrix();
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat ns;
    diffuse[0] = 1.0;
    diffuse[1] = 1.0;
    diffuse[2] = 1.0;
    diffuse[3] = 1.0f;
    specular[0] = 1;
    specular[1] = 1;
    specular[2] = 1;
    specular[3] = 1.0f;
    ns = 50.0f;
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);
    glBindTexture(GL_TEXTURE_2D, 0);
        glRotatef(angulo,0.0,1.0,0.0);
        esferaQuadrica();
    glPopMatrix();
    
}

void desenhaSatelites(){
    float v1 = 1.2;
    float v2 = 1.4;

        
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture_id[2]);
        glRotatef(angulo*v1,0.0,1.0,0.0);
        glTranslatef(-0.48,0.0,1.0);
        desenhaEsferaComTextura();
    glPopMatrix();

        
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture_id[4]);
        glRotatef(-angulo*v2,0.0,1.0,0.0);
        glTranslatef(-0.8,0.0,2.0);
        desenhaEsferaComTextura();
    glPopMatrix();
}

void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        desenhaPlanetaCentral();
        desenhaSatelites();

        glFlush();
}

void rotacionarPlaneta(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(0.0, 2.0, 6.0,
                        0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0, 1.0, 2.0, 8.0);
           break ;
        case GLUT_KEY_DOWN :
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(0.0, -7.0, 3.0,
                    0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0, 1.0, 2.0, 8.0);
           break ;
        case GLUT_KEY_LEFT :
           angulo-=15;
           break ;
        case GLUT_KEY_RIGHT :
           angulo+=15;
           break ;
        default:
           break;
     }
     glutPostRedisplay() ;
}

void executaAnimacao(){
    if(stop == 0){
        angulo+=6;
        glutTimerFunc(100, executaAnimacao, 1);
        glutPostRedisplay();
    }
}

void mouse(int botao, int estado, int x, int y)
{
    switch (botao)
    {
    case GLUT_LEFT_BUTTON:
        stop = 1;
        break;
    case GLUT_RIGHT_BUTTON:
        stop = 0;
                glutTimerFunc(100, executaAnimacao, 1);
        glutPostRedisplay();
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(700,700);
    glutCreateWindow("Planetas");
    glutDisplayFunc(display);
    glutSpecialFunc(rotacionarPlaneta);
    glutTimerFunc(5, executaAnimacao, 1);
    glutMouseFunc(mouse);
    init();
    initTexture();
    glutMainLoop();
    return 0;
}