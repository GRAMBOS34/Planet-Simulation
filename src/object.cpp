#include "../include/object.h"
#include <SDL2/SDL_sensor.h>

/**
 * @brief Construct a new Object::Object object
 *
 * @param mesh - Mesh/vertex data of the object
 * @param glShapeType - The type of shape expected for the draw function
 * @param position - The object's initial position. At the origin by default
 */
Object::Object(
    const Mesh* mesh,
    GLenum glShapeType,
    glm::vec3 position
) : mesh(mesh), m_shapeTypeVal(glShapeType){
    transform.SetPosition(position);

    // Because for some reason it won't work properly
    // if i just declared a default value in the private
    // section of the class
    m_color = glm::vec3(1.0f, 1.0f, 1.0f);
    m_acceleration = glm::vec3(0,0,0);
    m_velocity = glm::vec3(0,0,0);
}

/**
 * @brief Integrates acceleration to get velocity
 * 
 * @param acceleration - acceleration vector
 * @param deltaTime - time between frames
 */
void Object::Accelerate(glm::vec3 acceleration, float deltaTime){
    m_velocity += (acceleration * deltaTime);
}

/**
 * @brief Integrates velocity to get position
 * 
 * @param deltaTime - time between frames
 */
void Object::UpdatePosition(float deltaTime){
    // * new position = old position + (velocity * time between frames)
    glm::vec3 oldPosition = transform.GetPosition();
    glm::vec3 newPosition = oldPosition + (m_velocity * deltaTime);

    transform.SetPosition(newPosition);
}

/**
 * @brief Update the scale of the object
 *
 * @param newScale
 */
void Object::Scale(glm::vec3 newScale){
    transform.GetScale() = newScale;
}
