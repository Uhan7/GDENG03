#include "transform.h"

void Transform::ChangePosition(glm::vec3 offsetPosition){
    position += offsetPosition;
}

void Transform::ChangeRotation(glm::vec3 offsetRotation){
    rotation += offsetRotation;
}

void Transform::ChangeScale(glm::vec3 offsetScale){
    scale += offsetScale;
}

void Transform::MoveWithVelocity(){
    position += velocity;
}

void Transform::RotateWithAngularVelocity()
{
    rotation += angularVelocity;
}

void Transform::UpdateModelMatrix()
{
    model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
}