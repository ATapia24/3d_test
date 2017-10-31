#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#define GLEW_STATIC
#include "GL/glew.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

struct Vertex {
	GLfloat x, y, z;
	GLfloat r, g, b;
	
	Vertex(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _r, GLfloat _g, GLfloat _b) {
		x = _x;
		y = _y;
		z = _z;
		r = _r;
		g = _g;
		b = _b;
	}
};

class Drawbuffer {
    public:
        Drawbuffer();
        ~Drawbuffer();
        unsigned int getN_Vertices() const;
		GLfloat* getVertexData();
		GLfloat* getColorData();
		unsigned int getVertexSize() const;
		unsigned int getColorSize() const;
		void addVertex(Vertex v);

    private:
		const unsigned int MAX_VERTICES = 30000;
		const unsigned int VERTEX_OFFSET = sizeof(GLfloat) * 3;
		GLfloat *vertex_data, *color_data;
		unsigned int vertex_size, color_size;
		unsigned int n_vertices;	
};
