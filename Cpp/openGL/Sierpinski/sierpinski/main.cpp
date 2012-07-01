#include <GL/glut.h>
#include <unistd.h>

#define DEP 7

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

void init (void)
{
	depth = 1;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void drawTriangle (const Point p1, const Point p2, const Point p3) {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2d(p1.x, p1.y);
        glVertex2d(p2.x, p2.y);
        glVertex2d(p3.x, p3.y);
    glEnd();
}

void sierpinski (const Point A, const Point B, const Point C, const int d)
{
	Point m12, m23, m31;
	if (d == depth)
		return;

	m12 = midPoint(A, B);
	m23 = midPoint(B, C);
	m31 = midPoint(C, A);

    drawTriangle(m12, m23, m31);

	sierpinski(  A, m12, m31, d+1);
	sierpinski(m12,   B, m23, d+1);
	sierpinski(m31, m23,   C, d+1);

}
void draw (void)
{
    Point A, B, C, D;
	A.x =  30.0, A.y = 20.0;
	B.x =  90.0, B.y = 130.0;
	C.x = 150.0, C.y = 20.0;

	glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2d(A.x, A.y);
        glVertex2d(B.x, B.y);
        glVertex2d(C.x, C.y);
    glEnd();

	while (depth != DEP) {
		depth++;
		sierpinski(A, B, C, 0);
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

    glutCreateWindow("openGL sierpinski");

	init();
	glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
