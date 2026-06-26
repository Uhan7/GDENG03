#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

// #include "structs.h"

class Transform{
    public:
        // Default Properties
        glm::mat4 model = glm::mat4(1.0f);
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);

        // Default Deltas -> is dat what I shud call em..?
        glm::vec3 velocity =  glm::vec3(0.0f);

        // Move Functions
        void ChangePosition(glm::vec3 offsetPosition);
        void ChangeRotation(glm::vec3 offsetRotation); // -> gawd this prolly needs to be changed to use QUATERNIRNOSINIONS
        void ChangeScale(glm::vec3 offsetScale);

        // Delta Magic
        void MoveWithVelocity();

        // Update Function
        void UpdateModelMatrix();
};