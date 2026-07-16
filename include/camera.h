#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL_events.h>
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

    void UpdateCameraPosition(SDL_Event& event);
    void RotateCamera(float deltaPitch, float deltaYaw);

    inline glm::mat4 GetViewProjection() const {
        glm::mat4 viewMatrix = glm::lookAt(m_cameraPosition, m_cameraPosition + m_rotationForward, m_rotationUp);
        return m_perspective * viewMatrix;
    }

    inline void setCameraPosition(glm::vec3 newCamPosition) { m_cameraPosition = newCamPosition; }

private:
    glm::mat4 m_perspective;
    glm::vec3 m_cameraPosition;

    // Rotation stuff
    glm::vec3 m_rotationForward;
    glm::vec3 m_rotationUp;

    float m_pitch;
    float m_yaw;
};

#endif
