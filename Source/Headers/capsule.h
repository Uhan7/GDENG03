#pragma once

#include <glad/glad.h>
#include <memory>
#include <vector>
#include <cmath>

#include <glm/vec3.hpp>

#include "structs.h"
#include "transform.h"

class Capsule{
    public:
        Capsule(glm::vec3 origin, float radius, float totalHeight, glm::vec3 color);
        ~Capsule();

        Transform transform;

    private:
        std::vector<ColorVertex> vertices;
        std::vector<unsigned int> indices;

        int segments = 32;
        int hemisphereRings = 16;

        unsigned int VAO, VBO, EBO;

    public:
        void Draw(unsigned int shaderProgram);
        void SetupMesh();
};