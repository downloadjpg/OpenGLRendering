#version 330 core
layout (location = 0) in vec3 aPos; // position and normal in local coords
layout (location = 1) in vec3 aNormal; // vertex normal in local coords
layout (location = 2) in vec3 aColor;  // albedo

uniform mat4 model; 
uniform mat4 modelInverseTranspose;
uniform mat4 view; 
uniform mat4 projection; 


out vec3 worldNormal;
out vec3 worldPosition;
out vec3 albedo;


void main() {
    albedo = vec3(1.0, 0.8, 0.2); // set the output variable to input color
    worldPosition = vec3(model * vec4(aPos, 1.0));
    worldNormal = normalize((vec3(modelInverseTranspose * vec4(aNormal, 0.0))));
    gl_Position = projection * view * vec4(worldPosition, 1.0f);
}
