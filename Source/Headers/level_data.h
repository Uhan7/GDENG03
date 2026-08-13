#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>

enum class PrimitiveType{
    Plane,
    Cube,
    Sphere,
    Capsule
};

struct LevelObject{
    PrimitiveType type = PrimitiveType::Cube;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

    bool hasRigidBody = false;
};

struct LevelData{
    std::vector<LevelObject> objects;
};

inline std::string PrimitiveTypeToString(PrimitiveType type){
    switch (type){
        case PrimitiveType::Plane: return "plane";
        case PrimitiveType::Cube: return "cube";
        case PrimitiveType::Sphere: return "sphere";
        case PrimitiveType::Capsule: return "capsule";
        default: return "cube";
    }
}

inline bool StringToPrimitiveType(const std::string& text, PrimitiveType& outType){
    if (text == "plane"){
        outType = PrimitiveType::Plane;
        return true;
    }
    if (text == "cube"){
        outType = PrimitiveType::Cube;
        return true;
    }
    if (text == "sphere"){
        outType = PrimitiveType::Sphere;
        return true;
    }
    if (text == "capsule"){
        outType = PrimitiveType::Capsule;
        return true;
    }

    return false;
}