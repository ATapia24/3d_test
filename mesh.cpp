#include "mesh.h"

Mesh::Mesh() {
    transformMat = glm::mat4(1.0f);
    position = glm::vec3(0, 0, 0);

	vertexData = new GLfloat[N_VERTICES * 3];
	colorData = new GLfloat[N_VERTICES * 3];

	GLfloat* VertexData = new GLfloat[36*3] {
                -1.0f,-1.0f,-1.0f,
                -1.0f,-1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f,-1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f,-1.0f,
                 1.0f,-1.0f, 1.0f,
                -1.0f,-1.0f,-1.0f,
                 1.0f,-1.0f,-1.0f,
                 1.0f, 1.0f,-1.0f,
                 1.0f,-1.0f,-1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f,-1.0f,
                 1.0f,-1.0f, 1.0f,
                -1.0f,-1.0f, 1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f,-1.0f, 1.0f,
                 1.0f,-1.0f, 1.0f,
                 1.0f, 1.0f, 1.0f,
                 1.0f,-1.0f,-1.0f,
                 1.0f, 1.0f,-1.0f,
                 1.0f,-1.0f,-1.0f,
                 1.0f, 1.0f, 1.0f,
                 1.0f,-1.0f, 1.0f,
                 1.0f, 1.0f, 1.0f,
                 1.0f, 1.0f,-1.0f,
                -1.0f, 1.0f,-1.0f,
                 1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,
                 1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                 1.0f,-1.0f, 1.0f
	};

	GLfloat* ColorData = new GLfloat[36*3] {
                0.583f,  0.771f,  0.014f,
                0.609f,  0.115f,  0.436f,
                0.327f,  0.483f,  0.844f,
                0.822f,  0.569f,  0.201f,
                0.435f,  0.602f,  0.223f,
                0.310f,  0.747f,  0.185f,
                0.597f,  0.770f,  0.761f,
                0.559f,  0.436f,  0.730f,
                0.359f,  0.583f,  0.152f,
                0.483f,  0.596f,  0.789f,
                0.559f,  0.861f,  0.639f,
                0.195f,  0.548f,  0.859f,
                0.014f,  0.184f,  0.576f,
                0.771f,  0.328f,  0.970f,
                0.406f,  0.615f,  0.116f,
                0.676f,  0.977f,  0.133f,
                0.971f,  0.572f,  0.833f,
                0.140f,  0.616f,  0.489f,
                0.997f,  0.513f,  0.064f,
                0.945f,  0.719f,  0.592f,
                0.543f,  0.021f,  0.978f,
                0.279f,  0.317f,  0.505f,
                0.167f,  0.620f,  0.077f,
                0.347f,  0.857f,  0.137f,
                0.055f,  0.953f,  0.042f,
                0.714f,  0.505f,  0.345f,
                0.783f,  0.290f,  0.734f,
                0.722f,  0.645f,  0.174f,
                0.302f,  0.455f,  0.848f,
                0.225f,  0.587f,  0.040f,
                0.517f,  0.713f,  0.338f,
                0.053f,  0.959f,  0.120f,
                0.393f,  0.621f,  0.362f,
                0.673f,  0.211f,  0.457f,
                0.820f,  0.883f,  0.371f,
                0.982f,  0.099f,  0.879f
	};

	for(int i=0; i<N_CUBES; i++) {
		for(int j=0; j<36*3; j++) {
			//vertexData[j + (i*36*3)] = VertexData[j];
			vertexData[j + (i*36*3)] = VertexData[j] + (i*2.f);
			colorData[j + (i*36*3)] = ColorData[j];
		}	
	}

}

Mesh::~Mesh() {

}

//SET POSITION
void Mesh::setPosition(float _x, float _y, float _z) {
    position = glm::vec3(_x, _y, _z);
    transformMat = glm::mat4(1.0f) * glm::translate(position);
}

//MOVE
void Mesh::move(glm::vec3 translate) {
    position += translate;
    transformMat *= glm::translate(translate);
}

//GET POSITION
glm::vec3 Mesh::getPosition() const {
    return position;
}

//MOVE
void Mesh::move(unsigned int i, GLfloat x, GLfloat y, GLfloat z) {
	for(int j=0; j<36; j+=3) {
		//vertexData[(i*36*3)+j] += x;
		//vertexData[(i*36*3)+1+j] += y;
		//vertexData[(i*36*3)+2+j] += z;
	}
}

//SET
void Mesh::set(unsigned int i, GLfloat x, GLfloat y, GLfloat z) {
}

//GET MODEL VIEW PROJECTION
glm::mat4 Mesh::getModelViewProjection(glm::mat4 projection, glm::mat4 camera) {
    mvpMat = projection * camera * transformMat;
    return mvpMat;
}

//GET TRANSFORM
glm::mat4 Mesh::getTransform() const {
    return transformMat;
}

//GET NUMBER OF VERTICES
int Mesh::getN_Vertices() const {
    return N_VERTICES;
}

//GET VERTEX DATA
GLfloat* Mesh::getVertexData() {
	return vertexData;
}

//GET COLOR DATA
GLfloat* Mesh::getColorData() {
	return colorData;
}

//GET VERTEX SIZE
int Mesh::getVertexSize() const {
	return vertexSize;
}

//GET COLOR SIZE
int Mesh::getColorSize() const {
	return colorSize;
}
