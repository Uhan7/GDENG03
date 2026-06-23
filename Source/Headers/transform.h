#pragma once

#include "structs.h"

class Transform{
    public:
        Vec3 position{0.0f, 0.0f, 0.0f};
        Vec3 rotation{0.0f, 0.0f, 0.0f};
        Vec3 scale{1.0f, 1.0f, 1.0f};

        float speedX = 0;
        float speedY = 0;

    public:
        void SetPosition(Vec3 newPosition);
        void ChangePosition(Vec3 offsetPosition);
        void MoveWithSpeed();
};