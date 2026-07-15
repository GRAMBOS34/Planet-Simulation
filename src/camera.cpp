#include "../include/camera.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>

#include <SDL2/SDL_stdinc.h>
#include <iostream>

const float MOVEMENT_SPEED_PX = 1.5f;
const float ROTATION_SPEED_SENS = 0.5f;

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
    m_perspective = glm::perspective(fov, aspect, zNear, zFar);
    m_cameraPosition = pos;

    m_rotationForward = glm::vec3(0, 0, -1);
    m_rotationUp = glm::vec3(0, 1, 0);
}

void Camera::RotateCamera(float deltaPitch, float deltaYaw){
    m_pitch += glm::radians(deltaPitch);
    m_yaw += glm::radians(deltaYaw);

    // Constrain pitch so the camera doesn't flip upside down
    // (90 degrees in radians is ~1.55)
    if (m_pitch > 1.55f)  m_pitch = 1.55f;
    if (m_pitch < -1.55f) m_pitch = -1.55f;

    glm::vec3 newForward;
    newForward.x = m_rotationForward.x;
    newForward.y = sin(m_pitch);
    newForward.z = m_rotationForward.z;

    m_rotationForward = glm::normalize(newForward);

    // Recalculate local Right and Up to keep them perpendicular
    glm::vec3 globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 localRight = glm::normalize(glm::cross(m_rotationForward, globalUp));

    m_rotationUp = glm::normalize(glm::cross(localRight, m_rotationForward));
}

void Camera::UpdateCameraPosition(){
    /*
     * Continuously poll the keyboard to update the camera
     * position to create movement
     */
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    // * Camera Positioning
    // Z-axis movement
    if(keystate[SDL_SCANCODE_W]){
        m_cameraPosition.z -= MOVEMENT_SPEED_PX;
    }
    if(keystate[SDL_SCANCODE_S]){
        m_cameraPosition.z += MOVEMENT_SPEED_PX;
    }

    // X-axis movement
    if(keystate[SDL_SCANCODE_A]){
        m_cameraPosition.x -= MOVEMENT_SPEED_PX;
    }
    if(keystate[SDL_SCANCODE_D]){
        m_cameraPosition.x += MOVEMENT_SPEED_PX;
    }

    // Y-axis movement
    if(keystate[SDL_SCANCODE_LCTRL]){
        m_cameraPosition.y -= MOVEMENT_SPEED_PX;
    }
    if(keystate[SDL_SCANCODE_SPACE]){
        m_cameraPosition.y += MOVEMENT_SPEED_PX;
    }

    float cameraPitch = 0.0f;

    // ! Camera rotation test
    if(keystate[SDL_SCANCODE_I]){
        cameraPitch += 0.1f;
        if(cameraPitch < 1.55f){
            m_cameraPosition.x = cameraPitch;
        }
    }

    // * Camera Rotation

    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
        // Left mouse button is currently being held down
        // (e.g., continuously spraying a weapon or dragging an item)

        // TODO: Make sure that when MMB is held down
        // the mouse can move to rotate the camera
        SDL_SetRelativeMouseMode(SDL_TRUE);

        int xRel = 0;
        int yRel = 0;
        SDL_GetRelativeMouseState(&xRel, &yRel);

        float pitch = xRel * ROTATION_SPEED_SENS;
        float yaw = yRel * ROTATION_SPEED_SENS;

        RotateCamera(pitch, yaw);

        // std::cout << xRel << ", " << yRel << "\n";
        std::cout << m_rotationForward.x << ", " << m_rotationForward.y << ", " << m_rotationForward.z << "\n";
    }
    else SDL_SetRelativeMouseMode(SDL_FALSE);
}
