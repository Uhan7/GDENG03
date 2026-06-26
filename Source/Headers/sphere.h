#pragma once

#include <glad/glad.h>
#include <memory>
#include <vector>
#include <cmath>

#include <glm/vec3.hpp>

#include "structs.h"
#include "transform.h"

class Sphere{
    public:
        Sphere(glm::vec3 origin, float radius, glm::vec3 color);
        ~Sphere();

        Transform transform;

    private:
        std::vector<ColorVertex> vertices;
        std::vector<unsigned int> indices;
        unsigned int VAO, VBO, EBO;
        int segmentsX = 64;
        int segmentsY = 64;

    public:
        void Draw(unsigned int shaderProgram);
        void SetupMesh();
        void SetPosition(glm::vec3 newPosition);
};