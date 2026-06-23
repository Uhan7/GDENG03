#include "transform.h"

void Transform::SetPosition(Vec3 newPosition){
    position = newPosition;
}

void Transform::ChangePosition(Vec3 offsetPosition){
    position.x += offsetPosition.x;
    position.y += offsetPosition.y;
    position.z += offsetPosition.z;
}

void Transform::MoveWithSpeed(){
    position.x += speedX;
    position.y += speedY;
}