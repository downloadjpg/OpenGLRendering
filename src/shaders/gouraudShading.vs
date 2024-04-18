#version 330 core
layout (location = 0) in vec3 aPos; // position and normal in local coords
layout (location = 1) in vec3 aNormal; // vertex normal in local coords
layout (location = 2) in vec3 aColor;  // albedo

uniform mat4 model; 
uniform mat4 modelInverseTranspose;
uniform mat4 view; 
uniform mat4 projection; 

//uniform vec3 triangleNormal; // normal of the triangle the model is on
uniform vec3 cameraPosition;

out vec3 vertexColor; // specify a color output to the fragment shader


vec3 calculateLighting(vec3 position, vec3 normal, vec3 albedo) {
    // calculates the lighting of a specific vertex. this is then interpolated across different fragments
    
    vec3 lightPos = vec3(4.0f, 3.0f, 1.0f);
    vec3 lightColor = vec3(1.0f, 0.0f, 0.5f) * 0.9f; // soft purple lighting :D
    vec3 lightDir = normalize(lightPos - position);

    // ambient lighting
    vec3 ambient = vec3(1.0f, 1.0f, 1.0f) * 0.2f;

    // diffuse lighting
    float diffuseStrength = 1.0f;
    float diff = max(dot(normal, lightDir), 0.0f);
    float diffuse = diff * diffuseStrength;

    // specular lighting
    float specularStrength = 1.0f;
    vec3 viewDir = normalize(cameraPosition - position);
    vec3 reflectDir = normalize(reflect(-lightDir, normal));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 25.0f);
    float specular = specularStrength * spec;

    vec3 total = (diffuse) * lightColor + ambient + specular * vec3(1.0f, 1.0f, 1.0f);
    return clamp(total, 0.0, 1.0);
}

void main() {
    // aPos, aNormal, and aColor should be fed in as model space coordinates?
    vec3 worldPos = vec3(model * vec4(aPos, 1.0));
    vec3 worldNormal = normalize((vec3(modelInverseTranspose * vec4(aNormal, 0.0))));
    vertexColor = calculateLighting(worldPos, worldNormal, aColor);
    gl_Position = projection * view * vec4(worldPos, 1.0f);
}