#include "mesh.h"

//CONSTRUCTOR
Mesh::Mesh() {
	int vertices = SIZE * 9;
	vertexData = new GLfloat[vertices];
	colorData = new GLfloat[vertices];
	tri = new Triangle[SIZE];
	
	for(int i=0; i<SIZE; i+=9) {
		
		vertexData[i] = -1.f + (float)i;
		vertexData[i+1] = 1.f + (float)i;
		vertexData[i+2] = 0.0f + (float)i;
		vertexData[i+3] = 1.f + (float)i;
		vertexData[i+4] = 1.f + (float)i;
		vertexData[i+5] = 0.0f + (float)i;
		vertexData[i+6] = -1.f + (float)i;
		vertexData[i+7] = -1.f + (float)i;
		vertexData[i+8] = 0.0f + (float)i;
		
		colorData[i] = 1.f;
		colorData[i+1] = 0.f;
		colorData[i+2] = 0.f;
		colorData[i+3] = 0.f;
		colorData[i+4] = 1.f;
		colorData[i+5] = 0.f;
		colorData[i+6] = 0.f;
		colorData[i+7] = 0.f;
		colorData[i+8] = 1.f;
	}
	
	int offset = 0;
	for(int i=0; i<SIZE; i++) {
		tri[i].v1x = &vertexData[offset];
		tri[i].v1y = &vertexData[offset+1];
		tri[i].v1z = &vertexData[offset+2];
		tri[i].v2x = &vertexData[offset+3];
		tri[i].v2y = &vertexData[offset+4];
		tri[i].v2z = &vertexData[offset+5];
		tri[i].v3x = &vertexData[offset+6];
		tri[i].v3y = &vertexData[offset+7];
		tri[i].v3z = &vertexData[offset+8];
		offset += 9;
	}
}

//DECONSTRUCTOR
Mesh::~Mesh() {
	delete [] vertexData;
	delete [] colorData;
	delete [] tri;
}