#pragma once

#include "structs.h"

class Transform{
    public:
        Vec3 position{0.0f, 0.0f, 0.0f};
        Vec3 rotation{0.0f, 0.0f, 0.0f};
        Vec3 scale{1.0f, 1.0f, 1.0f};

        Vec3 velocity{0.0f, 0.0f, 0.0f};

    public:
        void SetPosition(Vec3 newPosition);
        void ChangePosition(Vec3 offsetPosition);
        void MoveWithVelocity();
};