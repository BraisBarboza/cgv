#include <GL/glut.h>

#define WIDTH 500
#define HEIGTH 500
#define ORIGIN_X 50
#define ORIGIN_Y 50

void init()
{
    glClearColor(0,0,0,0);/*Fijar el color por defecto a negro en el formato (RGBA)*/
}

void trianguloBlanco(){
    glColor3f( 1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0f, -1.0f, 0.0f); //V1
    glVertex3f(1.0f, -1.0f, 0.0f); //V2
    glVertex3f(0.0f, 1.0f, 0.0f); //V3
    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT); /*Borrado del FrameBuffer*/ 
    glMatrixMode(GL_MODELVIEW); /* Activar las modificaciones en los objetos del mundo*/
    glLoadIdentity();/* Cargar la identidad en la matrix de modeficaciones del mundo*/
    trianguloBlanco();
    /* Lo que haya que pintar ira aquí*/

    glutSwapBuffers(); /*Forzar el renderizado*/
}


void reshape(int w, int h)
{
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);/*Activar las modificaciones en la camara*/
    glLoadIdentity(); /*Cargar la identidad en la matrix de proyección*/
    glOrtho(-1, 1, -1, 1, -1, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); /*Cargar el teclado y el ráton*/
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); /*inicializar el Frame Buffer GLUT_DOUBLE O GLUT_SIMPLE para uno o 2 buffers*/
    glutInitWindowSize(WIDTH, HEIGTH); /*Tamaño de la ventana*/ 
    glutInitWindowPosition(ORIGIN_X, ORIGIN_Y); /*Posición del extremo superior-izquierdo de la ventana*/
    glutCreateWindow("Hola Mundo"); /* Crear la ventana*/
    init();
    glutDisplayFunc(display); /*Activar la funcion de pintado*/
    glutReshapeFunc(reshape); /*Activar la funcion de escalado*/
    glutMainLoop(); /*Arrancar el bucle de OpenGL*/
    return 0;
}