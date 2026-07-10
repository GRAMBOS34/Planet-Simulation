#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform {
public:
    Transform(
        const glm::vec3& position = glm::vec3(),
        const glm::vec3& rotation = glm::vec3(),
        const glm::vec3& scale = glm::vec3(1.0f,1.0f,1.0f)
    ) : m_position(position), m_rotation(rotation), m_scale(scale) {}

    /**
     * @brief Get the Model matrix
     * 
     * @return glm::mat4 - The model matrix - a product of the scale, rotation, and position matrices
     */
    inline glm::mat4 GetModel() const {
        glm::mat4 positionMatrix = glm::translate(m_position);
        glm::mat4 scaleMatrix = glm::scale(m_scale);

        // TODO Turn the rotation stuff into a quaternion, mainly to avoid gimbal lock
        glm::mat4 rotation_X = glm::rotate(m_rotation.x, glm::vec3(1.0, 0, 0));
        glm::mat4 rotation_Y = glm::rotate(m_rotation.y, glm::vec3(0, 1.0, 0));
        glm::mat4 rotation_Z = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1.0));

        glm::mat4 rotationMatrix = rotation_Z * rotation_Y * rotation_X; // because of how matrix multiplication works

        return positionMatrix * rotationMatrix * scaleMatrix; // the order of the application is backwards because of matrix multiplication
    }

    // Getters
    inline glm::vec3& GetPosition() { return m_position; }
    inline glm::vec3& GetRotation() { return m_rotation; }
    inline glm::vec3& GetScale() { return m_scale; }

    // Setters
    inline void SetPosition(const glm::vec3& position) { m_position = position; }
    inline void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; }
    inline void SetScale(const glm::vec3& scale) { m_scale = scale; }

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation; // TODO figure out how to turn this into quaternions
    glm::vec3 m_scale;
};

#endif
