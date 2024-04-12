#include <GL/glew.h>
#include <glm/glm.hpp>
class Mesh;

class ModelViewMatrix {
public:
        glm::mat4 modelMatrix; // Transforms from model space to world space
        glm::mat4 viewMatrix; // Transforms from world space to camera space

        glm::mat4 totalMatrix; // = viewMatrix * modelMatrix;

        ModelViewMatrix();
        void applyToMesh(Mesh &mesh);

        void rotate(float angle, glm::vec3 axis);
        void scale(float multiplier);
        void translate(glm::vec3 translation);
};