#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

#include "transform.hpp"
#include "camera.hpp"

class Shader {
public:
    Shader(const std::string& filename);

    void Bind();
    void Update(const Transform &transform, const Camera& camera);
    virtual ~Shader();

    void SetColor(const glm::vec3& color);

    inline int getModelMatrixLocation() {
        return uniforms[TRANSFORM_U]; // returns the transform/model matrix
    }

private:
    static const unsigned int NUM_SHADER = 2;
    Shader(const Shader& other) = delete;
    void operator=(const Shader& other) = delete;

    enum{
        TRANSFORM_U,
        COLOR_U,
        NUM_UNIFORMS
    };

    GLuint program;
    GLuint shaders[NUM_SHADER];
    GLuint uniforms[NUM_UNIFORMS];
};

#endif
