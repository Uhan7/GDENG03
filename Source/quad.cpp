#include "quad.h"

Quad::Quad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 color){
    vertices[0] = {{p1.x, p1.y, p1.z}, color};
    vertices[1] = {{p2.x, p2.y, p2.z}, color};
    vertices[2] = {{p3.x, p3.y, p3.z}, color};
    vertices[3] = {{p4.x, p4.y, p4.z}, color};

    SetupMesh();
}

Quad::~Quad(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Quad::SetupMesh(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Quad::Draw(unsigned int shaderProgram){
    glUseProgram(shaderProgram);
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &transform.model[0][0]);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Quad::SetPosition(glm::vec3 newPosition){
    transform.position = newPosition;
}

Quad Quad::MakeSquare(glm::vec3 center, float sideLength, glm::vec3 color){
    float halfLength = sideLength / 2;
    return Quad(
        glm::vec3{center.x - halfLength, center.y + halfLength, 0.0f},
        glm::vec3{center.x + halfLength, center.y + halfLength, 0.0f},
        glm::vec3{center.x - halfLength, center.y - halfLength, 0.0f},
        glm::vec3{center.x + halfLength, center.y - halfLength, 0.0f},
        color
    );
}

std::unique_ptr<Quad> Quad::MakeSquarePtr(glm::vec3 center, float sideLength, glm::vec3 color){
    float halfLength = sideLength / 2;
    return std::make_unique<Quad>(
        glm::vec3{center.x - halfLength, center.y + halfLength, 0.0f},
        glm::vec3{center.x + halfLength, center.y + halfLength, 0.0f},
        glm::vec3{center.x - halfLength, center.y - halfLength, 0.0f},
        glm::vec3{center.x + halfLength, center.y - halfLength, 0.0f},
        color
    );
}