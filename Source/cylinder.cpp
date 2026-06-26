#include "cylinder.h"

Cylinder::Cylinder(glm::vec3 origin, float radius, float height, glm::vec3 color){
    transform.position = (origin);

    height /= 2;
    
    vertices.push_back({glm::vec3(0.0f, height, 0.0f), color}); // Top Center Vertex
    vertices.push_back({glm::vec3(0.0f, -height, 0.0f), color}); // Bottom Center Vertex

    for (int i = 0; i <= segments; i++){
        float angle = (2 * M_PI * i) / segments;
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);

        vertices.push_back({glm::vec3(x, height, z), color});
        vertices.push_back({glm::vec3(x, -height, z), color});
    }

    // Indices Loop
    for (int i = 0; i < segments; i++){
        int topCurrent = 2 + i * 2;
        int bottomCurrent = topCurrent + 1;
        int topNext = topCurrent + 2;
        int bottomNext = bottomCurrent + 2;

        // Top Cap
        indices.push_back(0);
        indices.push_back(topCurrent);
        indices.push_back(topNext);

        // Sides
        indices.push_back(topCurrent);
        indices.push_back(bottomCurrent);
        indices.push_back(topNext);
        indices.push_back(topNext);
        indices.push_back(bottomCurrent);
        indices.push_back(bottomNext);

        // Bottom Cap
        indices.push_back(1);
        indices.push_back(bottomCurrent);
        indices.push_back(bottomNext);
    }

    SetupMesh();
}

Cylinder::~Cylinder(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Cylinder::SetupMesh(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ColorVertex), vertices.data(), GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Cylinder::Draw(unsigned int shaderProgram){
    glUseProgram(shaderProgram);
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &transform.model[0][0]);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Cylinder::SetPosition(glm::vec3 newPosition){
    transform.position = newPosition;
}