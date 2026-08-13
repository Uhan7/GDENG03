#include "level_renderer.h"

void ApplyLevelObjectTransform(const LevelObject& object, Transform& transform){
    transform.position = object.position;
    transform.rotation = object.rotation;
    transform.scale = object.scale;
}

void DrawLevelObject(const LevelObject& object, Quad& plane, Cube& cube, Sphere& sphere, Capsule& capsule, unsigned int shaderProgram){
    switch (object.type){
        case PrimitiveType::Plane:
            ApplyLevelObjectTransform(object, plane.transform);
            plane.Draw(shaderProgram);
            break;

        case PrimitiveType::Cube:
            ApplyLevelObjectTransform(object, cube.transform);
            cube.Draw(shaderProgram);
            break;

        case PrimitiveType::Sphere:
            ApplyLevelObjectTransform(object, sphere.transform);
            sphere.Draw(shaderProgram);
            break;

        case PrimitiveType::Capsule:
            ApplyLevelObjectTransform(object, capsule.transform);
            capsule.Draw(shaderProgram);
            break;
    }
}