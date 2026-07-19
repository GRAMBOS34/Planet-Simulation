#include "../include/camera.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>

#include <SDL2/SDL_stdinc.h>
#include <glm/geometric.hpp>

const float MOVEMENT_SPEED_PX = 1.5f;
const float ROTATION_SPEED_SENS = 1.0f;

const glm::vec3 globalUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool isRelativeMode = false;

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

    m_localForward = glm::vec3(0, 0, -1);
    m_localUp = glm::vec3(0, 1, 0);

    m_localRight = glm::normalize(glm::cross(m_localForward, globalUp));
}

void Camera::RotateCamera(float deltaPitch, float deltaYaw){
    m_pitch += glm::radians(deltaPitch);
    m_yaw += glm::radians(deltaYaw);

    // Constrain pitch so the camera doesn't flip upside down
    // (90 degrees in radians is ~1.55)
    if (m_pitch > 1.55f)  m_pitch = 1.55f;
    if (m_pitch < -1.55f) m_pitch = -1.55f;

    // Point the forward vector somewhere else
    // This shit uses some fairly complex linear algebra
    // which I can't fully explain yet
    glm::vec3 newForward;
    newForward.x = cos(m_pitch) * cos(m_yaw);
    newForward.y = sin(m_pitch);
    newForward.z = cos(m_pitch) * sin(m_yaw);

    // We normalize the forward vector to make sure its magnitude stays at 1
    m_localForward = glm::normalize(newForward);

    // Recalculate local Right and Up to keep them perpendicular
    m_localRight = glm::normalize(glm::cross(m_localForward, globalUp));

    m_localUp = glm::normalize(glm::cross(m_localRight, m_localForward));
}

/*
 * Continuously poll the keyboard to update the camera
 * position to create movement
 */
void Camera::UpdateCameraPosition(){
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    // * Camera Positioning
    // Z-axis movement
    if(keystate[SDL_SCANCODE_W]){
        m_cameraPosition += m_localForward * MOVEMENT_SPEED_PX;
    }
    if(keystate[SDL_SCANCODE_S]){
        m_cameraPosition -= m_localForward * MOVEMENT_SPEED_PX;
    }

    // X-axis movement
    if(keystate[SDL_SCANCODE_D]){
        m_cameraPosition += m_localRight * MOVEMENT_SPEED_PX;
    }
    if(keystate[SDL_SCANCODE_A]){
        m_cameraPosition -= m_localRight * MOVEMENT_SPEED_PX;
    }

    // Y-axis movementc
    if(keystate[SDL_SCANCODE_LCTRL]){
        m_cameraPosition -= m_localUp * MOVEMENT_SPEED_PX;
    }
    if(keystate[SDL_SCANCODE_SPACE]){
        m_cameraPosition += m_localUp * MOVEMENT_SPEED_PX;
    }

    // * Camera Rotation
    // Get's the mouse state and its position
    // There's probably a way to do this without having to get the mouse coordinates
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
        int yaw = 0;
        int pitch = 0;
        SDL_GetRelativeMouseState(&yaw, &pitch); // Get relative position instead of absolute position
        SDL_ShowCursor(SDL_DISABLE); // Hide cursor

        // This is here mainly to avoid the camera suddenly turning when
        // the middle mouse button is clicked
        if (isRelativeMode == true){
            // Pitch is negative because I prefer moving down to go down
            // Although I can probably make this togglable at some point
            RotateCamera(-pitch, yaw);
        }

        isRelativeMode = true;
    }
    else{
        SDL_SetRelativeMouseMode(SDL_FALSE);
        SDL_ShowCursor(SDL_ENABLE);
        isRelativeMode = false;
    }
}
