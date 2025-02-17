#include "mesh.h"
#include "transformations.h"

Mesh::Mesh(std::vector<Vertex> triangles) {
    this->triangles = triangles;
    setupMesh();
}

void Mesh::draw(Shader &shader) {
    // Bind the VAO, draw elements using our indices, and unbind the VAO.
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, triangles.size());
    //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    // Each element is a vertex with all the attributes we got, gets passed through 
    //      whatever shaders are bound, etc.
    glBindVertexArray(0);
}


// reads the vertices and indices from the vectors and sets up the VAO, VBO, and EBO
void Mesh::setupMesh() {
    // Generate all our guys
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the VAO, which organizes the data in the VBO.
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Write the vertices to the VBO
    glBufferData(GL_ARRAY_BUFFER, triangles.size() * sizeof(Vertex), &triangles[0], GL_STATIC_DRAW);

    // Set up the vertex attributes
    // -----------------------------
    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)); // this offsetof stuff is crazy cool and useful
    
    // Color
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    // -----------------------------
    glBindVertexArray(0); // cleannnup!
}