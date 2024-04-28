#version 330 core

uniform vec3 cameraPosition;
out vec4 FragColor;

in vec3 worldNormal; // since the normal is passed in, it will be interpolated across the triangle
in vec3 worldPosition;
in vec3 albedo;


vec3 calculateLighting(vec3 position, vec3 normal, vec3 albedo) {    
    vec3 lightPos = vec3(4.0f, 3.0f, 1.0f);
    vec3 lightColor = vec3(1.0f, 0.0f, 0.5f) * 0.9f; // soft purple lighting :D
    vec3 lightDir = normalize(lightPos - position);

    // ambient lighting
    float ambientStrength = 0.1f;
    vec3 ambient = vec3(1.0f, 1.0f, 1.0f) * ambientStrength;

    // diffuse lighting
    float diffuseStrength = 0.8f;
    float diff = max(dot(normal, lightDir), 0.0f);
    float diffuse = diff * diffuseStrength;

    // specular lighting
    float specularStrength = 0.3f;
    vec3 viewDir = normalize(cameraPosition - position);
    vec3 reflectDir = normalize(reflect(-lightDir, normal));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 25.0f);
    float specular = specularStrength * spec;

    vec3 total = (diffuse  + specular) * lightColor  + ambient *vec3(1.0f, 1.0f, 1.0f);
    return clamp(total, 0.0, 1.0);
}

void main()
{             
    vec3 color = calculateLighting(worldPosition, worldNormal, albedo);
    //color = vec3(1.0, 1.0, 1.0);
    FragColor = vec4(vec3(color), 1.0);
}