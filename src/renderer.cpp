#include "../include/renderer.h"


// This renderer class exists because the camera and shader are things
// that each object uses
Renderer::Renderer(Camera* camera, Shader* shader){
    m_camera = camera;
    m_shader = shader;
}

/**
 * @brief Draw an object using the renderer
 *
 * @param object - Object::Object to be drawn
 */
void Renderer::Draw(Object& object){
    if (!object.mesh) return;

    // Update the position in the shader
    m_shader->Update(object.transform, *m_camera);

    // Update the color
    m_shader->SetColor(object.GetColor());

    object.mesh->Draw(object.GetShapeType());
}
