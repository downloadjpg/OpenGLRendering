#include "mesh.h"

void addFaceToIndices(std::vector<unsigned int> face, std::vector<unsigned int> &indices);

Mesh loadObjFile(const char* filename) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file " << filename << std::endl;
        return Mesh(vertices, indices);
    }
    std::vector<glm::vec3> positions;
    // std::vector<glm::vec2> textures;
    std::vector<glm::vec3> normals;
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

        // Reading faces (indices)
        else if(line != "" && line.at(0) == 'f' && line.at(1) == ' ') {
            std::vector<unsigned int> faceIndices;
            unsigned int iter = 2; // 'f ' is 2 characters long
            while (iter < lineTemp.size()) {
                std::string vertex = lineTemp.substr(iter, lineTemp.find(' ', iter) - iter);
                // std::cout << "Vertex: " << vertex << std::endl;
                // We need to account for the varying formats of the faces
                // 1. 1/1/1 2/2/2 3/3/3
                // 2. 1//1 2//2 2//2
                // 3. 1 2 3
                // But for now, let's just grab the first number and ignore the rest.
                std::string value = vertex.substr(0, vertex.find('/'));
                // std::cout << "Value: " << value << std::endl;
                if (value != "")
                    faceIndices.push_back(std::stoi(value) - 1); // OBJ indices are 1-based, so we need to subtract 1.
                iter += vertex.size() + 1;
            }
                // std::cout << "Face index: ";
                // for (unsigned int i = 0; i < faceIndices.size(); i++) {
                //     std::cout << faceIndices[i] << " ";
                // }
                addFaceToIndices(faceIndices, indices);
        }
    }
    std::cout << "Loaded " << filename << " with " << positions.size() << " vertices, " << normals.size() << "normals and " << indices.size() << " faces." << std::endl;

    // Now that we'eve accumulated our data, put them into Vertex structs and add them to the vertices vector.
    for (unsigned int i = 0; i < positions.size(); i++) {
        Vertex vertex;
        vertex.Position = positions.at(i);
        if (i < normals.size())
            vertex.Normal = normals.at(i);
        vertex.Color = glm::vec3(1.0f, 1.0f, 1.0f);
        vertices.push_back(vertex);
    }
    // for (unsigned int i = 0; i < vertices.size(); i++) {
    //     std::cout << "Vertex " << i << std::endl;
    //     std::cout << "\tPosition: " << vertices[i].Position.x << " " << vertices[i].Position.y << " " << vertices[i].Position.z << std::endl;
    //     std::cout << "\tColor: " << vertices[i].Color.x << " " << vertices[i].Color.y << " " << vertices[i].Color.z << std::endl;
    //     std::cout << "\tNormal: " << vertices[i].Normal.x << " " << vertices[i].Normal.y << " " << vertices[i].Normal.z << std::endl;
    // }

    std::cout << "Loaded " << filename << " with " << vertices.size() << " vertices and " << indices.size() << " indices." << std::endl;
    return Mesh(vertices, indices);
}

void addFaceToIndices(std::vector<unsigned int> face, std::vector<unsigned int> &indices) {
    // If the face has 3 vertices:
    if (face.size() == 3) {
        indices.push_back(face[0]);
        indices.push_back(face[1]);
        indices.push_back(face[2]);
    }
    // If the face has 4 vertices, it's easy to split into two triangles.
    else if (face.size() == 4) {
        indices.push_back(face[0]);
        indices.push_back(face[1]);
        indices.push_back(face[2]);
        indices.push_back(face[0]);
        indices.push_back(face[2]);
        indices.push_back(face[3]);
    }   
    // Oops! You lose.
    else std::cout << "Face has " << face.size() << " vertices, not supported." << std::endl;
}
