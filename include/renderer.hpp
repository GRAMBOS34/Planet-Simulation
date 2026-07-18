#ifndef RENDERER_H
#define RENDERER_H

#include "camera.hpp"
#include "shader.hpp"
#include "object.hpp"

class Renderer {
public:
    Renderer(Camera* camera, Shader* shader);

    void Draw(Object& object);

private:
    Camera* m_camera = nullptr;
    Shader* m_shader = nullptr;

};

#endif
