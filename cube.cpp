#include "Cube.h"

Cube::Cube() {
    transformMat = glm::mat4(1.0f);
    position = glm::vec3(0, 0, 0);
}

Cube::~Cube() {

}

//SET POSITION
void Cube::setPosition(float _x, float _y, float _z) {
    position = glm::vec3(_x, _y, _z);
    transformMat = glm::mat4(1.0f) * glm::translate(position);
}

//MOVE
void Cube::move(glm::vec3 translate) {
    position += translate;
    transformMat *= glm::translate(translate);
}

//GET POSITION
glm::vec3 Cube::getPosition() const {
    return position;
}

//GET MODEL VIEW PROJECTION
glm::mat4 Cube::getModelViewProjection(glm::mat4 projection, glm::mat4 camera) {
    mvpMat = projection * camera * transformMat;
    return mvpMat;
}

//GET TRANSFORM
glm::mat4 Cube::getTransform() const {
    return transformMat;
}

//GET NUMBER OF VERTICES
int Cube::getN_Vertices() const {
    return N_VERTICES;
}
