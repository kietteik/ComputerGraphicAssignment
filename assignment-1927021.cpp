// --------------------------------------------------------------------------------------------
//							SUPPORTCLASS.H
// --------------------------------------------------------------------------------------------

#pragma once
#if !defined (_SUPPORT_CLASS)
#define _SUPPORT_CLASS

#include "GLUT/glut.h"

class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Point3& p)
	{
		x = p.x; y = p.y; z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}

};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}
	void set(Color3& c)
	{
		r = c.r; g = c.g; b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}

};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
	void set(float xx, float yy) { x = xx; y = yy; }
	float getX() { return x; }
	float getY() { return y; }
	void draw() {
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}
private:
	float 	x, y;
};
class IntRect
{
public:
	IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void draw() {
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int  getWidth() { return (r - l); }
	int  getHeight() { return (t - b); }
private:
	int	l, r, b, t;
};

class RealRect
{
public:
	RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	float  getWidth() { return (r - l); }
	float  getHeight() { return (t - b); }
	void draw() {
		glRectf(l, b, r, t);
		glFlush();
	};// draw this rectangle using OpenGL
private:
	float	l, r, b, t;
};

class Vector3
{
public:
	float	x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	void flip()
	{
		x = -x; y = -y; z = -z;
	}
	void normalize();
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	Vector3(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};
#endif

// --------------------------------------------------------------------------------------------
//							SUPPORTCLASS.H
// --------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------
//							SUPPORTCLASS.CPP
// --------------------------------------------------------------------------------------------
// #include "supportClass.h"
#include <math.h>


Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x * b.x + y * b.y + z * b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x * x + y * y + z * z);
	x = x / temp;
	y = y / temp;
	z = z / temp;
}
// --------------------------------------------------------------------------------------------
//							SUPPORTCLASS.CPP
// --------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------
//							MESH.H
// --------------------------------------------------------------------------------------------

#pragma once
#if !defined (_MESH_CLASS)
#define _MESH_CLASS
#include "supportClass.h"
#include "stddef.h"


class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID* vert;
	Vector3	facenorm;

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3* pt;

	int		numFaces;
	Face* face;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
	void DrawPoint();
	void SetColor(int colorIdx);
	void drawShape(int option);
	void Draw();
	void CalculateFacesNorm();

	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateCuboid(float	fSizeX, float	fSizeZ, float fSizeY);
	void CreateLuoiDao(float R, float x, float z, float y);
	void CreateCanDao(float R1, float R2, float x1, float x2, float z1, float z2, float y);
	void CreateGiaDo1(float R, float x1, float x2, float x3, float z1, float z2, float y);
	void CreateGiaDo2(float R,float x1,float x2,float z1,float z2,float y);
	void CreateTayNoi(float R,float x, float y);
	void CreateFloorUnit(float x);
	void CreateFloorUnitReflect(float x);
	void DrawReflection(float opacity);

};

#endif

// --------------------------------------------------------------------------------------------
//							MESH.H
// --------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------
//							MESH.CPP
// --------------------------------------------------------------------------------------------


#include "Mesh.h"
#include <math.h>

#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = { { 0.2, 0.3, 0.3 },{ 0.0, 1.0, 0.0 },{ 0.0,  0.0, 1.0 },
{ 1.0, 1.0,  0.0 },{ 1.0, 0.0, 1.0 },{ 0.0, 1.0, 1.0 },
{ 0.3, 0.3, 0.3 },{ 0.5, 0.5, 0.5 },{ 0.9,  0.9, 0.9 },
{ 1.0, 0.5,  0.5 },{ 0.5, 1.0, 0.5 },{ 0.5, 0.5, 1.0 },
{ 0.0, 0.0, 0.0 } };

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight / 2, 0);
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * cos(fAngle * i);
		z = fRadius * sin(fAngle * i);
		y = fHeight / 2;
		pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if (i < nSegment - 1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}
	CalculateFacesNorm();
}

void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
	CalculateFacesNorm();
}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts = 4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces = 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;


	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;


	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;
	
	CalculateFacesNorm();
}

void Mesh::CreateCuboid(float fSizeX, float fSizeZ,float fSizeY) {
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, fSizeZ);
	pt[2].set(fSizeX, fSizeY, -fSizeZ);
	pt[3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set(fSizeX, -fSizeY, fSizeZ);
	pt[6].set(fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 0;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 0;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 0;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 0;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 0;

	CalculateFacesNorm();
}

void Mesh::CreateLuoiDao(float R, float x, float z, float y) {
	float goc1 = atan(z / x);
	float goc2 = acos(R / sqrt(z * z + x * x));
	float alpha = PI - goc1 - goc2;

	int nSegments = 20;

	this->numVerts = ((nSegments + 1) + 2) * 2;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angleInc = alpha / nSegments;

	// Tạo (nSegments + 1) điểm trên hình cung
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = -x - R * cos(angleInc * i);
		pt[idx].z = -R * sin(angleInc * i);
		pt[idx].y = 0;
		idx++;
	}

	// Điểm tiếp theo theo counter clockwise
	pt[idx].x = 0;
	pt[idx].z = -z;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = 0;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	// Nhân đôi số điểm
	for (int i = 0; i < (nSegments + 1) + 2; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = y;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = nSegments +5 ;
	face = new Face[numFaces];
	int nOffset = this->numVerts/2;
	idx = 0;

	for (int i = 0; i < nSegments+2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i+nOffset;
		face[idx].vert[2].vertIndex = i+1+nOffset;
		face[idx].vert[3].vertIndex = i+1;
		idx++;
	}
	//mặt bên cuối cùng
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments +2;
	face[idx].vert[1].vertIndex = nSegments +2+nOffset;
	face[idx].vert[2].vertIndex = nOffset;
	face[idx].vert[3].vertIndex = 0;
	idx++;

	//mặt dưới
	face[idx].nVerts = nSegments+1+2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments+1+2;i++){
		face[idx].vert[i].vertIndex = i;
	}
	idx++;

	//mặt trên
	face[idx].nVerts = nSegments+1+2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments+1+2;i++){
		face[idx].vert[nSegments+1+2 -i-1].vertIndex = i+nOffset;
	}

	this->CalculateFacesNorm();	
}

void Mesh::CreateCanDao(float R1, float R2, float x1, float x2, float z1, float z2, float y){
	int nSegments = 20;

	this->numVerts = ((nSegments+1)*2+4)*2;
	this->pt = new Point3[numVerts];
	int idx = 0;

	float alpha1 = atan((z1+z2)/x1);
	float alpha2 = acos(R1/sqrt(x1*x1+(z1+z2)*(z1+z2)));
	float angle1 = (2*PI - 2*(alpha1+alpha2))/nSegments;

	//Duong cong 1
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = -x1 -R1 * sin(alpha1+alpha2-PI/2+angle1 * i);
		pt[idx].z = -R1 * cos(alpha1+alpha2-PI/2+angle1 * i);
		pt[idx].y = 0;
		idx++;
	}

	// điểm nằm ngoài bên dưới
	pt[idx].x = 0;
	pt[idx].z = z1+z2;
	pt[idx].y = 0;
	idx++;
	// điểm nằm trong bên dưới
	pt[idx].x = 0;
	pt[idx].z = z2;
	pt[idx].y = 0;
	idx++;

	//Cung tròn thứ 2
	float alpha3 = atan((z2)/x2);
	float alpha4 = acos(R1/sqrt(x2*x2+(z2)*(z2)));
	float angle2 = (2*PI - 2*(alpha1+alpha2))/nSegments;
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = x2 +R2 * sin(alpha1+alpha2-PI/2+angle1 * (nSegments-i));
		pt[idx].z = -R2 * cos(alpha1+alpha2-PI/2+angle1 * (nSegments-i));
		pt[idx].y = 0;
		idx++;
	}

	// điểm nằm trong bên trên
	pt[idx].x = 0;
	pt[idx].z = -z2;
	pt[idx].y = 0;
	idx++;
	// điểm nằm ngoài bên trên
	pt[idx].x = 0;
	pt[idx].z = -z1-z2;
	pt[idx].y = 0;
	idx++;

	//Nhan doi diem update depth
	for (int i = 0; i < numVerts/2; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = y;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = nSegments*2 +6 +2*2;
	face = new Face[numFaces];
	idx = 0;
	int nOffset = this->numVerts/2;

	//các mặt bên 
	for (int i = 0; i < nSegments*2 +5; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[3].vertIndex = i;
		face[idx].vert[2].vertIndex = i+nOffset;
		face[idx].vert[1].vertIndex = i+1+nOffset;
		face[idx].vert[0].vertIndex = i+1;
		idx++;
	}
	//mặt bên cuối cùng
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[3].vertIndex = nSegments*2 +5;
	face[idx].vert[2].vertIndex = nSegments*2 +5+nOffset;
	face[idx].vert[1].vertIndex = nOffset;
	face[idx].vert[0].vertIndex = 0;
	idx++;

	//mặt dưới 1
	face[idx].nVerts = nSegments+1+2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments+1;i++){
		face[idx].vert[nSegments+1-i-1].vertIndex = i;
	}
	face[idx].vert[nSegments+1+1].vertIndex = nSegments+1;
	face[idx].vert[nSegments+1].vertIndex = nSegments*2+5;
	idx++;

	//mặt dưới 2
	face[idx].nVerts = nSegments+1+2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments+1;i++){
		face[idx].vert[nSegments+1-i-1].vertIndex = nSegments+1+2+i;
	}
	face[idx].vert[nSegments+1+1].vertIndex = nSegments*2+4;
	face[idx].vert[nSegments+1].vertIndex = nSegments+2;
	idx++;

	//mặt trên 1
	face[idx].nVerts = nSegments+1+2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments+1;i++){
		face[idx].vert[i].vertIndex = i+nOffset;
	}
	face[idx].vert[nSegments+1].vertIndex = nSegments+1+nOffset;
	face[idx].vert[nSegments+1+1].vertIndex = nSegments*2+5+nOffset;
	idx++;

	//mặt trên 2
	face[idx].nVerts = nSegments+1+2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments+1;i++){
		face[idx].vert[i].vertIndex = nSegments+1+2+i+nOffset;
	}
	face[idx].vert[nSegments+1].vertIndex = nSegments*2+4+nOffset;
	face[idx].vert[nSegments+1+1].vertIndex = nSegments+2+nOffset;
	idx++;


	this->CalculateFacesNorm();

}

void Mesh::CreateGiaDo1(float R, float x1, float x2, float x3, float z1, float z2, float y) {
	// Danh sách điểm trên vòng cung bên trái
	float goc11 = atan(x3 / z2);
	float goc12 = acos(R / sqrt(x3 * x3 + z2 * z2));
	float alpha1 = PI - goc11 - goc12;

	int nSegments = 20;

	this->numVerts = ((nSegments + 1) + 4 + (nSegments + 1)) * 2;
	this->pt = new Point3[numVerts];

	int idx = 0;
	float angle = alpha1 / nSegments;

	// Tạo (nSegments + 1) điểm trên hình cung bên trái
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = -x2 - x3 + R * sin(angle * i);
		pt[idx].z = -z1 - z2 - R * cos(angle * i);
		pt[idx].y = 0;
		idx++;
	}

	// Các điểm tiếp theo theo counter clockwise
	// Index = nSegments + 1
	pt[idx].x = -x2;
	pt[idx].z = -z1;
	pt[idx].y = 0;
	idx++;

	// nSegments + 2
	pt[idx].x = 0;
	pt[idx].z = -z1;
	pt[idx].y = 0;
	idx++;

	// nSegments + 3
	pt[idx].x = 0;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	// nSegments + 4
	pt[idx].x = -x1;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	// cung tròn bên phải
	float rW = x1 - (x2 + x3);
	float rH = z1 + z2;
	float goc21 = atan(rW / rH);
	float goc22 = acos(R / sqrt(rW * rW + rH * rH));
	float alpha2 = PI - goc21 - goc22;

	angle = alpha2 / nSegments;

	// Cung tròn 1
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = -x2 - x3 - R * sin(angle * i);
		pt[idx].z = -z1 - z2 - R * cos(angle * i);
		pt[idx].y = 0;
		idx++;
	}

	//nhân đôi số điểm 
	for (int i = 0; i < (nSegments + 1) * 2 + 4; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = y;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = nSegments * 2 + 5+ 6;
	face = new Face[numFaces];
	idx = 0;
	int nOffset = this->numVerts/2;

	//mặt bên từ cung tròn 1
	for (int i = 0; i < nSegments + 4; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		face[idx].vert[1].vertIndex = i+nOffset;
		face[idx].vert[2].vertIndex = i+1+nOffset;
		face[idx].vert[3].vertIndex = i+1;
		idx++;
	}
	
	//mặt bên từ cung tròn 2
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[3].vertIndex = i+nSegments + 5;
		face[idx].vert[2].vertIndex = i+nSegments + 5+nOffset;
		face[idx].vert[1].vertIndex = i+nSegments + 5+1+nOffset;
		face[idx].vert[0].vertIndex = i+nSegments + 5+1;
		idx++;
	}
	//mặt bên cuối cùng
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[3].vertIndex = nSegments*2 + 5;
	face[idx].vert[2].vertIndex = nSegments*2 + 5+nOffset;
	face[idx].vert[1].vertIndex = nSegments+4+nOffset;
	face[idx].vert[0].vertIndex = nSegments+4;
	idx++;

	//mặt dưới 1
	face[idx].nVerts = nSegments+1+2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments+1+1;i++){
		face[idx].vert[i].vertIndex = i;
	}
	face[idx].vert[nSegments+1+1].vertIndex = nSegments+4;
	idx++;

	//mặt dưới 2
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<4;i++){
		face[idx].vert[i].vertIndex = i+nSegments+1;
	}
	idx++;

	//mặt dưới 3
	face[idx].nVerts = nSegments+1+1;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments+1+1;i++){
		face[idx].vert[nSegments+1+1-i-1].vertIndex = i+nSegments+4;
	}
	idx++;

	//mặt trên 1
	face[idx].nVerts = nSegments+1+2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments+1+1;i++){
		face[idx].vert[nSegments+1+2-i-1].vertIndex = i+nOffset;
	}
	face[idx].vert[0].vertIndex = nSegments+4+nOffset;
	idx++;

	// mặt trên 2
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<4;i++){
		face[idx].vert[4-i-1].vertIndex = i+nSegments+1+nOffset;
	}
	idx++;

	// mặt trên 3
	face[idx].nVerts = nSegments+1+1;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments+1+1;i++){
		face[idx].vert[i].vertIndex = i+nSegments+4+nOffset;
	}
	idx++;



	this->CalculateFacesNorm();
	
}

void Mesh::CreateGiaDo2(float R,float x1,float x2,float z1,float z2,float y){
	int nSegments = 20;
	this->numVerts = (nSegments+4)*2;
	this->pt = new Point3[numVerts];
	int idx=0;
	float alpha1 = atan(x2/z2);
	float alpha2 = acos(R / sqrt(x2 * x2 + z2 * z2));
	float alpha3 = atan((x1-x2)/(z1+z2));
	float alpha4 = acos(R/sqrt((x1-x2)*(x1-x2)+(z1+z2)+(z1+z2)));
	float angle = (2*PI-(alpha1+alpha2+alpha3+alpha4))/nSegments;

	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = -(x1-x2)+R * cos(-PI/2+alpha3+alpha4+angle * i);
		pt[idx].z = -(z1+z2)-R * sin(-PI/2+alpha3+alpha4+angle * i);
		pt[idx].y = 0;
		idx++;
	}

	pt[idx].x = -x1;
	pt[idx].z = -z1;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = -x1;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	pt[idx].x = 0;
	pt[idx].z = 0;
	pt[idx].y = 0;
	idx++;

	//Nhan doi diem update depth
	for (int i = 0; i < numVerts/2; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = y;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = nSegments+4+4;
	face = new Face[numFaces];
	idx = 0;
	int nOffset = this->numVerts/2;

	//nSegments 1
	for (int i = 0; i < nSegments+3; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[3].vertIndex = i;
		face[idx].vert[2].vertIndex = i+nOffset;
		face[idx].vert[1].vertIndex = i+1+nOffset;
		face[idx].vert[0].vertIndex = i+1;
		idx++;
	}

	// măt bên còn lại
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[3].vertIndex = nSegments+3;
	face[idx].vert[2].vertIndex = nSegments+nOffset+3;
	face[idx].vert[1].vertIndex = nOffset;
	face[idx].vert[0].vertIndex = 0;
	idx++;

	//mặt dưới 1
	face[idx].nVerts = nSegments+1+1;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments+1+1;i++){
		face[idx].vert[nSegments+1+1-i-1].vertIndex = i;
	}
	idx++;
	//mặt dưới 2
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[3].vertIndex = nSegments+1;
	face[idx].vert[2].vertIndex = nSegments+2;
	face[idx].vert[1].vertIndex = nSegments+3;
	face[idx].vert[0].vertIndex = 0;
	idx++;

	// //mặt trên 1
	face[idx].nVerts = nSegments+1+1;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments+1+1;i++){
		face[idx].vert[i].vertIndex = i+nOffset;
	}
	idx++;

	//mặt dưới 2
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegments+1+nOffset;
	face[idx].vert[1].vertIndex = nSegments+2+nOffset;
	face[idx].vert[2].vertIndex = nSegments+3+nOffset;
	face[idx].vert[3].vertIndex = 0+nOffset;
	idx++;

	this->CalculateFacesNorm();

}

void Mesh::CreateTayNoi(float R, float x, float y) {
	
	int nSegments = 30;

	this->numVerts = (nSegments+1)*4;
	this->pt = new Point3[numVerts];
	int idx = 0;

	float angle = PI /  nSegments;

	//Cung tròn 1
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = R - R * cos(angle * i);
		pt[idx].z = R * sin(angle * i);
		pt[idx].y = 0;
		idx++;
	}
	//Cung tròn 2
	for (int i = 0; i <= nSegments; i++) {
		pt[idx].x = R - R * cos(PI+(angle * i));
		pt[idx].z = -x + R * sin(PI+(angle * i));
		pt[idx].y = 0;
		idx++;
	}

	int  nOffset = numVerts/2;
	// Khúc này nhân đôi số điểm (đổi depth của những điểm cũ ==> điểm mới)
	for (int i = 0; i < numVerts/2; i++) {
		pt[idx].x = pt[i].x;
		pt[idx].z = pt[i].z;
		pt[idx].y = y;
		idx++;
	}

	// Tạo các lưới đa giác (faces)
	numFaces = 4 + nSegments*2;
	face = new Face[numFaces];
	idx = 0;

	//mặt bên cung tròn 1
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[3].vertIndex = i;
		face[idx].vert[2].vertIndex = i+nOffset;
		face[idx].vert[1].vertIndex = i+1+nOffset;
		face[idx].vert[0].vertIndex = i+1;
		idx++;
	}
	//mặt bên 1
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[3].vertIndex = nSegments;
	face[idx].vert[2].vertIndex = nSegments+nOffset;
	face[idx].vert[1].vertIndex = nSegments+1+nOffset;
	face[idx].vert[0].vertIndex = nSegments+1;
	idx++;
	//mặt bên cung tr 2
	for (int i = 0; i < nSegments; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[3].vertIndex = i +nSegments;
		face[idx].vert[2].vertIndex = i+nOffset+nSegments;
		face[idx].vert[1].vertIndex = i+1+nOffset+nSegments;
		face[idx].vert[0].vertIndex = i+1+nSegments;
		idx++;
	}
	//mặt bên 2
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[3].vertIndex = nSegments*2;
	face[idx].vert[2].vertIndex = nSegments*2+nOffset;
	face[idx].vert[1].vertIndex = 0+nOffset;
	face[idx].vert[0].vertIndex = 0;
	idx++;

	//mặt dưới
	face[idx].nVerts = nSegments*2+2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments*2+2;i++){
		face[idx].vert[nSegments*2+2-i-1].vertIndex = i;
	}
	idx++;

	//mặt trên
	face[idx].nVerts = nSegments*2+2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (int i=0;i<nSegments*2+2;i++){
		face[idx].vert[i].vertIndex = i+nOffset;
	}
	this->CalculateFacesNorm();
}

void Mesh::CreateFloorUnit(float x){
	int idx;
	numVerts = 20;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(x/3, 0,0);
	pt[2].set(2*x/3, 0, 0);
	pt[3].set(x, 0, 0);
	pt[4].set(0, 0, -x/3);
	pt[5].set(0.5*x, 0, -0.5*x);
	pt[6].set(0.8*x, 0, -0.4*x);
	pt[7].set(x, 0, -x/3);
	pt[8].set(0, 0, -2*x/3);
	pt[9].set(0.4*x, 0, -0.8*x);
	pt[10].set(0.9*x, 0, -0.7*x);
	pt[11].set(x, 0, -2*x/3);
	pt[12].set(0, 0, -x);
	pt[13].set(x/3, 0, -x);
	pt[14].set(2*x/3, 0, -x);
	pt[15].set(x, 0, -x);
	pt[16].set(0.7*x, 0, -0.9*x);
	pt[17].set(0.75*x, 0, -0.75*x);

	numFaces = 5;
	face = new Face[numFaces];
	idx = 0;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 1;
	face[idx].vert[1].vertIndex = 2;
	face[idx].vert[2].vertIndex = 6;
	face[idx].vert[3].vertIndex = 5;
	idx++;
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4;
	face[idx].vert[1].vertIndex = 5;
	face[idx].vert[2].vertIndex = 9;
	face[idx].vert[3].vertIndex = 8;
	idx++;
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 6;
	face[idx].vert[1].vertIndex = 7;
	face[idx].vert[2].vertIndex = 11;
	face[idx].vert[3].vertIndex = 10;
	idx++;
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 9;
	face[idx].vert[1].vertIndex = 16;
	face[idx].vert[2].vertIndex = 14;
	face[idx].vert[3].vertIndex = 13;
	idx++;
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 17;
	face[idx].vert[1].vertIndex = 10;
	face[idx].vert[2].vertIndex = 15;
	face[idx].vert[3].vertIndex = 16;
	idx++;

	CalculateFacesNorm();
}

void Mesh::CreateFloorUnitReflect(float x){
	int idx;
	numVerts = 20;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(x/3, 0,0);
	pt[2].set(2*x/3, 0, 0);
	pt[3].set(x, 0, 0);
	pt[4].set(0, 0, -x/3);
	pt[5].set(0.5*x, 0, -0.5*x);
	pt[6].set(0.8*x, 0, -0.4*x);
	pt[7].set(x, 0, -x/3);
	pt[8].set(0, 0, -2*x/3);
	pt[9].set(0.4*x, 0, -0.8*x);
	pt[10].set(0.9*x, 0, -0.7*x);
	pt[11].set(x, 0, -2*x/3);
	pt[12].set(0, 0, -x);
	pt[13].set(x/3, 0, -x);
	pt[14].set(2*x/3, 0, -x);
	pt[15].set(x, 0, -x);
	pt[16].set(0.7*x, 0, -0.9*x);
	pt[17].set(0.75*x, 0, -0.75*x);

	numFaces = 7;
	face = new Face[numFaces];
	idx = 0;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 1;
	face[idx].vert[2].vertIndex = 5;
	face[idx].vert[3].vertIndex = 4;
	idx++;
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 2;
	face[idx].vert[1].vertIndex = 3;
	face[idx].vert[2].vertIndex = 7;
	face[idx].vert[3].vertIndex = 6;
	idx++;
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 6;
	face[idx].vert[1].vertIndex = 10;
	face[idx].vert[2].vertIndex = 17;
	face[idx].vert[3].vertIndex = 5;
	idx++;
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 5;
	face[idx].vert[1].vertIndex = 17;
	face[idx].vert[2].vertIndex = 16;
	face[idx].vert[3].vertIndex = 9;
	idx++;
	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 10;
	face[idx].vert[1].vertIndex = 11;
	face[idx].vert[2].vertIndex = 15;
	idx++;
	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 16;
	face[idx].vert[1].vertIndex = 15;
	face[idx].vert[2].vertIndex = 14;
	idx++;
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 8;
	face[idx].vert[1].vertIndex = 9;
	face[idx].vert[2].vertIndex = 13;
	face[idx].vert[3].vertIndex = 12;
	idx++;

	CalculateFacesNorm();
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}


void Mesh::Draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++){
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++){
			int		iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawReflection(float opacity) {
	glDisable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++){
		glBegin(GL_POLYGON);
		glColor4f(200.0/255, 200.0/255, 1, opacity);
		for (int v = 0; v < face[f].nVerts; v++){
			int		iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
	glEnable(GL_LIGHTING);
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			// ic = f % COLORNUM;
			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawPoint() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPointSize(3);
	glColor3f(1, 0, 0);
	for (int f = 0; f < numVerts; f++) {
		glBegin(GL_POINTS);
		glVertex3f(pt[f].x, pt[f].y, pt[f].z);
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx){
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Mesh::drawShape(int option){
	if (option==1){
		this->DrawWireframe();
	}
	else{
		this->Draw();
	}
}


void Mesh::CalculateFacesNorm(){
	float mx,my,mz;
	int idx,next;
	for (int f=0;f<numFaces;f++){
		mx=0;
		my=0;
		mz=0;
		for (int v=0;v<face[f].nVerts;v++){
			idx =v;
			next = (idx+1)%face[f].nVerts;

			int p1=face[f].vert[idx].vertIndex;
			int p2=face[f].vert[next].vertIndex;

			mx = mx +(pt[p1].y-pt[p2].y)*(pt[p1].z+pt[p2].z);
			my = my +(pt[p1].z-pt[p2].z)*(pt[p1].x+pt[p2].x);
			mz = mz +(pt[p1].x-pt[p2].x)*(pt[p1].y+pt[p2].y);
		}
		face[f].facenorm.set(mx,my,mz);
		face[f].facenorm.normalize();
	}
}

// --------------------------------------------------------------------------------------------
//							MESH.CPP
// --------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------
//								MAINFILE
// --------------------------------------------------------------------------------------------
//Nguyễn Tuấn Kiệt - 1927021

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
Mesh	floorUnit;
Mesh	floorUnitReflect;
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

int find_intersection(double x0, double y0, double r0,
                               double x1, double y1, double r1)
{
  double x2, y2;
  double a, dx, dy, d, h, rx, ry;
  dx = x1 - x0;
  dy = y1 - y0;
  d = hypot(dx,dy); // Suggested by Keith Briggs

  if (d > (r0 + r1))
  {
    return 0;
  }
  if (d < fabs(r0 - r1))
  {
    return 0;
  }

  a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;
  x2 = x0 + (dx * a/d);
  y2 = y0 + (dy * a/d);
  h = sqrt((r0*r0) - (a*a));

  rx = -dy * (h/d);
  ry = dx * (h/d);

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

void setupLight1(){
	GLfloat	light1Diffuse[] = { 1.2f, 1.2f, 1.2f, 1.2f };
	GLfloat	light1Specular[] = { 0.85f, 0.85f, 0.85f, 0.85f };
	GLfloat	light1Ambient[] = { 0.3f, 0.3f, 0.3f, 0.3f };
	GLfloat light1Position[] = { 75, 100.0f, 20, 0 };

	glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}
void setupLight2(){

	GLfloat	light2Diffuse[] = { 0.6f, 0.6f, 0.6f, 0.6f };
	GLfloat	light2Specular[] = { 0.7f, 0.7f, 0.7f, 0.7f };
	GLfloat	light2Ambient[] = { 0.2f, 0.2f, 0.2f, 0.2f };
	GLfloat light2Position[] = { -75.0f, 60.0f, -80.0f, 0 };

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

	//ĐIỂM ĐẦU TAY NỐI
	tn1.set(2.1- cos((rotateAngle*PI)/180),2.5 -sin((rotateAngle*PI)/180),-0.5);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(tn1.x,tn1.y,tn1.z);
	glEnd();

	//ĐIỂM CUỐI TAY NỐI
	find_intersection(tn1.x,tn1.y,1,-0.6,1.3,1.6);

	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(tn2.x,tn2.y,tn2.z);
	glEnd();

	//MẶT ĐÁY
	glPushMatrix();
	glTranslatef(0,0.25,0);
	GLfloat matdayAmbient[] = { 8.0f,0.15f,0.15f, 0.8f};
	GLfloat matdayDiffuse[] = { 0.3f,0.15f,0.15f, 0.5f };
	GLfloat matdaySpecular[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat matdayShine = 80.0;
	setupMaterial(matdayAmbient, matdayDiffuse, matdaySpecular, matdayShine);
	cuboid.drawShape(drawChoice);
	glPopMatrix();

	// GIÁ ĐỠ 1
	glPushMatrix();
	glTranslatef(0,0.5,0.5);
	glTranslatef(-3,0,0);
	glRotatef(90,1,0,0);
	glRotatef(180,0,0,1);
	GLfloat giado1Ambient[] = { 0.82, 0.52, 0.34, 0.8 };
	GLfloat giado1Diffuse[] = { 0.6, 0.4, 0.2, 0.21};
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
	GLfloat giado2Ambient[] = { 0.82, 0.52, 0.34, 0.8 };
	GLfloat giado2Diffuse[] = { 0.6, 0.4, 0.2, 0.21};
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
	GLfloat luoidaoAmbient[] = { 0.12, 0.1, 0.85, 1.0 };
	GLfloat luoidaoDiffuse[] = { 0.12, 0.1, 0.6, 0.5 };
	GLfloat luoidaoSpecular[] = { 0.9, 0.9, 0.9, 1.0 };
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
	GLfloat candaoAmbient[] = { 0.2, 1, 0.23, 1.0 };
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
	GLfloat taynoiAmbient[] = { 1, 0.15, 0.3, 1.0 };
	GLfloat taynoiDiffuse[] = { 0.4, 0.2, 0.2, 1.0 };
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
	GLfloat coinSpecular[] = { 0.1, 0.1, 0.1, 1.0 };
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

void drawGround(float unitWidth4,float groundWidth){
	// int groundWidth = (int) groundWidth/unitWidth4;
	float unitWidth = unitWidth4/2;
	for (int x=0;x<groundWidth;x++){
		for (int z=0;z<groundWidth;z++){
			glPushMatrix();	
			glTranslatef(unitWidth4*(x-groundWidth/2),0,unitWidth4*(z-groundWidth/2));
			glRotatef(0,0,1,0);
			glTranslatef(-unitWidth/2,0,-unitWidth/2);
			floorUnit.drawShape(drawChoice);
			glDisable(GL_STENCIL_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			if (!drawChoice){
				floorUnitReflect.DrawReflection(0.5f);
			}
			glDisable(GL_BLEND);
			glPopMatrix();

			glPushMatrix();	
			glTranslatef(unitWidth4*(x-groundWidth/2)+unitWidth,0,unitWidth4*(z-groundWidth/2));
			glRotatef(90,0,1,0);
			glTranslatef(-unitWidth/2,0,-unitWidth/2);
			floorUnit.drawShape(drawChoice);
			glDisable(GL_STENCIL_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			if (!drawChoice){
				floorUnitReflect.DrawReflection(0.5f);
			}
			glDisable(GL_BLEND);
			glPopMatrix();

			glPushMatrix();	
			glTranslatef(unitWidth4*(x-groundWidth/2)+unitWidth,0,unitWidth4*(z-groundWidth/2)-unitWidth);
			glRotatef(180,0,1,0);
			glTranslatef(-unitWidth/2,0,-unitWidth/2);
			floorUnit.drawShape(drawChoice);
			glDisable(GL_STENCIL_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			if (!drawChoice){
				floorUnitReflect.DrawReflection(0.5f);
			}
			glDisable(GL_BLEND);
			glPopMatrix();

			glPushMatrix();	
			glTranslatef(unitWidth4*(x-groundWidth/2),0,unitWidth4*(z-groundWidth/2)-unitWidth);
			glRotatef(-90,0,1,0);
			glTranslatef(-unitWidth/2,0,-unitWidth/2);
			floorUnit.drawShape(drawChoice);
			glDisable(GL_STENCIL_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			if (!drawChoice){
				floorUnitReflect.DrawReflection(0.5f);
			}
			glDisable(GL_BLEND);
			glPopMatrix();

		}
	}
	// glPushMatrix();
	// glDisable(GL_STENCIL_TEST);
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// if (drawChoice){
	// 	floorUnitReflect.DrawReflection(0.5f);
	// }else{
	// 	floorUnitReflect.DrawWireframe();
	// }
	// glDisable(GL_BLEND);
	// glPopMatrix();
}

void mydisplay2(){
	// glColor3f(0,0,0);
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

	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	// //glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	glPushMatrix();
	glScaled(1,-1,1);
	setupLight1();
	if (setLight2==true){
		setupLight2();
	}else{
		glDisable(GL_LIGHT2);
	}

	if (drawChoice){
		glDisable(GL_LIGHTING);
	}
	drawAllShapes();
	glPopMatrix();

	GLfloat coinAmbient[] = { 153.0/255, 153.0/255, 153.0/255, 1.0 };
	GLfloat coinDiffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat coinSpecular[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat coinShine = 50.0;
	setupMaterial(coinAmbient, coinDiffuse, coinSpecular, coinShine);
	drawGround(4,20);
	// floorUnitReflect.DrawReflection(0.5f);

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
	cout<<"1,2 	: Xoay can dao"<<endl;
	cout<<"W,w 	: Chuyen doi qua lai giua che do khung day va to mau"<<endl;
	cout<<"V,v 	: Chuyen doi qua lai giua hai che do nhin khac nhau"<<endl;
	cout<<"+	: Tang khoang cach camera"<<endl;
	cout<<"-	: Giam khoang cach camera"<<endl;
	cout<<"up	: Tang chieu cao camera"<<endl;
	cout<<"down	: Giam chieu cao camera"<<endl;
	cout<<"->	: Quay camera theo chieu kim dong ho"<<endl;
	cout<<"<-	: Quay camera nguoc chieu kim dong ho"<<endl;


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
	cuboid.CreateCuboid(4, 1.2, 0.25);
	coin.CreateCylinder(30,1.1,0.15);
	floorUnit.CreateFloorUnit(2);
	floorUnitReflect.CreateFloorUnitReflect(2);
	myInit();
	glutDisplayFunc(mydisplay2);
	glutSpecialFunc(mySpecialFunc);
	glutKeyboardFunc(myKeyboardFunc);
	glutMainLoop();
	return 0;
}

// --------------------------------------------------------------------------------------------
//							MAINFILE
// --------------------------------------------------------------------------------------------

