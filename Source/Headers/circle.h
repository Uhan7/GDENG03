#pragma once

#include <glad/glad.h>
#include <memory>
#include <vector>

#include <glm/vec3.hpp>

#include "structs.h"
#include "transform.h"

class Circle{
    public:
        Circle(glm::vec3 origin, float diameter, glm::vec3 color);
        ~Circle();

        Transform transform;

    private:
        std::vector<ColorVertex> vertices;
        unsigned int VAO, VBO, EBO;

    public:
        void Draw(unsigned int shaderProgram);
        void SetupMesh();
        void SetPosition(glm::vec3 newPosition);
};