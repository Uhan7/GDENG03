#pragma once

#include "level_data.h"
#include "quad.h"
#include "cube.h"
#include "sphere.h"
#include "capsule.h"

void ApplyLevelObjectTransform(const LevelObject& object, Transform& transform);
void DrawLevelObject(const LevelObject& object, Quad& plane, Cube& cube, Sphere& sphere, Capsule& capsule, unsigned int shaderProgram);