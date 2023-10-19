#include "Camera.h"
#include <ofQuaternion.h>

void Camera::setPosition()
{
    Vector particlePosition = followParticule->GetPosition();
    position.set(particlePosition.get_x() + cos(rollAngle) * cos(pitchAngle) * norm, particlePosition.get_y() + norm * sin(rollAngle), particlePosition.get_z() + norm * cos(rollAngle) * sin(pitchAngle));
    cam.setPosition(position.get_x(), position.get_y(), position.get_z());
    Vector direction = particlePosition - position;
    direction = direction.normalisation();

    cam.lookAt(particlePosition.toVec3(), glm::vec3(0,-1,0));
}

Camera::Camera()
{
}

Camera::Camera(Vector startPosition, Particule* followParticule)
{
    this->position = startPosition;
    setParticuleFollow(startPosition, followParticule);
}




void Camera::changeNorm(double changeValue) {
    norm += (changeValue * speedZoom);
    norm = max(norm, 0.0);
    
}

void Camera::changeRollAngle(double changeValue) {
    rollAngle += changeValue * speedAngle;

    rollAngle = max(-maxAngle, rollAngle);
    rollAngle = min(maxAngle, rollAngle);
    // Appliquer la rotation autour de la particule ici

}

void Camera::changePitchAngle(double changeValue) {
    pitchAngle += changeValue * speedAngle;
    pitchAngle = fmod(pitchAngle, 2 * PI);


}

void Camera::setParticuleFollow(Vector new_position, Particule *newParticule)
{
    this->position = new_position;
    this->followParticule = newParticule;
    this->norm = followParticule->GetPosition().distance(position);
    Vector diff = position - followParticule->GetPosition();
    this->rollAngle = atan2(diff.get_y(), diff.get_x());
    this->pitchAngle = asin((diff.get_z()) / norm);
  
    if (rollAngle > maxAngle)
    {
        pitchAngle += PI;
        rollAngle -= PI;
    }
    else if (rollAngle < -maxAngle)
    {
        pitchAngle -= PI;
        rollAngle += PI;
    }
   
    
    setPosition();
}



Vector Camera::getPosition() {
    return position;
}

void Camera::beginCam() {
    cam.begin();
}

void Camera::endCam() {
    cam.end();
}