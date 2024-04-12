#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 vertexColor; // specify a color output to the fragment shader

void main() {
    vertexColor = aColor; // set the output variable to input color
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}