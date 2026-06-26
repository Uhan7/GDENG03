#include "cube.h"
#include "colors.h"

Cube::Cube(glm::vec3 origin, float sideLength, glm::vec3 color){
    transform.position = (origin);

    sideLength /= 2;

    vertices[0] = {{-sideLength, -sideLength,  sideLength}, color};
    vertices[1] = {{sideLength, -sideLength,  sideLength}, color};
    vertices[2] = {{sideLength,  sideLength,  sideLength}, color};
    vertices[3] = {{-sideLength,  sideLength,  sideLength}, color};
    vertices[4] = {{-sideLength, -sideLength, -sideLength}, color};
    vertices[5] = {{sideLength, -sideLength, -sideLength}, color};
    vertices[6] = {{sideLength,  sideLength, -sideLength}, color};
    vertices[7] = {{-sideLength,  sideLength, -sideLength}, color};

    // vertices[0] = {{-sideLength, -sideLength,  sideLength}, whiteColor};
    // vertices[1] = {{sideLength, -sideLength,  sideLength}, redColor};
    // vertices[2] = {{sideLength,  sideLength,  sideLength}, orangeColor};
    // vertices[3] = {{-sideLength,  sideLength,  sideLength}, yellowColor};
    // vertices[4] = {{-sideLength, -sideLength, -sideLength}, greenColor};
    // vertices[5] = {{sideLength, -sideLength, -sideLength}, blueColor};
    // vertices[6] = {{sideLength,  sideLength, -sideLength}, magentaColor};
    // vertices[7] = {{-sideLength,  sideLength, -sideLength}, blackColor};

    SetupMesh();
}

Cube::~Cube(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Cube::SetupMesh(){
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

void Cube::Draw(unsigned int shaderProgram){
    glUseProgram(shaderProgram);
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    transform.UpdateModelMatrix();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &transform.model[0][0]);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}