#include "quad.h"


//CONSTRUCTOR
Quad::Quad() {
	data = new GLfloat[N_VERTICES * 3]{
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};
	
    transformMat = glm::mat4(1.0f);
    position = glm::vec3(0, 0, 0);
}

//DECONSTRUCTOR
Quad::~Quad() {

}

//SET POSITION
void Quad::setPosition(float _x, float _y, float _z) {
    position = glm::vec3(_x, _y, _z);
    transformMat = glm::mat4(1.0f) * glm::translate(position);
}

//MOVE
void Quad::move(glm::vec3 translate) {
    position += translate;
    transformMat *= glm::translate(translate);
}

//GET POSITION
glm::vec3 Quad::getPosition() const {
    return position;
}

//GET MODEL VIEW PROJECTION
glm::mat4 Quad::getModelViewProjection(glm::mat4 projection, glm::mat4 camera) {
    mvpMat = projection * camera * transformMat;
    return mvpMat;
}

//GET TRANSFORM
glm::mat4 Quad::getTransform() const {
    return transformMat;
}

//GET NUMBER OF VERTICES
int Quad::getN_Vertices() const {
    return N_VERTICES;
}