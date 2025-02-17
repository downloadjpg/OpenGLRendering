#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor; // specify a color output to the fragment shader

void main() {
    vertexColor = aColor; // set the output variable to input color
    //vertexColor = (aPos + 1.0f) / 2.0f; // renders positions as colors
    //vertexColor = (aNormal + vec3(1.0f)) / 2.0f; // renders normals as colors
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}