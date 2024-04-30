#include "mesh.h"
#include <algorithm> // for std::count

struct Material {
    std::string name;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

void addFaceToTriangles(std::vector<Vertex> face, std::vector<Vertex> &triangles);
Vertex parseVertexString(std::string vertexStr, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals);

Mesh loadObjFile(const char* filename) {
    // Check if there's a material file. If there is, call loadMtlFile.
    // If there isn't, just load the obj file.
    // filename should be the same, just with a mtl extension instead of obj
    std::string mtlFilename = std::string(filename);
    mtlFilename.replace(mtlFilename.find_last_of('.') + 1, 3, "mtl");
    loadMtlFile(mtlFilename.c_str());
    
    std::vector<Vertex> triangles = {}; // vertexes in pairs of 3
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file " << filename << std::endl;
        return Mesh(triangles);
    }
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    Material currentMaterial = Material();
    //std::vector<glm::vec2> texCoords;

    for (std::string line; getline(file, line);) { 
        std::string lineTemp = line;  

        // Reading vertex (position)
        if(line != "" && line.at(0) == 'v' && line.at(1) == ' ') {
            glm::vec3 position;
            lineTemp = lineTemp.substr(2);
            sscanf(lineTemp.c_str(), "%f %f %f", &position.x, &position.y, &position.z); // huh
            positions.push_back(position);
           //std::cout << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;
        }

        // Reading normals
        else if(line != "" && line.at(0) == 'v' && line.at(1) == 'n') {
            glm::vec3 normal;
            lineTemp = lineTemp.substr(3);
            sscanf(lineTemp.c_str(), "%f %f %f", &normal.x, &normal.y, &normal.z);
            normals.push_back(normal);
        }

        // Reading texture coordinates
        // else if (line != "" && line.at(0) == 'v' && line.at(1) == 't') {
        //     glm::vec2 texCoord;
        //     lineTemp = lineTemp.substr(3);
        //     sscanf(lineTemp.c_str(), "%f %f", &texCoord.x, &texCoord.y);
        //     texCoords.push_back(texCoord);
        // }

        // Reading faces (indices)
        // This will essentially construct the VBO, since I'm ditching the EBO stuff.
        // Each vertex in the face will be parsed and constructed from the positions[] and normals[] arrays.
        // After this, the face will be triangulated, and the triangle will be appended to vertices.
        else if(line != "" && line.at(0) == 'f' && line.at(1) == ' ') {
            std::vector<Vertex> face;
            unsigned int iter = 2; // 'f ' is 2 characters long, so we begin here.
            while (iter < lineTemp.size()) {
                // Get the next vertex in the line.
                std::string vertexStr = lineTemp.substr(iter, lineTemp.find(' ', iter) - iter);
                Vertex vertex = parseVertexString(vertexStr, positions, normals, currentMaterial);
                face.push_back(vertex);
                iter += vertexStr.size() + 1;
            }
                addFaceToTriangles(face, triangles);
        }

        // Reading material
        if (line != "" && line.substr(0, 6) == "usemtl") {
            currentMaterial = line.substr(7);
        }
    }
    // std::cout << "Loaded " << filename << " with " << positions.size() << " vertices, " << normals.size() << " normals and " << indices.size() << " faces." << std::endl;

 

    //std::cout << "Loaded " << filename << " with " << vertices.size() << " vertices and " << indices.size() << " indices." << std::endl;
    std::cout << "Loaded!";
    return Mesh(triangles);
}

Vertex parseVertexString(
    std::string str,
    std::vector<glm::vec3> &positions,
    std::vector<glm::vec3> &normals,
    Material currentMaterial ) {
    //std::vector<glm::vec2> &texCoords ) {

    // This string can come in the following formats:
    // v/vt/vn
    // v/vt
    // v//vn
    // v
    Vertex vertex;
    unsigned int numSlashes = std::count(str.begin(), str.end(), '/');
    unsigned int normalIndex = 0;
    unsigned int positionIndex = 0;
    //unsigned int texCoordIndex = 0;
    // if (numSlashes >= 1) {
    //     texCoordIndex = std::stoi(str.substr(str.find('/') + 1, str.find_last_of('/') - str.find('/') - 1));
    //     vertex.texCoord = texCoords.at(texCoordIndex - 1); // obj is 1 based!
    // }
    if (numSlashes == 0)
        positionIndex = std::stoi(str);
    else
        positionIndex = std::stoi(str.substr(0, str.find('/')));
    if (numSlashes == 2)
        normalIndex = std::stoi(str.substr(str.find_last_of('/') + 1));

    vertex.position = positions.at(positionIndex - 1); // obj is 1 based!
    vertex.normal = glm::normalize(normals.at(normalIndex - 1));
    vertex.color = currentMaterial.diffuse;

    return vertex;
}

void addFaceToTriangles(std::vector<Vertex> face, std::vector<Vertex> &triangles) {
    // If the face has 3 vertices:
    if (face.size() == 3) {
        triangles.push_back(face[0]);
        triangles.push_back(face[1]);
        triangles.push_back(face[2]);
    }
    // If the face has 4 vertices, it's easy to split into two triangles.
    else if (face.size() == 4) {
        triangles.push_back(face[0]);
        triangles.push_back(face[1]);
        triangles.push_back(face[2]);
        triangles.push_back(face[0]);
        triangles.push_back(face[2]);
        triangles.push_back(face[3]);
    }   
    // Oops! You lose.
    else std::cout << "Face has " << face.size() << " vertices, not supported." << std::endl;
}

std::vector<Material> loadMtlFile(const char* filename) {
    std::vector<Material> materials;
    Material defaultMaterial = Material();
    materials.push_back(Material());
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << " " << filename << std::endl;
        return materials;
    }
}