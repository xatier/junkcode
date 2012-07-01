#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define DEP 13

int depth;

typedef struct {
	GLdouble x;
	GLdouble y;
} Point;

typedef struct {
    GLdouble x;
    GLdouble y;
} Vector;

void init (void)
{
	depth = 1;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void drawLine (const Point p1, const Point p2)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p2.x, p2.y);
	glEnd();
}

Vector vectorRevolve (Vector v, GLdouble theta) {
    Vector nv;
    theta = theta / 180.0 * 3.1415926535897;
    GLdouble sinTheta = sin(theta);
    GLdouble cosTheta = cos(theta);
    nv.x = v.x*cosTheta - v.y*sinTheta;
    nv.y = v.x*sinTheta + v.y*cosTheta;
    return nv;
}

void LSystem (char* ctrl, const GLdouble theta, const GLdouble len, const Point S)
{
    int i, ctrlLen = strlen(ctrl);
    Vector v;
    Point start, end;
    end = start = S;

    v.x = len;
    v.y = 0;

    for (i = 0; i < ctrlLen; i++) {
        switch (ctrl[i]) {
            case 'F':
                end.x = start.x + v.x;
                end.y = start.y + v.y;
                drawLine(start, end);
                break;
            case '+':
                v = vectorRevolve(v, theta);
                break;
            case '-':
                v = vectorRevolve(v, -theta);
                break;
        }
        start = end;
    }
}

char* nextLayer (const char *str) {
    int i, len = strlen(str);
    char* next = (char*)malloc(len*len);
    for (i = 0; i < len; i++) {
        if (str[i] == 'F')
            sprintf(next, "%s%s", next, str);
        else {
            sprintf(next, "%s%c", next, str[i]);
        }
    }
    return next;
}


void draw (void)
{
	Point A;
	char ctrl[] = "F+F-F-F+F";
	char *tmp[3];
	//the initial one:  F <- "F+F-F-F+F", theta = 90.0
	//koch curve in L system:  F <- "F+F--F+F", theta = 60.0

	A.x =  5.0, A.y = 140.0;
    LSystem(ctrl, 90.0, 5, A);

    A.y = 125.0;
    tmp[0] = nextLayer(ctrl);
    LSystem(tmp[0], 90.0, 2.5, A);

    tmp[1] = nextLayer(tmp[0]);
    A.y = 100.0;
    LSystem(tmp[1], 90.0, 1, A);

    A.y = 10.0;
    tmp[2] = nextLayer(tmp[1]);
    LSystem(tmp[2], 90.0, 0.0295, A);

    glFlush();      //flush the window

    free(tmp[0]);
    free(tmp[1]);
    free(tmp[2]);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1300, 680);

    glutCreateWindow("openGL L_System");

	init();
	glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
