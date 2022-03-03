#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLint ancho=400;
GLint alto=400;
GLfloat  angulos[2][3] ={
    {0.0f,0.0f,0.0f},
    {0.0f,0.0f,0.0f}
}; 

int joint=0;
int hazPerspectiva = 0;

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
     glOrtho(-8,8, -8, 8, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    ancho = width;
    alto = height;
}

void drawCube(void)
{
    glColor3f(1.0f, 0.0f, 0.0f); // Rojo
    glBegin(GL_QUADS);       //cara frontal
    glVertex3f(-1.0f, -1.0f,  1.0f); 
    glVertex3f( 1.0f, -1.0f,  1.0f); 
    glVertex3f( 1.0f,  1.0f,  1.0f); 
    glVertex3f(-1.0f,  1.0f,  1.0f); 
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    glBegin(GL_QUADS);       //cara trasera
    glVertex3f( 1.0f, -1.0f, -1.0f); 
    glVertex3f(-1.0f, -1.0f, -1.0f); 
    glVertex3f(-1.0f,  1.0f, -1.0f); 
    glVertex3f( 1.0f,  1.0f, -1.0f); 
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // Azul
    glBegin(GL_QUADS);       //cara lateral izq
    glVertex3f(-1.0f,-1.0f, -1.0f); 
    glVertex3f(-1.0f,-1.0f,  1.0f); 
    glVertex3f(-1.0f, 1.0f,  1.0f); 
    glVertex3f(-1.0f, 1.0f, -1.0f); 
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
    glBegin(GL_QUADS);       //cara lateral dcha
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glEnd(); 
    
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    glBegin(GL_QUADS);       //cara arriba
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();
 
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glBegin(GL_QUADS);       //cara abajo
    glVertex3f( 1.0f,-1.0f, -1.0f);
    glVertex3f( 1.0f,-1.0f,  1.0f);
    glVertex3f(-1.0f,-1.0f,  1.0f);
    glVertex3f(-1.0f,-1.0f, -1.0f);
    glEnd();
}
void rotate(int joint,int axis,int amount){//funcion que modifica el angulo deseado
    angulos[joint][axis]=angulos[joint][axis]+amount;
}
void _half_member(int joint){//dibuja medio miembro y le pasamos su controlador
    glutWireSphere(0.5f, 8, 8);//dibujamos la esfera con su angulo y el cubo pegado
    glRotatef(angulos[joint][0], 1.0f, 0.0f, 0.0f);
    glRotatef(angulos[joint][1], 0.0f, 1.0f, 0.0f);
    glRotatef(angulos[joint][2], 0.0f, 0.0f, 1.0f);
    glTranslatef(1.5f,0.0f,0.0f);
    glPushMatrix();
    glScalef(2.0,1.0,1.0);
    glScalef(0.5,0.5,0.5);
    drawCube();
    glPopMatrix();
}
void member(int joint1, int joint2){
  glPushMatrix();
  _half_member(joint);
  glTranslatef(1.5f,0.0f,0.0f);
  _half_member(joint);
  glPopMatrix();
}
void display()
{ 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-5.0f);
    glPushMatrix();
    glScalef(3.0,4.0,1.0);
    drawCube();
    glPopMatrix();
    glTranslatef(3.5f,2.0f,0.0f);
    member(0,1);
    glTranslatef(-7.0f,0.0f,0.0f);
    glPushMatrix();
    glRotatef(180, 0.0f, 1.0f, 0.0f);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    member(0,1);
    glPopMatrix();
    glTranslatef(2.0f,-6.5f,0.0f);
    glPushMatrix();
    glRotatef(-90, 0.0f, 0.0f, 1.0f);
    member(0,1);
    glPopMatrix();
    glTranslatef(3.0f,0.0f,0.0f);
    glPushMatrix();
    glRotatef(-90, 0.0f, 0.0f, 1.0f);
    member(0,1);
    glPopMatrix();
    glLoadIdentity();
    glFlush();
    glutSwapBuffers();
    
}

void init()
{
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    ancho = 400;
    alto = 400;
}
 

void idle()
{
    display();
}
 
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'Q'://q y e seleccionan la articulacion
    case 'q':
      joint=0 ;
      break;
 
    case 'e':
    case 'E':
      joint=1;
      break;
 
    case 'W'://wasd modifican el valor del angulo en la direccion deseada
    case 'w':
      rotate(joint,1,1);
      break;
 
    case 'a':
    case 'A':
      rotate(joint,0,-1);
      break;
 
    case 's':
    case 'S':
      rotate(joint,1,-1);
      break;
 
    case 'D':
    case 'd':
      rotate(joint,0,1);
      break;
 
    case 'Z':
    case 'z':
      rotate(joint,2,1);
      break;
 
    case 'C':
    case 'c':
      rotate(joint,2,-1);
      break;
 
    case 27:   // escape
      exit(0);
      break;
    }
}
 
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Cubo");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
