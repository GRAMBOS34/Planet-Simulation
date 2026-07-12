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
    m_acceleration = glm::vec3(0,0,0);
}

void Object::Accelerate(glm::vec3 acceleration){
    // * new position = old position + (velocity * time between frames)
    m_velocity += acceleration;
}

void Object::UpdatePosition(float deltaTime){
    transform.GetPosition() += m_velocity / 1000.0f * deltaTime;
}

/**
 * @brief Update the scale of the object
 *
 * @param newScale
 */
void Object::Scale(glm::vec3 newScale){
    transform.GetScale() = newScale;
}
