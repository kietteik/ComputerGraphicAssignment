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

// void Mesh::CalculateFacesNorm() {
// 	float mx, my, mz;
// 	int idx, next;
// 	for (int f = 0; f < numFaces; f++) {
// 		mx = 0;
// 		my = 0;
// 		mz = 0;
// 		for (int v = 0; v < face[f].nVerts; v++) {
// 			idx = v;
// 			next = (idx + 1) % face[f].nVerts;
// 			int p1 = face[f].vert[idx].vertIndex;
// 			int p2 = face[f].vert[next].vertIndex;
// 			mx = mx + (pt[p1].y - pt[p2].y) * (pt[p1].z + pt[p2].z);
// 			my = my + (pt[p1].z - pt[p2].z) * (pt[p1].x + pt[p2].x);
// 			mz = mz + (pt[p1].x - pt[p2].x) * (pt[p1].y + pt[p2].y);
// 		}
// 		face[f].facenorm.set(mx, my, mz);
// 		face[f].facenorm.normalize();
// 	}
// }
