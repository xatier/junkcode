#include <GL/glut.h>

#define DEP 75

int depth;

typedef struct {
	GLdouble x;
	GLdouble y;
} Point;

Point midPoint (const Point a, const Point b)
{
	Point P;
	P.x = (a.x+b.x) / 2;
	P.y = (a.y+b.y) / 2;
	return P;
}

Point divPoint (const Point a, const Point b, const int i, const int j)
{
	Point P;
	P.x = (i*a.x + j*b.x) / (i+j);
	P.y = (i*a.y + j*b.y) / (i+j);
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

void nine (const Point A, const Point B, const Point C, const Point D, const int d)
{
    int i, j;
    i = 7, j = 1;
    //also try
    //i = 999, j = 1;

	Point m12, m23, m34, m41;
	if (d == depth)
		return;

	m12 = midPoint(A, B);
	m23 = midPoint(B, C);
	m34 = midPoint(C, D);
	m41 = midPoint(D, A);

	drawLine(A, B);
	drawLine(B, C);
	drawLine(C, D);
	drawLine(D, A);
	drawLine(A, m23);
	drawLine(m23, D);
	drawLine(D, m12);
	drawLine(m12, C);
	drawLine(C, m41);
	drawLine(m41, B);
	drawLine(B, m34);
	drawLine(m34, A);

	nine(divPoint(A, B, i, j), divPoint(B, C, i, j), divPoint(C, D, i, j), divPoint(D, A, i, j), d+1);

}
void draw (void)
{
    Point A, B, C, D;
	A.x =  40.0, A.y =  30.0;
	B.x =  40.0, B.y = 140.0;
	C.x = 150.0, C.y = 140.0;
	D.x = 150.0, D.y =  30.0;

	while (depth != DEP) {
		depth++;
		nine(A, B, C, D, 0);
	}
	glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(10, 10);
    glutInitWindowSize(800, 600);

    glutCreateWindow("openGL Square recursion");

	init();
	glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
