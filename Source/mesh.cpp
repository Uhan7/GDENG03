#include "mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Mesh::Mesh(const std::string& objPath, glm::vec3 color){
    LoadObj(objPath, color);

    transform.position = glm::vec3(0.f, 0.f, 0.f);

    SetupMesh();
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::LoadObj(const std::string& objName, glm::vec3 color){
    namespace fs = std::filesystem;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;

    fs::path modelPath = fs::absolute(fs::path("../../../Models") / objName);
    std::string modelPathString = modelPath.string();
    std::string baseDir = modelPath.parent_path().string();

    std::cout << "cwd: " << fs::current_path() << std::endl;
    std::cout << "Loading OBJ path in: " << modelPathString << std::endl;
    std::cout << "exists? " << fs::exists(modelPath) << std::endl;

    bool ok = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPathString.c_str(), baseDir.c_str());

    if (!warn.empty()) std::cout << "WARNING on tiny_obj_loader: " << warn << std::endl;
    if (!err.empty()) std::cout << "ERROR on tiny_obj_loader: " << err << std::endl;
    if (!ok) return;

    vertices.clear();

    for (const auto& shape : shapes){
        for (const auto& index : shape.mesh.indices){
            int vi = index.vertex_index;

            glm::vec3 pos;
            pos.x = attrib.vertices[3 * vi + 0];
            pos.y = attrib.vertices[3 * vi + 1];
            pos.z = attrib.vertices[3 * vi + 2];

            vertices.push_back({pos, color});
        }
    }
}

void Mesh::SetupMesh(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(ColorVertex),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::Draw(unsigned int shaderProgram){
    glUseProgram(shaderProgram);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    transform.UpdateModelMatrix();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &transform.model[0][0]);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
}