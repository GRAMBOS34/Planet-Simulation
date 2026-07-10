#ifndef CAMERA_H
#define CAMERA_H

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera{
public:
    Camera(
        const glm::vec3 &pos,
        float fov, float aspect,
        float zNear,
        float zFar
    );

    inline glm::mat4 GetViewProjection() const {
        glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraPosition + rotationForward, rotationUp);
        return perspective * viewMatrix;
    }

private:
    glm::mat4 perspective;
    glm::vec3 cameraPosition;

    // Rotation stuff
    glm::vec3 rotationForward;
    glm::vec3 rotationUp;
};

#endif
