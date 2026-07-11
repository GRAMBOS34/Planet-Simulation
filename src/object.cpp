#include "../include/object.h"


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
    m_velocity = glm::vec3(0,0,0);
}

/**
 * @brief Update the current position with the velocity vector
 *
 * @param velocity
 * @param deltaTime
 */
void Object::Move(glm::vec3 acceleration, float deltaTime){
    // * This line is essentially integrating acceleration to get velocity
    // * But, each iteration of the update loop integrates this again to get position

    // * new position = old position + (velocity * time between frames)
    transform.GetPosition() += acceleration * deltaTime;
}

/**
 * @brief Update the scale of the object
 *
 * @param newScale
 */
void Object::Scale(glm::vec3 newScale){
    transform.GetScale() = newScale;
}
