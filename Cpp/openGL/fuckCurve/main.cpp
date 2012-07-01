#include <GL/glut.h>
#include <math.h>
#define DEP 400

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

void vectorRevolution (Point A, Point B, int d)
{
	Vector v;
	Point start, end;

    while (d < DEP) {
        v.x = B.x - A.x;
        v.y = B.y - A.y;

        drawLine(A, B);

        v = vectorRevolve(v, 89.5);

        v.x *= 0.99, v.y *= 0.99;
        //also try :
        //v.x *= 0.9 , v.y *= 0.9 ;

        A = B;
        B.x = B.x + v.x;
        B.y = B.y + v.y;
        d++;
    }
    glFlush();

}
void draw (void)
{
	Point A, B;
	A.x =  30.0, A.y = 10.0;
	B.x =  150.0, B.y = 10.0;

    vectorRevolution(A, B, 0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(10, 10);
    glutInitWindowSize(800, 600);

    glutCreateWindow("openGL fuckCurve");

	init();
	glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
