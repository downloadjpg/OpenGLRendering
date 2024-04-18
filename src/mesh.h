#include "glm/glm.hpp"
#include <vector>
#include <GL/glew.h>
#include "shader_s.h"
#pragma once

class ModelViewMatrix;

struct Vertex {
    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec3 normal = glm::vec3(0,0,0);
    glm::vec3 color = glm::vec3(0,0,0);
};

class Mesh {
public:
    std::vector<Vertex> triangles; // vector of vertex triplets
    Mesh(std::vector<Vertex> triangles);
    void draw(Shader &shader);
    unsigned int VAO, VBO;

private:
    void setupMesh();
};