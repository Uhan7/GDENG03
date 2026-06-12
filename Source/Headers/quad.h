#pragma once

#include <glad/glad.h>

#include "structs.h"

class Quad{
    public:
        Quad(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4, Vec3 color);
        void Draw(unsigned int shaderProgram);

    private:
        colorVertex vertices[4];
        unsigned int indices[6] = {0, 1, 2, 1, 2, 3};
        unsigned int VAO, VBO, EBO;

        void SetupMesh();
};