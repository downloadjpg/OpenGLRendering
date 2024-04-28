#include "transformations.h"
#include "mesh.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <fstream>
#include <string>


ModelViewMatrix::ModelViewMatrix() {
    const float CAMERA_OFFSET = -30.0f;
    modelMatrix = glm::mat4(1.0f);
    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, CAMERA_OFFSET)); // Camera is 5 units back (forward..?) from the origin.

    totalMatrix = viewMatrix * modelMatrix;
}

void ModelViewMatrix::scale(float multiplier) {
    modelMatrix = glm::scale(modelMatrix, glm::vec3(multiplier, multiplier, multiplier));
    totalMatrix = viewMatrix * modelMatrix;
}

void ModelViewMatrix::rotate(float angle, glm::vec3 axis) {
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
    totalMatrix = viewMatrix * modelMatrix;
}

void ModelViewMatrix::translate(glm::vec3 translation) {
    modelMatrix = glm::translate(modelMatrix, translation);
    totalMatrix = viewMatrix * modelMatrix;
}


void ModelViewMatrix::save(std::string path) {
    std::ofstream file(path, std::ios::binary | std::ios::out);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            file.write(reinterpret_cast<const char*>(&modelMatrix[i][j]), sizeof(float));
        }
    }
    // std::cout << "Saved model transformation to " << path << "\n";
    file.close();
}


void ModelViewMatrix::load(std::string path) {
    std::ifstream file(path, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for reading");
    }

    glm::mat4 matrix;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            file.read(reinterpret_cast<char*>(&matrix[i][j]), sizeof(float));
        }
    }

    file.close();
    // std::cout << "Loaded model transformation from " << path << "\n";
    modelMatrix = matrix;
}