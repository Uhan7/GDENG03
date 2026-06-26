#pragma once

#include <glad/glad.h>
#include <memory>
#include <vector>
#include <cmath>

#include <glm/vec3.hpp>

#include "structs.h"
#include "transform.h"

class Cylinder{
    public:
        Cylinder(glm::vec3 origin, float radius, float height, glm::vec3 color);
        ~Cylinder();

        Transform transform;

    private:
        std::vector<ColorVertex> vertices;
        std::vector<unsigned int> indices;
        int segments = 64;
        unsigned int VAO, VBO, EBO;

    public:
        void Draw(unsigned int shaderProgram);
        void SetupMesh();
        void SetPosition(glm::vec3 newPosition);
};