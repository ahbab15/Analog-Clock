#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>

const GLfloat tam_x = 50.0f;
const GLfloat tam_y = 50.0f;

const GLint sy = 30;
const GLint my = 25;
const GLint hy = 20;

int hora;
int minuto;
int segundo;

void circulo(GLfloat xc, GLfloat yc, GLfloat raio, bool fill)
{
  const GLfloat c = 3.14169f / 180.0f;
  GLint i;

  glBegin(fill ? GL_TRIANGLE_FAN : GL_LINE_LOOP);

  for (i = 0; i <= 360; i += 2)
  {
    float a = i * c;
    glVertex2f(xc + sin(a) * raio, yc + cos(a) * raio);
  }

  glEnd();
}


void desenha(void)
{

	glClear(GL_COLOR_BUFFER_BIT);


    glColor3f(1.0f, 0.0f, 1.0f);
    circulo(0, 0, tam_x, true);

    glColor3f(0.0f, 0.0f, 0.0f);
    circulo(0, 0, tam_x, false);


    float anguloS = segundo * 6;


    glRotatef(-anguloS, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(0,0);
    glVertex2i(0,sy);
    glEnd();

    glLoadIdentity();


    float anguloM = minuto * 6;


    glRotatef(-anguloM, 0.0f, 0.0f, 1.0f);

	glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2i(0,0);
    glVertex2i(0,my);
    glEnd();

    glLoadIdentity();
	float anguloH = (hora + minuto/60.0) * 30;


    glRotatef(-anguloH, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2i(0,0);
    glVertex2i(0,hy);
    glEnd();

    glLoadIdentity(); 	glFlush();
}

void redimensiona(GLsizei largura, GLsizei altura)
{

     glViewport(0, 0, largura, altura);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    if (largura <= altura)
       gluOrtho2D(-tam_x, tam_x, -tam_y * altura / largura, tam_y * altura / largura);
    else
       gluOrtho2D(-tam_x * largura / altura, tam_x * largura / altura, -tam_y, tam_y);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void move(int n)
{

     time_t agora = time(0);
     struct tm *datahora = localtime(&agora);

     hora = datahora->tm_hour;
     minuto = datahora->tm_min;
     segundo = datahora->tm_sec;

     glutPostRedisplay();
     glutTimerFunc(1000, move, 0);
}


void inicializa (void)
{

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400,400);
    glutInitWindowPosition(10,10);
	glutCreateWindow("Clock");
	glutDisplayFunc(desenha);
	glutReshapeFunc(redimensiona);
	glutTimerFunc(1000, move, 0);
	inicializa();
	glutMainLoop();
	return 0;
}
