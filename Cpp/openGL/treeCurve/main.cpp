#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#define DEP 18

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

void vectorRevolution (const Point A, const Point B, GLdouble theta, const int d)
{
	Vector v;
	Point start1, end1, start2, end2;
	v.x = B.x - A.x;
	v.y = B.y - A.y;

	if (d == depth)
		return;

	drawLine(A, B);

	v = vectorRevolve(v, theta);

	v.x *= 0.85;
	v.y *= 0.85;

	start2 = start1 = B;
	end1.x = B.x + v.x;
	end1.y = B.y + v.y;

	v = vectorRevolve(v, -theta*2);

	end2.x = B.x + v.x;
	end2.y = B.y + v.y;

	vectorRevolution( start1, end1, theta, d+1);
	vectorRevolution( start2, end2, theta, d+1);

}
void draw (void)
{
	Point A, B;
	A.x =  100.0, A.y = 25.0;
	B.x =  100.0, B.y = 40.0;

	while (depth != DEP) {
		depth++;
        vectorRevolution(A, B, 20.0, 0);
        glFlush();
        sleep(1);
	}
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(10, 10);
    glutInitWindowSize(800, 600);

    glutCreateWindow("openGL treeCurve");

	init();
	glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
