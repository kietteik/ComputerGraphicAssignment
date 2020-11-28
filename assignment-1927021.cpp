// Bai3.cpp : Defines the entry point for the console application.
//

#define PI			3.1415926
#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"



using namespace std;

int		screenWidth = 1200;
int		screenHeight = 600;

Mesh	tetrahedron;
Mesh	cube;
Mesh	cylinder;
Mesh	luoidao;
Mesh	candao;
Mesh	giado1;
Mesh	giado2;
Mesh	taynoi;
Mesh	cuboid;
Mesh	coin;
float	angle;
float 	rotateAngle;

Point3 	tn1;
Point3 	tn2;
Point3 	O1;
Point3 	O2;
Point3 	O3;

float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

bool	choiceDisplay = false;
bool 	drawChoice;
int		nChoice = 1;
bool 	setLight2=true;
void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
}

int circle_circle_intersection(double x0, double y0, double r0,
                               double x1, double y1, double r1)
{
  double a, dx, dy, d, h, rx, ry;
  double x2, y2;

  /* dx and dy are the vertical and horizontal distances between
   * the circle centers.
   */
  dx = x1 - x0;
  dy = y1 - y0;

  /* Determine the straight-line distance between the centers. */
  //d = sqrt((dy*dy) + (dx*dx));
  d = hypot(dx,dy); // Suggested by Keith Briggs

  /* Check for solvability. */
  if (d > (r0 + r1))
  {
    /* no solution. circles do not intersect. */
    return 0;
  }
  if (d < fabs(r0 - r1))
  {
    /* no solution. one circle is contained in the other */
    return 0;
  }

  /* 'point 2' is the point where the line through the circle
   * intersection points crosses the line between the circle
   * centers.  
   */

  /* Determine the distance from point 0 to point 2. */
  a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;

  /* Determine the coordinates of point 2. */
  x2 = x0 + (dx * a/d);
  y2 = y0 + (dy * a/d);

  /* Determine the distance from point 2 to either of the
   * intersection points.
   */
  h = sqrt((r0*r0) - (a*a));

  /* Now determine the offsets of the intersection points from
   * point 2.
   */
  rx = -dy * (h/d);
  ry = dx * (h/d);

  /* Determine the absolute intersection points. */
  float xi = x2 + rx;
  float xi_prime = x2 - rx;
  float yi = y2 + ry;
  float yi_prime = y2 - ry;

  if (yi < yi_prime){
	  tn2.x = xi;
	  tn2.y = yi;
  }
  else{
	  tn2.x = xi_prime;
	  tn2.y = yi_prime;
  }

  return 1;
}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);

	glRotatef(angle, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, screenWidth / 2, screenHeight);

	drawAxis();

	glColor3f(0, 0, 0);
	// if (nChoice == 1)
	// 	tetrahedron.DrawWireframe();
	// else if (nChoice == 2)
	// 	cube.DrawWireframe();
	// else if (nChoice == 3)
	// 	cylinder.DrawWireframe();
	// else if (nChoice == 4)
	// 	luoidao.DrawPoint();
	// else if (nChoice == 5)
	// 	candao.DrawPoint();
	// else if (nChoice == 6)
	// 	giado1.DrawPoint();
	// else if (nChoice == 7)
	// 	giado2.DrawPoint();
	// else if (nChoice == 8)
	// 	taynoi.DrawWireframe();
	// else if (nChoice == 9)
	// 	cuboid.DrawWireframe();
	cuboid.DrawWireframe();

	glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);

	drawAxis();
	// if (nChoice == 1)
	// 	tetrahedron.DrawColor();
	// else if (nChoice == 2)
	// 	cube.DrawColor();
	// else if (nChoice == 3)
	// 	cylinder.DrawColor();
	// else if (nChoice == 4)
	// 	luoidao.DrawColor();
	// else if (nChoice == 5)
	// 	candao.DrawColor();
	// else if (nChoice == 6)
	// 	giado1.DrawColor();
	// else if (nChoice == 7)
	// 	giado2.DrawColor();
	// else if (nChoice == 8)
	// 	taynoi.DrawColor();
	// else if (nChoice == 9)
	// 	cuboid.DrawColor();

	cuboid.DrawColor();

	glFlush();
	glutSwapBuffers();
}

void setupLight1(){


	GLfloat	light1Diffuse[] = { 1.3f, 1.3f, 1.3f, 1.3f };
	GLfloat	light1Specular[] = { 0.2f, 0.2f, 0.2f, 0.2f };
	GLfloat	light1Ambient[] = { 0.9f, 0.9f, 0.9f, 0.9f };
	GLfloat light1Position[] = { -75, 100.0f, 75, 0 };

	glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}
void setupLight2(){

	GLfloat	light2Diffuse[] = { 0.3f, 0.3f, 0.3f, 0.3f };
	GLfloat	light2Specular[] = { 0.7f, 0.7f, 0.7f, 0.7f };
	GLfloat	light2Ambient[] = { 0.1f, 0.1f, 0.1f, 0.1f };
	GLfloat light2Position[] = { -75.0f, 60.0f, -80.0f, 1 };

	glLightfv(GL_LIGHT2, GL_POSITION, light2Position);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Diffuse);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light2Ambient);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2Specular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
}

void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}


void drawAllShapes(){
	glColor3f(0, 0, 0);

	//điểm đầu tay nối
	tn1.set(2.1- cos((rotateAngle*PI)/180),2.5 -sin((rotateAngle*PI)/180),-0.5);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(tn1.x,tn1.y,tn1.z);
	glEnd();

	//điểm cuối tay nối
	circle_circle_intersection(tn1.x,tn1.y,1,-0.6,1.3,1.6);

	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(tn2.x,tn2.y,tn2.z);
	glEnd();

	//MẶT ĐÁY
	glPushMatrix();
	glTranslatef(0,0.25,0);
	GLfloat matdayAmbient[] = { 0.1, 0.2, 0.2, 0.8};
	GLfloat matdayDiffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat matdaySpecular[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat matdayShine = 50.0;
	setupMaterial(matdayAmbient, matdayDiffuse, matdaySpecular, matdayShine);
	cuboid.drawShape(drawChoice);
	glPopMatrix();

	// GIÁ ĐỠ 1
	glPushMatrix();
	glTranslatef(0,0.5,0.5);
	glTranslatef(-3,0,0);
	glRotatef(90,1,0,0);
	glRotatef(180,0,0,1);
	GLfloat giado1Ambient[] = { 0.6, 0.1, 0.1, 1.0 };
	GLfloat giado1Diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat giado1Specular[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat giado1Shine = 50.0;
	setupMaterial(giado1Ambient, giado1Diffuse, giado1Specular, giado1Shine);
	giado1.drawShape(drawChoice);
	glPopMatrix();

	// GIÁ ĐỠ 2
	glPushMatrix();
	glTranslatef(1.4+2,0,0);
	glTranslatef(0,0.5,0);
	glRotatef(90,1,0,0);
	GLfloat giado2Ambient[] = { 0.6, 0.1, 0.1, 1.0 };
	GLfloat giado2Diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat giado2Specular[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat giado2Shine = 50.0;
	setupMaterial(giado2Ambient, giado2Diffuse, giado2Specular, giado2Shine);
	giado2.drawShape(drawChoice);
	glPopMatrix();

	//LƯỠI DAO
	glPushMatrix();
	glTranslatef(-0.6,1.3,0);
	glRotatef(atan((tn2.y-1.3)/(tn2.x+0.6))*180/PI,0,0,1); //xoay
	glTranslatef(0.6,-1.3,0); //Mang về tâm
	glTranslatef(1.4,1,-0.5);
	glRotatef(90,1,0,0);
	GLfloat luoidaoAmbient[] = { 0, 0.2, 0.4, 1.0 };
	GLfloat luoidaoDiffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat luoidaoSpecular[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat luoidaoShine = 50.0;
	setupMaterial(luoidaoAmbient, luoidaoDiffuse, luoidaoSpecular, luoidaoShine);
	luoidao.drawShape(drawChoice);
	glPopMatrix();

	//CÁN DAO
	glPushMatrix();
	glTranslatef(2.1,2.5,-0.5); //Mang đi
	glRotatef(rotateAngle,0,0,1); //xoay
	glTranslatef(4.5-1,0,0); //Mang về trục
	glRotatef(90,1,0,0);
	GLfloat candaoAmbient[] = { 0, 0.2, 0.4, 1.0 };
	GLfloat candaoDiffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat candaoSpecular[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat candaoShine = 50.0;
	setupMaterial(candaoAmbient, candaoDiffuse, candaoSpecular, candaoShine);
	candao.drawShape(drawChoice);
	glPopMatrix();
	

	//TAY NỐI
	glPushMatrix();
	glTranslatef((tn2.x+tn1.x)/2,(tn2.y+tn1.y)/2,0);
	glRotatef(atan((tn2.y-tn1.y)/(tn2.x-tn1.x))*180/PI,0,0,1); //xoay
	glRotatef(90,0,0,1);
	glTranslatef(-0.3,-0.5,0);
	glRotatef(90,1,0,0);
	GLfloat taynoiAmbient[] = { 0.6, 0.4, 0.3, 1.0 };
	GLfloat taynoiDiffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat taynoiSpecular[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat taynoiShine = 50.0;
	setupMaterial(taynoiAmbient, taynoiDiffuse, taynoiSpecular, taynoiShine);
	taynoi.drawShape(drawChoice);
	glPopMatrix();

	//CÁC ĐIỂM TÂM
	glPushMatrix();
	glTranslatef(-0.6,1.3,0);
	glRotatef(90,1,0,0);
	GLfloat coinAmbient[] = { 0, 0, 0, 1.0 };
	GLfloat coinDiffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat coinSpecular[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat coinShine = 50.0;
	setupMaterial(coinAmbient, coinDiffuse, coinSpecular, coinShine);
	coin.drawShape(drawChoice);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.1,2.5,0);
	glRotatef(90,1,0,0);
	coin.drawShape(drawChoice);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(tn1.x,tn1.y,0);
	glRotatef(90,1,0,0);
	coin.drawShape(drawChoice);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(tn2.x,tn2.y,0);
	glRotatef(90,1,0,0);
	coin.drawShape(drawChoice);
	glPopMatrix();
}


void drawLucGiac(float x, float y, float z, float R, float alpha)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(-60 * PI / 180), y, z + R * sin(-60 * PI / 180));
	glVertex3f(x + R * cos(0), y, z + R * sin(0));
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R * sin(60 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
	glBegin(GL_QUADS);
	glColor4f(0.5,1,1, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R * sin(60 * PI / 180));
	glVertex3f(x + R * cos(120 * PI / 180), y, z + R * sin(120 * PI / 180));
	glVertex3f(x + R * cos(180 * PI / 180), y, z + R * sin(180 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
	glBegin(GL_QUADS);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(180 * PI / 180), y, z + R * sin(180 * PI / 180));
	glVertex3f(x + R * cos(240 * PI / 180), y, z + R * sin(240 * PI / 180));
	glVertex3f(x + R * cos(300 * PI / 180), y, z + R * sin(300 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
}

void drawNen(float alpha)
{
	float y = 0;
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	float d = 0.7, R = d / cos(PI / 6);
	int i = 0;
	for (float x = -30; x < 30; x += R + R * cos(PI / 3))
	{
		float z = (i % 2 == 0) ? -20 : (-20 - d);
		for (; z < 20; z += 2 * d)
			drawLucGiac(x, y, z, R, alpha);
		i++;
	}
	glEnable(GL_LIGHTING);
}

void drawGround(){
	glPushMatrix();
	glRotatef(30, 0, 1, 0);
	glDisable(GL_STENCIL_TEST);
	// Blend the floor onto the screen
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawNen(1.0f);
	drawNen(0.5f);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void mydisplay2(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera_Z= sin(camera_angle)*camera_dis;
	camera_X= cos(camera_angle)*camera_dis;
	camera_Y=camera_height;

	if (choiceDisplay==0){
		if (camera_dis == 0)
		{
			gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, sinf(camera_angle * PI / 180), 0, cosf(camera_angle * PI / 180));
		}
		else
		{
			gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);
		}
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, screenWidth, screenHeight);

	setupLight1();
	if (setLight2==true){
		setupLight2();
	}else{
		glDisable(GL_LIGHT2);
	}

	if (drawChoice){
		glDisable(GL_LIGHTING);
	}

	drawAxis();
	drawAllShapes();
	drawGround();
	glPushMatrix();
	glRotatef(180,1,0,0);
	drawAllShapes();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();

}


void myInit()
{
	rotateAngle = 12;
	drawChoice = 0;

	lookAt_X=0;
	lookAt_Y=2;
	lookAt_Z=0;

	camera_angle=45;
	camera_height=5;
	camera_dis=10;

	float	fHalfSize = 8;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	// glShadeModel(GL_SMOOTH);
	// glDepthFunc(GL_LEQUAL);
	// //glEnable(GL_COLOR_MATERIAL);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (choiceDisplay==0){gluPerspective(45, 2.2, 2.5, 1000);}
	else{glOrtho(-fHalfSize, fHalfSize, -fHalfSize/2, fHalfSize/2, -1000, 1000);
			gluLookAt(0,0,10,0,0,0,0,1,0);}

	

}

void mySpecialFunc(int key, int x, int y) {
	if (choiceDisplay==0){
		if (key == GLUT_KEY_LEFT) {
			camera_angle -= 0.1;
		}
		else if (key == GLUT_KEY_RIGHT) {
			camera_angle += 0.1;
		}
		else if (key == GLUT_KEY_UP) {
			camera_height += 1;
		}
		else if (key == GLUT_KEY_DOWN) {
			camera_height -= 1;
		}
	}

	glutPostRedisplay();
}

void myKeyboardFunc(unsigned char key,int x, int y){
	switch (key)
	{
	case '1':
		if (rotateAngle==45){
			rotateAngle=45;
		}
		else{
		rotateAngle += 1;
		}
		break;
	case '2':
		if (rotateAngle==-7){
			rotateAngle=-7;
		}
		else{
			rotateAngle -= 1;
		}
		break;
	case 'w':
	case 'W':
		drawChoice=!drawChoice;
		break;
	case 'v':
	case 'V':
		choiceDisplay=!choiceDisplay;
		myInit();
		break;
	case 'd':
	case 'D':
		setLight2=!setLight2;
		break;
	case '+':
		camera_dis += 1;
		break;
	case '-':
		camera_dis -= 1;
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	// cout << "1. Tetrahedron" << endl;
	// cout << "2. Cube" << endl;
	// cout << "3. Cylinder" << endl;
	// cout << "4. Shape 1" << endl;
	// cout << "5. Shape 2" << endl;
	// cout << "6. Shape 3" << endl;
	// cout << "7. Shape 4" << endl;
	// cout << "8. Shape 5" << endl;
	// cout << "9. CreateCuboid" << endl;
	// cout << "Input the choice: " << endl;
	// cin >> nChoice;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Nguyễn Tuấn Kiệt - 1927021"); // open the screen window

	tetrahedron.CreateTetrahedron();
	cube.CreateCube(1);
	cylinder.CreateCylinder(20, 3.8, 1);
	luoidao.CreateLuoiDao(0.45, 4, 0.7, 0.5);
	candao.CreateCanDao(0.3, 0.25, 4.5, 1, 0.14, 0.22, 0.5);
	giado1.CreateGiaDo1(0.3, 3, 2, 0.4, 0.5, 0.3, 0.5);
	giado2.CreateGiaDo2(0.3,1.4,0.1,1.4,0.6,0.5);
	taynoi.CreateTayNoi(0.3, 1, 0.5);
	cuboid.CreateCuboid(5, 2, 0.25);
	coin.CreateCylinder(30,1.2,0.1);
	myInit();
	glutDisplayFunc(mydisplay2);
	glutSpecialFunc(mySpecialFunc);
	glutKeyboardFunc(myKeyboardFunc);

	glutMainLoop();
	return 0;
}


