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
#include <math.h>
#include "cube.h"
#include "quad.h"
#include "mesh.h"
#include "drawbuffer.h"
#include "objloader.hpp"

using namespace glm;

class Window {
    public:
        Window();
        Window(int _width, int _height, std::string _title, bool initialize);
        ~Window();

        void init();
        void draw();
        void close();
		bool isOpen();
    private:
        GLFWwindow* window;
        std::string title;
        int width, height;
        bool initialized;
		bool windowOpen;
        mat4 camera, projection;
        glm::vec3 position, direction;

        double deltaTime, lastTime;

        void input();
        float horizontalAngle = 3.14159265359, verticalAngle = 0.0f;
        float mouseSpeed = 0.001f;
        float moveSpeed = 0.3f;
        std::vector<Cube> cubes;
		std::vector<Quad> quads;

        //tmp
        GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
        GLuint vertexArrayId, programId, matrixId;
	    glm::mat4 MVP; // Remember, matrix multiplication is the other way around
        GLuint vertexbuffer;
        GLuint colorbuffer;
		

		Mesh mesh;
		Drawbuffer db;
		float amplitude = 7.f;
		float amp_rate = 0.1f;
		void loadModel(std::string file, Drawbuffer& db);
};
