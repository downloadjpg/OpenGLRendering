#include "glm/glm.hpp"
#include <vector>
#include <GL/glew.h>
#include "shader_s.h"
#pragma once

class ModelViewMatrix;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Color;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    //vector<Texture> textures;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void draw(Shader &shader);
    void draw_with_CPU_transform(Shader &shader, ModelViewMatrix &modelViewMatrix);
    unsigned int VAO, VBO, EBO;

private:
    void setupMesh();
};