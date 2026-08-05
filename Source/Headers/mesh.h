#pragma once

#include <iostream>
#include <filesystem>

#include <glad/glad.h>
#include <vector>
#include <string>
#include <glm/vec3.hpp>

#include "structs.h"
#include "transform.h"

const std::filesystem::path MODEL_PATH = "../../../Models";

class Mesh {
public:
    Mesh(const std::string& objPath);
    ~Mesh();

    Transform transform;

    void Draw(unsigned int shaderProgram);

private:
    std::vector<UvVertex> vertices;
    unsigned int VAO = 0;
    unsigned int VBO = 0;

    void LoadObj(const std::string& objPath);
    void SetupMesh();
};