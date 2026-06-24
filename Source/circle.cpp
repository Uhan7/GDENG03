#include "circle.h"

Circle::Circle(glm::vec3 origin, float diameter, glm::vec3 color){
    // Whatever circle logic here

    SetupMesh();
}

Circle::~Circle(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Circle::SetupMesh(){
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

void Circle::Draw(unsigned int shaderProgram){
    glUseProgram(shaderProgram);
    int offsetLoc = glGetUniformLocation(shaderProgram, "offset");
    glUniform3f(offsetLoc, transform.position.x, transform.position.y, transform.position.z);
    glBindVertexArray(VAO);
    // triangle fan or whatever
}

void Circle::SetPosition(glm::vec3 newPosition){
    transform.position = newPosition;
}