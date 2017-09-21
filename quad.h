#ifndef QUAD_H
#define QUAD_H

#include <iostream>
#define GLEW_STATIC
#include "GL/glew.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

class Quad {
	public:
		Quad();
		~Quad();
        void setPosition(float _x, float _y, float _z);
		void move(glm::vec3 translate);
        glm::vec3 getPosition() const;
        glm::mat4 getModelViewProjection(glm::mat4 projection, glm::mat4 camera);
        glm::mat4 getTransform() const;
        int getN_Vertices() const;
		GLfloat* getData() {return data;};

    private:
        glm::mat4 transformMat, mvpMat;
        glm::vec3 position;
        const int N_VERTICES = 6;
		
		GLfloat* data;/* = {
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
		};*/
};

#endif

static const GLfloat quadData[] = {
    -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f
};