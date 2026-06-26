#include "sphere.h"

Sphere::Sphere(glm::vec3 origin, float radius, glm::vec3 color){
    transform.position = (origin);

    // Vertices Loop
    for (int y = 0; y <= segmentsY; y++){
        float v = (float)y / segmentsY;
        float phi = v * M_PI;
        for (int x = 0; x <= segmentsX; x++){
            float u = (float)x / segmentsX;
            float theta = u * 2 * M_PI;

            float posX = radius * sin(phi) * cos(theta);
            float posY = radius * cos(phi);
            float posZ = radius * sin(phi) * sin(theta);

            vertices.push_back({glm::vec3(posX, posY, posZ), color});
        }
    }

    // Indices Loop
    int rowSize = segmentsX + 1;
    for (int y = 0; y <= segmentsY; y++){
        for (int x = 0; x <= segmentsX; x++){
            int topLeft = y * rowSize + x;
            int topRight = topLeft + 1;
            int bottomLeft = (y + 1) * rowSize + x;
            int bottomRight = bottomLeft + 1;

            // This shi is like the [0, 1, 2, 1, 2, 3] whatever from the indices
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(bottomRight);
        }
    }

    SetupMesh();
}

Sphere::~Sphere(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Sphere::SetupMesh(){
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

void Sphere::Draw(unsigned int shaderProgram){
    glUseProgram(shaderProgram);
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &transform.model[0][0]);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Sphere::SetPosition(glm::vec3 newPosition){
    transform.position = newPosition;
}