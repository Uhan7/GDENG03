#include "capsule.h"

Capsule::Capsule(glm::vec3 origin, float radius, float totalHeight, glm::vec3 color){
    transform.position = origin;

    float cylinderHeight = totalHeight - (2.0f * radius);
    float cylinderHalfHeight = cylinderHeight / 2.0f;

    std::vector<float> ringYPositions;
    std::vector<float> ringRadii;

    // Top Pole
    ringYPositions.push_back(cylinderHalfHeight + radius);
    ringRadii.push_back(0.0f);

    // Top Hemisphere
    for (int i = 1; i <= hemisphereRings; i++){
        float t = static_cast<float>(i) / static_cast<float>(hemisphereRings);
        float angle = t * (M_PI / 2.0f);

        float y = cylinderHalfHeight + std::cos(angle) * radius;
        float ringRadius = std::sin(angle) * radius;

        ringYPositions.push_back(y);
        ringRadii.push_back(ringRadius);
    }

    // Bottom Cylinder End
    if (cylinderHeight > 0.0f){
        ringYPositions.push_back(-cylinderHalfHeight);
        ringRadii.push_back(radius);
    }

    // Bottom Hemisphere
    for (int i = 1; i <= hemisphereRings; i++){
        float t = static_cast<float>(i) / static_cast<float>(hemisphereRings);
        float angle = t * (M_PI / 2.0f);

        float y = -cylinderHalfHeight - std::sin(angle) * radius;
        float ringRadius = std::cos(angle) * radius;

        ringYPositions.push_back(y);
        ringRadii.push_back(ringRadius);
    }

    // Vertices
    for (int ring = 0; ring < static_cast<int>(ringYPositions.size()); ring++){
        float y = ringYPositions[ring];
        float ringRadius = ringRadii[ring];

        for (int seg = 0; seg <= segments; seg++){
            float u = static_cast<float>(seg) / static_cast<float>(segments);
            float angle = u * 2.0f * M_PI;

            float x = std::cos(angle) * ringRadius;
            float z = std::sin(angle) * ringRadius;

            vertices.push_back({glm::vec3(x, y, z), color});
        }
    }

    // Indices
    int rowSize = segments + 1;
    int rowCount = static_cast<int>(ringYPositions.size());

    for (int row = 0; row < rowCount - 1; row++){
        for (int seg = 0; seg < segments; seg++){
            int topLeft = row * rowSize + seg;
            int topRight = topLeft + 1;
            int bottomLeft = (row + 1) * rowSize + seg;
            int bottomRight = bottomLeft + 1;

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    SetupMesh();
}

Capsule::~Capsule(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Capsule::SetupMesh(){
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

void Capsule::Draw(unsigned int shaderProgram){
    glUseProgram(shaderProgram);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    transform.UpdateModelMatrix();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &transform.model[0][0]);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}