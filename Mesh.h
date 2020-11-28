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
};

#endif