#ifndef MESH_H
#define MESH_H

#include <iostream>
#define GLEW_STATIC
#include "GL/glew.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

struct Triangle {
	GLfloat* v1x;
	GLfloat* v1y;
	GLfloat* v1z;
	GLfloat* v2x;
	GLfloat* v2y;
	GLfloat* v2z;
	GLfloat* v3x;
	GLfloat* v3y;
	GLfloat* v3z;
};

class Mesh {
	public:
		Mesh();
		~Mesh();
		

		void setPosition(float _x, float _y, float  _z);
		void move(glm::vec3 translate);

		inline glm::vec3 getPosition() {return position;};
		inline glm::mat4 getModelViewProjection(glm::mat4 projection, glm::mat4 camer) {return mvpMat;};
		inline glm::mat4 getTransform() {return transformMat;};
		inline GLfloat* getVertexData() {return vertexData;};
		inline GLfloat* getColorData() {return colorData;};
		inline int getSize() {return SIZE;};

	private:
		const int SIZE = 10;
		GLfloat* vertexData;
		GLfloat* colorData;
		Triangle* tri;
		glm::mat4 transformMat, mvpMat;
		glm::mat3 position;
};

#endif
