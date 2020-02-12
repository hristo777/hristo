#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include<cmath>

using namespace std;

int N=0;

class Point {
public:
	float x, y;
	Point() // default constructor
	{
		x = 0;
		y = 0;
	}
	Point(float x, float y) :x(x), y(y) // constructor with parameters
	{
	
	}
	void setxy(float x2, float y2) // setters for x and y
	{
		x = x2;
		y = y2;
	}
	// operators =,+,-,*
	const Point& operator=(const Point& rPoint)
	{
		x = rPoint.x;
		y = rPoint.y;
		return *this;
	}
	
	Point operator-(const Point& p)
	{
		return { x - p.x,y - p.y };
	}

	Point operator+(const Point& p)
	{
		return { x + p.x,y + p.y };
	}

	Point operator*(const int N)
	{
		return { x * N, y * N };
	}

};




Point abc[10000]; //array that contains the numbers of the points 
Point A(320, 250);
int SCREEN_HEIGHT = 500;

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 500.0);

}

void drawDot(float x, float y) {
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

void drawLine(Point p1, Point p2) {
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
	glFlush();
}
Point getCasteljauPoint(int r, int i, float t,Point arr[]) {
	if (r == 0) {
		return arr[i];
	}

	Point p1 = getCasteljauPoint(r - 1, i, t,arr);
	Point p2 = getCasteljauPoint(r - 1, i + 1, t,arr);

	return Point((float)((1 - t) * p1.x + t * p2.x), (float)((1 - t) * p1.y + t * p2.y));
}

void drawCasteljau(Point PT[],int N) {
	if (N == 0)
	{
		return;
	}
	for (int i = 0; i < N; i++)
	{
		drawDot(PT[i].x,PT[i].y);
	}
	Point tmp, prev=PT[0];
		
		for (float t = 0.000; t <= 1.000; t += 0.001) 
		{
			tmp = getCasteljauPoint(N-1, 0, t,PT);
			drawLine(tmp,prev);
			prev = tmp;
		}
	}
void drawHodograph()
{
	Point def[200];
	int k = 0;//1
	for (int i = 1; i < N;)
	{
		//def[0]=A;
		def[k] = (abc[i] - abc[i-1])+A;
		k++;
		i++;
	}
	drawCasteljau(def,k);//k+1
	for (int i = 0; i <=N; i++) {
		if (i==N) //to see the cordinats of the points
		{
			for (int i = 0; i < k; i++)
			{
				cout << def[i].x << " " << def[i].y << endl;
			}
			for (int i = 0; i < N; i++)
			{
				cout << abc[i].x << " " << abc[i].y << endl;
			}
		}
	}
}
bool IsLeft(int x)
{
	if (x >= 0.0 && x <= 320.0)
	{
		return true;
    }
	else
	{
		return false;
	}
}
void myMouse(int button, int state, int x, int y)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && IsLeft(x)) 
	{
		abc[N].setxy((float)x,(float)(SCREEN_HEIGHT - y));
		N++;
	}
}


void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	drawLine({ 320,0 }, { 320,500 });
	drawCasteljau(abc,N);
	drawHodograph();
	glFlush();
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 500);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Hodograph");
	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();

	return 0;
}