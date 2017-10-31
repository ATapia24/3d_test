#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <fstream>
#define GLEW_STATIC
#include "GL/glew.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include <random>

class Mesh {
    public:
        Mesh();
        ~Mesh();
        void setPosition(float _x, float _y, float _z);
		void move(glm::vec3 translate);
        glm::vec3 getPosition() const;
        glm::mat4 getModelViewProjection(glm::mat4 projection, glm::mat4 camera);
        glm::mat4 getTransform() const;
        int getN_Vertices() const;
		GLfloat* getVertexData();
		GLfloat* getColorData();
		int getVertexSize() const;
		int getColorSize() const;
		void move(unsigned int i, GLfloat x, GLfloat y, GLfloat z);
		void set(unsigned int i, GLfloat x, GLfloat y, GLfloat z);
		const int N_CUBES = 1000;
		
		float randf(float min, float max)
		{
			return (min + 1) + (((float) rand()) / (float) RAND_MAX) * (max - (min + 1));
		}
    private:
        glm::mat4 transformMat, mvpMat;
        glm::vec3 position;
        const int N_VERTICES = 36 * N_CUBES;
		GLfloat* vertexData;
		GLfloat* colorData;
		int vertexSize = N_VERTICES * sizeof(GLfloat) * 3;
		int colorSize = N_VERTICES * sizeof(GLfloat) * 3;
		
};
