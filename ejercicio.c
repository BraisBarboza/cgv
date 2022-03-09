#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

GLint ancho=400;
GLint alto=400;
GLfloat  angulos[8][3] ={
    {0.0f,0.0f,0.0f},
    {0.0f,0.0f,0.0f},
    {0.0f,0.0f,0.0f},
    {0.0f,0.0f,0.0f},
    {0.0f,0.0f,0.0f},
    {0.0f,0.0f,0.0f},
    {0.0f,0.0f,0.0f},
    {0.0f,0.0f,0.0f}
}; 
int current_member=0;
int articulation=0;
int joint=0;
int texture=0;
int automatic=0;
int speed=1;
int hazPerspectiva = 0;
int mouseX, mouseY;

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
     glOrtho(-12,12, -12, 12, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    ancho = width;
    alto = height;
}
void drawSphere(void){
  if(texture){
    glutWireSphere(0.5f, 8, 8);
  }else
    glutSolidSphere(0.5f, 8, 8);
}
void drawCube(void)
{
  if(texture){
    glutWireCube(2);
  }else{
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
}
void rotate(int joint,int axis,float amount){//funcion que modifica el angulo deseado
    angulos[joint][axis]=angulos[joint][axis]+amount;
}
void _half_member(int joint){//dibuja medio miembro y le pasamos su controlador
    drawSphere();//dibujamos la esfera con su angulo y el cubo pegado
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
  _half_member(joint1);
  glTranslatef(1.5f,0.0f,0.0f);
  _half_member(joint2);
  glPopMatrix();
}
void textureMenuf( int id){
    switch( id){
    case 0:
        texture=0;
        break;
    case 1:
        texture=1;
        break;
    case 2:
        exit(0);
        break;
    }
}
void speedMenuf( int id){
    switch( id){
    case 0:
        speed=1;
        break;
    case 1:
        speed=3;
        break;
    case 2:
        speed=15;
        break;
    }
}
void automaticLegs(){
  rotate(4,0,speed);
  rotate(6,0,-speed);
  if(automatic)
    glutTimerFunc(10, automaticLegs,5); 
}
void mainMenu(int id){
    switch( id){
    case 0:
        if(automatic){
          automatic--;
        } 
        else{
          automatic++;
          automaticLegs();
        } 
        break;
    }
}
void menus(){
int textureMenu, speedMenu;
textureMenu = glutCreateMenu(textureMenuf);
glutAddMenuEntry("Solid", 0);
glutAddMenuEntry("Wire", 1);
speedMenu=glutCreateMenu(speedMenuf);
glutAddMenuEntry("Slow", 0);
glutAddMenuEntry("Medium", 1);
glutAddMenuEntry("Fast", 2);
glutCreateMenu(mainMenu);
glutAddSubMenu("Texture", textureMenu);
glutAddMenuEntry("Atomatic Legs", 0);
glutAddSubMenu("Speed",speedMenu);
glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void display()
{ 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-10.0f);
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
    member(2,3);
    glPopMatrix();
    glTranslatef(2.0f,-6.5f,0.0f);
    glPushMatrix();
    glRotatef(-90, 0.0f, 0.0f, 1.0f);
    member(4,5);
    glPopMatrix();
    glTranslatef(3.0f,0.0f,0.0f);
    glPushMatrix();
    glRotatef(-90, 0.0f, 0.0f, 1.0f);
    member(6,7);
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
 
void keyboard(unsigned char key, int x, int y)//las teclas o,p seleccionan los brazos izq y derecho
                                              //las teclas k, l seleccionan las ppiernas izquierda y derecha
{
    switch(key)
    {
    case 'P':
    case 'p':
      current_member=0;
      break;
    case 'O':
    case 'o':
      current_member=2;
      break;
    case 'K':
    case 'k':
      current_member=4;
      break;
    case 'L':
    case 'l':
      current_member=6;
      break;
 
    case 'e':
    case 'E':
      joint=0;
      break;
 
    case 'Q':
    case 'q':
      joint=1;
      break;
 
    case 'W'://wasd modifican el valor del angulo en la direccion deseada
    case 'w':
      articulation=current_member+joint;
      rotate(articulation,1,1);
      break;
 
    case 'a':
    case 'A':
      articulation=current_member+joint;
      rotate(articulation,0,-1);
      break;
 
    case 's':
    case 'S':
      articulation=current_member+joint;
      rotate(articulation,1,-1);
      break;
 
    case 'D':
    case 'd':
      articulation=current_member+joint;
      rotate(articulation,0,1);
      break;
 
    case 'Z':
    case 'z':
      articulation=current_member+joint;
      rotate(articulation,2,1);
      break;
 
    case 'C':
    case 'c':
      articulation=current_member+joint;
      rotate(articulation,2,-1);
      break;
 
    case 27:   // escape
      exit(0);
      break;
    }
}

void mouse(int x, int y){
  int displacementX, displacementY, joint, leg;
  displacementX= x-mouseX;
  displacementY= y-mouseY;
  mouseX=x;
  mouseY=y;
  if (glutGetModifiers() == GLUT_ACTIVE_CTRL)joint=0;
  else joint=1;
  if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) leg=4;
  else leg=6;
  rotate(joint+leg,0,displacementX);
  rotate(joint+leg,1,displacementY);

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
    glutPassiveMotionFunc(mouse);
    menus();
    glutMainLoop();
    return 0;
}
