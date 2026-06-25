#pragma once

#include <glad/glad.h>
#include <memory>
#include <vector>
#include <cmath>

#include <glm/vec3.hpp>

#include "structs.h"
#include "transform.h"

class Circle{
    public:
        Circle(glm::vec3 origin, float radius, glm::vec3 color);
        ~Circle();

        Transform transform;

    private:
        std::vector<ColorVertex> vertices;
        int segments = 64; // This is for 2d fo now
        unsigned int VAO, VBO; // No EBO for trianglefan

    public:
        void Draw(unsigned int shaderProgram);
        void SetupMesh();
        void SetPosition(glm::vec3 newPosition);
};