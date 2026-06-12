#include "quad.h"

Quad::Quad(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4, Vec3 color){
    vertices[0] = {{p1.x, p1.y, 0.0f}, color};
    vertices[1] = {{p2.x, p2.y, 0.0f}, color};
    vertices[2] = {{p3.x, p3.y, 0.0f}, color};
    vertices[3] = {{p4.x, p4.y, 0.0f}, color};

    SetupMesh();
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(colorVertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(colorVertex), (void*)sizeof(Vec3));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Quad::Draw(unsigned int shaderProgram){
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}