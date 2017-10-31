#include "Drawbuffer.h"

//CONSTRUCTOR
Drawbuffer::Drawbuffer() {

	vertex_data = new GLfloat[MAX_VERTICES * 3];
	color_data = new GLfloat[MAX_VERTICES * 3];
	n_vertices = 0;
	vertex_size = 0;
	color_size = 0;

}

//DECONSTRUCTOR
Drawbuffer::~Drawbuffer() {

}

//GET NUMBER OF VERTICES
unsigned int Drawbuffer::getN_Vertices() const {
    return n_vertices;
}

//GET VERTEX DATA
GLfloat* Drawbuffer::getVertexData() {
	return vertex_data;
}

//GET COLOR DATA
GLfloat* Drawbuffer::getColorData() {
	return color_data;
}

//GET VERTEX SIZE
unsigned int Drawbuffer::getVertexSize() const {
	return n_vertices * VERTEX_OFFSET;
}

//GET COLOR SIZE
unsigned int Drawbuffer::getColorSize() const {
	return n_vertices * VERTEX_OFFSET;
}

//ADD VERTEX
void Drawbuffer::addVertex(Vertex v) {
	unsigned int i = n_vertices * 3;
	vertex_data[i] = v.x;
	vertex_data[i+1] = v.y;
	vertex_data[i+2] = v.z;
	color_data[i] = v.r;
	color_data[i+1] = v.g;
	color_data[i+2] = v.b;
	n_vertices++;
}
