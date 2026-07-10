#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "shader.h"
#include "object.h"

class Renderer {
public:
    Renderer(Camera* camera, Shader* shader);

    void Draw(Object& object);

private:
    Camera* m_camera = nullptr;
    Shader* m_shader = nullptr;

};

#endif
