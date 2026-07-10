#include "../include/camera.h"

/**
 * @brief Construct a new Camera:: Camera object
 * 
 * @param pos - Initial position of the camera in 3D space
 * @param fov - FOV of the camera
 * @param aspect - Aspect ratio of the display
 * @param zNear - Minimum draw distance
 * @param zFar - Maximum draw distance
 */
Camera::Camera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar) {
    perspective = glm::perspective(fov, aspect, zNear, zFar);
    cameraPosition = pos;

    rotationForward = glm::vec3(0, 0, -1);
    rotationUp = glm::vec3(0, 1, 0);
}