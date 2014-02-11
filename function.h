#include<math.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
struct GLfloatPoint
{
	GLfloat x,y;
};
typedef struct GLfloatPoint GLfloatPoint;
struct GLintPoint
{
	GLint x,y;
};
typedef struct GLintPoint GLintPoint;
struct GLfloatPoint CP;
void moveTo(GLfloat x,GLfloat y)
{
	CP.x=x;
	CP.y=y;
}

void lineTo(GLfloat x,GLfloat y)
{
	glBegin(GL_LINES);
	glVertex2f(CP.x,CP.y);
	glVertex2f(x,y);
	glEnd();
}

void moveToPoint(struct GLfloatPoint point)
{
	CP.x=point.x;
	CP.y=point.y;
}

void lineToPoint(struct GLfloatPoint point)
{
	glBegin(GL_LINES);
	glVertex2f(CP.x,CP.y);
	glVertex2f(point.x,point.y);
	glEnd();
}

void drawDot(double x,double y)
{
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void drawCircle(double x, double y, float radius) 
{
	float angle;
	glBegin(GL_POLYGON);
	int i;
	for(i= 0; i < 100; i++) 
	{
		angle = i*2*M_PI/100;
	        glVertex2f(x + (cos(angle) * radius), y + (sin(angle) * radius));
	}
	glEnd();
} 

void drawEllipse(int w,int h,struct GLintPoint center)
{
	double i;
	glBegin(GL_LINE_LOOP);
	for(i=0;i<2*M_PI;i+=0.05)
	glVertex2f(center.x+w*cos(i),center.y+h*sin(i));
	glEnd();
}

void drawPolylineFile(char *fileName)
{
	FILE *inStream;
	inStream=fopen(fileName,"r");
	int numpolys,numLines,x,y;
	fscanf(inStream ,"%d",&numpolys);      // read the number of polylines
	int j,i;
	for(j=0; j< numpolys;j++)   //total number of polylines in the file
	{
		fscanf(inStream,"%d",&numLines);     // number of point in the polylines    
		glBegin(GL_LINE_STRIP); 
		for(i=0;i<numLines; i++)        
		{
			fscanf(inStream,"%d", &x);
			fscanf(inStream,"%d", &y);
			glVertex2i(x,y);

		}
		glEnd();	
	}
	
	glFlush();
	fclose(inStream);
}

// to set the window

void setWindow(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top)
{
	//define our own function to specify the window as explained 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left,right,bottom,top);
}

void setViewport(GLint left,GLint right,GLint bottom,GLint top)
{	
	// define our own function to specify the window as explained--
	glViewport(left,bottom,right-left,top - bottom);
}
