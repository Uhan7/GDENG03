#include "circle.h"

Circle::Circle(glm::vec3 origin, float radius, glm::vec3 color){
    transform.SetPosition(origin);
    
    vertices.push_back({glm::vec3(0.0f, 0.0f, 0.0f), color}); // Center Vertex First

    for (int i = 0; i <= segments; i++){
        float angle = (2 * M_PI * i) / segments;
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);

        vertices.push_back({glm::vec3(x, y, 0.0f), color});
    }

    SetupMesh();
}

Circle::~Circle(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Circle::SetupMesh(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ColorVertex), vertices.data(), GL_STATIC_DRAW);

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
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
}

void Circle::SetPosition(glm::vec3 newPosition){
    transform.position = newPosition;
}