// To compile in Linux: g++ -o mouse_exam mouse_exam.cpp -lGL -lGLU -lglut -lm

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GlUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#endif

#include <iostream>
#include <cmath>
using namespace std;

#define WIDTH 600
#define HEIGHT 600

#define WLEFT 0
#define WRIGHT WIDTH
#define WBOTTOM 0
#define WTOP HEIGHT 

#define RGBBLACK 0,0,0
#define RGBGREY .8,.8,.8

static int tracking = 0;
float previousx;
float previousy;

int inwindow(int x, int y)
{
	return(x>WLEFT && x<WRIGHT && y>WBOTTOM && y<WTOP);
}

void m_motion(int x, int y)
{
	y = WTOP - y;



	if (tracking && inwindow(x, y))
	{
		glBegin(GL_LINES);
		glVertex2f(previousx, previousy);
		glVertex2f(x, y);
		glEnd();

		glFlush();
	}
}

void handleButton(int button, int state, int x, int y)
{
	y = WTOP - y;

	if (button != GLUT_LEFT_BUTTON)
	{
		return;
	}

	if (state == GLUT_DOWN)
	{
		if (inwindow(x, y))
		{
			tracking = 1;
			previousx = x;
			previousy = y;

			cout << previousx << " " << previousy << endl;
		}
	}

	else
	{
		tracking = 0;
	}
}

void drawMouse(void)
{
	int i;

	glClearColor(RGBGREY, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(RGBBLACK);

	glFlush();

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Mouse Exam");
	glutDisplayFunc(drawMouse);
	glutMouseFunc(handleButton);
	glutMotionFunc(m_motion);
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	glutMainLoop();

	return 0;
}