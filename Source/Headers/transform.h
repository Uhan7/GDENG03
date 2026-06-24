#pragma once

#include <glm/vec3.hpp>

// #include "structs.h"

class Transform{
    public:
        glm::vec3 position{0.0f, 0.0f, 0.0f};
        glm::vec3 rotation{0.0f, 0.0f, 0.0f};
        glm::vec3 scale{1.0f, 1.0f, 1.0f};

        glm::vec3 velocity{0.0f, 0.0f, 0.0f};

    public:
        void SetPosition(glm::vec3 newPosition);
        void ChangePosition(glm::vec3 offsetPosition);
        void MoveWithVelocity();
};