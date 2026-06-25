#pragma once

#include <glad/glad.h>
#include <memory>

#include <glm/vec3.hpp>

#include "structs.h"
#include "transform.h"

class Cube{
    public:
        Cube(glm::vec3 origin, float sideLength, glm::vec3 color);
        ~Cube();

        Transform transform; // Ermm bad practice to put this in public? idk what if idgaf lol

    private:
        ColorVertex vertices[8]; // Hmm I kinda don't like "ColorVertex" but wtvr
        unsigned int indices[36] = {
            0, 1, 2,  2, 3, 0, // Front face
            1, 5, 6,  6, 2, 1, // Right face
            5, 4, 7,  7, 6, 5, // Back face
            4, 0, 3,  3, 7, 4, // Left face
            4, 5, 1,  1, 0, 4, // Bottom face
            3, 2, 6,  6, 7, 3 // Top face
        };
        unsigned int VAO, VBO, EBO;

    public:
        void Draw(unsigned int shaderProgram);
        void SetupMesh();
        void SetPosition(glm::vec3 newPosition);
};