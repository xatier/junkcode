#include <glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define DEP 8


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
//	glFlush();
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

void kerker (Point A, Point B, int d) {
    Point p1, p2;
    Vector v;

    if (d == depth)
        return;

    v.x = (B.x - A.x) / 2.645;
    v.y = (B.y - A.y) / 2.645;
    v = vectorRevolve(v, 19.1);

    p1.x = A.x + v.x;
    p1.y = A.y + v.y;

    v = vectorRevolve(v, -60.0);
    p2.x = p1.x + v.x;
    p2.y = p1.y + v.y;


    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
		glVertex2d(A.x, A.y);
		glVertex2d(B.x, B.y);
	glEnd();

    drawLine(A, p1);
    drawLine(p1, p2);
    drawLine(p2, B);

    glColor3f(1.0, 0.3, 0.0);
    glBegin(GL_LINES);
		glVertex2d(A.x, A.y);
		glVertex2d(A.x, A.y-2);
		glVertex2d(B.x, B.y);
		glVertex2d(B.x, B.y-2);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p1.x, p1.y-2);
		glVertex2d(p2.x, p2.y);
		glVertex2d(p2.x, p2.y-2);
	glEnd();

    kerker( A, p1, d+1);
    kerker(p1, p2, d+1);
    kerker(p2,  B, d+1);

}

void draw (void)
{
    Point A, B;
    A.x = 5.0, A.y = 70.0;
    B.x = 190.0, B.y = 20.0;

    while (depth != DEP) {
        depth++;
        kerker(A, B, 0);
    }
    glFlush();
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
