// template based on material from learnopengl.com
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "gl_debug_tool.h"
#include "mesh.h"
#include "objReader.h"
#include "shader_s.h"
#include "transformations.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, ModelViewMatrix &modelViewMatrix);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "viewGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // // glew: load all OpenGL function pointers
    glewInit();
    
    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);
    
    // ------------------------------------------------------------------

    // Loading shaders from file.
    Shader gouraud("src/shaders/gouraudShading.vs", "src/shaders/basic.fs");
    Shader phong("src/shaders/phongShading.vs", "src/shaders/phongShading.fs");
    Shader flat("src/shaders/flatShading.vs", "src/shaders/flatShading.fs");

    Shader& chosenShader = flat;

    

    // Load mesh from file
    Mesh myMesh = loadObjFile("data/venus.obj");
    // ------------------------------------------------------------------


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    const float fov = glm::radians(90.0f);
    const float near = 0.1f;
    const float far = 100.0f;
    const float aspectRatio = float(SCR_WIDTH) / float(SCR_HEIGHT);

    glm::mat4 projectionMatrix = glm::perspective(fov, aspectRatio, near, far);
    ModelViewMatrix modelViewMatrix;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window, modelViewMatrix);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // when the heck did the depth buffer get here? what's with the | operator?
        
        // Okay I read that you call use() on the shader object BEFORE setting uniforms. 
        chosenShader.use();
        chosenShader.setMat4("model", modelViewMatrix.modelMatrix);
        chosenShader.setMat4("modelInverseTranspose", inverse(transpose(modelViewMatrix.modelMatrix)));
        chosenShader.setMat4("view", modelViewMatrix.viewMatrix);
        chosenShader.setMat4("projection", projectionMatrix);
        chosenShader.setVec3("cameraPos", glm::vec3(0.0f, 0.0f, 30.0f));
        myMesh.draw(chosenShader);
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    //glDeleteProgram(shaderProgram); // no need to delete the shader program, it's deleted when the Shader object is destroyed.

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// User input processing
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, ModelViewMatrix &modelViewMatrix)
{
    // Exit application
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Scaling
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        modelViewMatrix.scale(1.05f);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
        modelViewMatrix.scale(0.95f);
    }

    // Rotation
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        modelViewMatrix.rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        modelViewMatrix.rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        modelViewMatrix.rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        modelViewMatrix.rotate(-1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    }


    // Translation
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        modelViewMatrix.translate(glm::vec3(0.0f, 0.0f, -0.1f));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        modelViewMatrix.translate(glm::vec3(0.0f, 0.0f, 0.1f));
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        modelViewMatrix.translate(glm::vec3(-0.1f, 0.0f, 0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        modelViewMatrix.translate(glm::vec3(0.1f, 0.0f, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        modelViewMatrix = ModelViewMatrix();
    }


    // Save current modelViewMatrix
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        modelViewMatrix.save("savedTranslation.bin");
    }

    // Load saved modelViewMatrix
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        modelViewMatrix.load("savedTranslation.bin");
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
