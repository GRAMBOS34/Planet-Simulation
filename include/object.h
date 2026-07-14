#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <iostream>

#include "transform.h"
#include "mesh.h"
#include "shader.h"

class Object {
public:
    Transform transform;
    const Mesh* mesh;

    Object(
        const Mesh* mesh,
        GLenum glShapeType,
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)
    );

    void UpdatePosition(float deltaTime);

    void Accelerate(glm::vec3 acceleration, float deltaTime);
    void Scale(glm::vec3 newScale);

    // Creates a default destructor
    virtual ~Object() = default;

    // Getters
    inline GLenum GetShapeType() { return m_shapeTypeVal; }
    inline glm::vec3 GetAcceleration() { return m_acceleration; }
    inline glm::vec3 GetVelocity() { return m_velocity; }
    inline glm::vec3 GetColor() { return m_color; }
    inline float GetMass() { return m_mass; }

    // Setters
    inline void SetColor(const glm::vec3& newColor) { m_color = newColor; }
    inline void SetMass(const float newMass) { m_mass = newMass; }
    inline void SetVelocity(const glm::vec3& newVelocity) { m_velocity = newVelocity; }

private:
    Camera* m_camera = nullptr;
    Shader* m_shader = nullptr;

    GLenum m_shapeTypeVal;
    glm::vec3 m_color;

    // Physics values
    // But the calculations will be done somewhere else
    glm::vec3 m_acceleration;
    glm::vec3 m_velocity;
    float m_mass;
};

#endif
