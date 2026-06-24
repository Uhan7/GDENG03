#include "transform.h"

void Transform::SetPosition(glm::vec3 newPosition){
    position = newPosition;
}

void Transform::ChangePosition(glm::vec3 offsetPosition){
    position.x += offsetPosition.x;
    position.y += offsetPosition.y;
    position.z += offsetPosition.z;
}

void Transform::MoveWithVelocity(){
    position.x += velocity.x;
    position.y += velocity.y;
    position.z += velocity.z;
}