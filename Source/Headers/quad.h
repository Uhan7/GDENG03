#pragma once

#include <glad/glad.h>
#include <memory>

#include <glm/vec3.hpp>

#include "structs.h"
#include "transform.h"

class Quad{
    public:
        Quad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 color);
        ~Quad();

        Transform transform; // Ermm bad practice to put this in public? idk what if idgaf lol

    private:
        ColorVertex vertices[4]; // Hmm I kinda don't like "ColorVertex" but wtvr
        unsigned int indices[6] = {0, 1, 2, 1, 2, 3};
        unsigned int VAO, VBO, EBO;

    public:
        void Draw(unsigned int shaderProgram);
        void SetupMesh();
        void SetPosition(glm::vec3 newPosition);

        static std::unique_ptr<Quad> MakeSquare(glm::vec3 center, float sideLength, glm::vec3 color);
};