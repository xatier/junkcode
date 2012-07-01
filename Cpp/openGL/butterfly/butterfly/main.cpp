#include <GL/glut.h>
#include <math.h>


typedef struct {
	GLdouble x;
	GLdouble y;
} Point;

void init (void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}
#define AUTOFLUSH 0
void drawLine (const Point p1, const Point p2, double r, double g, double b)
{
	glColor3f(r, g, b);
	glBegin(GL_LINES);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p2.x, p2.y);
	glEnd();
#if !AUTOFLUSH
	glFlush();
#endif
}

Point trans (Point A) {
    double d = 0.5;
    Point O;
    O.x = 100, O.y = 80;
    A.x = A.x * d + O.x;
    A.y = A.y * d + O.y;
    return A;
}

double F (double t) {
    return t*(cos(t)+1);
}

void draw (void)
{
	Point A, B;
	double t = 0.0, t1;
	double delta = 0.01;
	const double PI = 3.14159;
    for (t = -31*PI; t <= 31*PI; t += delta) {
        t1 = t + delta;
        A.x = F(t)*cos(t);
        A.y = F(t)*sin(t);
        B.x = F(t1)*cos(t1);
        B.y = F(t1)*sin(t1);
        A = trans(A);
        B = trans(B);
        drawLine(A, B, 0.0, 0.0, 0.0);
    }
#if AUTOFLUSH
    glFlush();
#endif
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(10, 10);
    glutInitWindowSize(1024, 600);

    glutCreateWindow("openGL");

	init();
	glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
