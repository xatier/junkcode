#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#define DEP 4

int depth;

typedef struct {
	GLdouble x;
	GLdouble y;
} Point;

Point oneThirdPoint (const Point a, const Point b)
{
	Point P;
	P.x = (2*a.x + b.x) / 3;
	P.y = (2*a.y + b.y) / 3;
	return P;
}

Point twoThirdPoint (const Point a, const Point b)
{
	Point P;
	P.x = (a.x + 2*b.x) / 3;
	P.y = (a.y + 2*b.y) / 3;
	return P;
}

Point kPoint( const Point a, const Point b ){
	Point P;
	P.x = a.x + ( (3*(b.x-a.x) - sqrt(3)*(b.y-a.y))  / 6 );
	P.y = a.y + ( (3*(b.y-a.y) - sqrt(3)*(a.x-b.x))  / 6 );
	return P;
}

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

void kochCurve (const Point A, const Point B, const int d)
{
	Point p1, p2, p3;

	if (d == depth)
		return;
    p1 = oneThirdPoint(A, B);
    p2 = kPoint(A, B);
    p3 = twoThirdPoint(A, B);

	drawLine( A, p1);
	drawLine(p1, p2);
	drawLine(p2, p3);
	drawLine(p3,  B);

    glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p3.x, p3.y);
	glEnd();
	glFlush();

	kochCurve( A, p1, d+1);
	kochCurve(p1, p2, d+1);
	kochCurve(p2, p3, d+1);
	kochCurve(p3,  B, d+1);

}
void draw (void)
{
	Point A, B, C;
	A.x =  60.0, A.y = 50.0;
	B.x = 150.0, B.y = 50.0;
	C.x = 105.0, C.y = 127.9422;

	while (depth != DEP) {
		depth++;
		kochCurve(A, C, 0);
        kochCurve(B, A, 0);
        kochCurve(C, B, 0);
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

    glutCreateWindow("openGL kochSnow");

	init();
	glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
