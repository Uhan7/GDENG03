#pragma once

#include <glad/glad.h>
#include <memory>

#include "structs.h"
#include "transform.h"

class Quad{
    public:
        Quad(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 p4, Vec3 color);
        ~Quad();

        Transform transform; // Ermm bad practice to put this in public? idk what if idgaf lol

    private:
        ColorVertex vertices[4]; // Hmm I kinda don't like "ColorVertex" but wtvr
        unsigned int indices[6] = {0, 1, 2, 1, 2, 3};
        unsigned int VAO, VBO, EBO;

    public:
        void Draw(unsigned int shaderProgram);
        void SetupMesh();
        void SetPosition(Vec3 newPosition);

        static std::unique_ptr<Quad> MakeSquare(Vec3 center, float sideLength, Vec3 color);
};