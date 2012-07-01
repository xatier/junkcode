#include <GL/glut.h>
#include <unistd.h>

#define DEP 5

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

void init (void)
{
	depth = 1;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void drawRect (const Point p1, const Point p2, const Point p3, const Point p4) {
    glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p2.x, p2.y);
		glVertex2d(p3.x, p3.y);
		glVertex2d(p4.x, p4.y);
	glEnd();
}

void sierpinskiRect (const Point A, const Point B, const Point C, const Point D, const int d)
{
	Point AB1, AB2, BC1, BC2, CD1, CD2, DA1, DA2, M1, M2, M3, M4;

	if (d == depth)
		return;

	AB1 = oneThirdPoint(A, B);
	BC1 = oneThirdPoint(B, C);
	CD1 = oneThirdPoint(C, D);
	DA1 = oneThirdPoint(D, A);

	AB2 = twoThirdPoint(A, B);
	BC2 = twoThirdPoint(B, C);
	CD2 = twoThirdPoint(C, D);
	DA2 = twoThirdPoint(D, A);

	M1 = twoThirdPoint(BC1, DA2);
	M2 = oneThirdPoint(BC1, DA2);
    M3 = oneThirdPoint(BC2, DA1);
    M4 = twoThirdPoint(BC2, DA1);

    drawRect(M1, M2, M3, M4);

	sierpinskiRect(   A, AB1,  M1, DA2, d+1);
	sierpinskiRect( AB1, AB2,  M2,  M1, d+1);
	sierpinskiRect( AB2,   B, BC1,  M2, d+1);
	sierpinskiRect(  M2, BC1, BC2,  M3, d+1);
	sierpinskiRect(  M3, BC2,   C, CD1, d+1);
	sierpinskiRect(  M4,  M3, CD1, CD2, d+1);
	sierpinskiRect( DA1,  M4, CD2,   D, d+1);
	sierpinskiRect( DA2,  M1,  M4, DA1, d+1);

}
void draw (void)
{
	Point A, B, C, D;
	A.x =  30.0, A.y = 30.0;
	B.x =  30.0, B.y = 140.0;
	C.x = 140.0, C.y = 140.0;
	D.x = 140.0, D.y = 30.0;

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2d(A.x, A.y);
		glVertex2d(B.x, B.y);
		glVertex2d(C.x, C.y);
		glVertex2d(D.x, D.y);
	glEnd();

	while (depth != DEP) {
		depth++;
		sierpinskiRect(A, B, C, D, 0);
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

    glutCreateWindow("openGL sierpinskiRect");

	init();
	glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
