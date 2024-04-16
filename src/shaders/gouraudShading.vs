#version 330 core
layout (location = 0) in vec3 aPos; // position and normal in local coords
layout (location = 1) in vec3 aNormal; // vertex normal 
layout (location = 2) in vec3 aColor; 

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection; 

uniform vec3 triangleNormal; // normal of the triangle the model is on

out vec3 vertexColor; // specify a color output to the fragment shader

vec3 calculateLighting(vec3 position, vec3 normal, vec3 albedo) {
    // TODO: this doesn't work as we move and rotate the model. find out why. 
    // (output just lightDir, position, normal, etc.)
    vec3 lightPos = vec3(0.0f, 2.0f, 0.0f);
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightDir = normalize(lightPos - position);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;
    return albedo * diffuse;
}

void main() {
    // aPos, aNormal, and aColor should be fed in as model space coordinates?
    vec3 worldPos = vec3(model * vec4(aPos, 1.0));
    vec3 worldNormal = normalize(vec3(model * vec4(aNormal, 0.0)));
    vertexColor = calculateLighting(worldPos, worldNormal, aColor);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}