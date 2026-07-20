#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex {
public:
    Vertex(const glm::vec3& pos) {
        this -> pos = pos;
    }
private:
    glm::vec3 pos;
};

class Mesh {
public:
    Mesh(Vertex *vertices, unsigned int numVertices, GLenum glShapeType);

    // ! Might have to figure out how to extend this to textures
    // Although that's a problem for another time
    void Draw() const;

    virtual ~Mesh();

    // Getters
    inline GLuint GetVBO() const { return m_vertexArrayObject; }
    inline GLenum GetShapeType() const { return m_shapeType; }

private:
    Mesh(const Mesh& other) = delete;
    void operator=(const Mesh& other) = delete;

    enum {
        POSITION_VB,
        NUM_BUFFERS
    };

    GLenum m_shapeType;
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;

};

namespace PrimitiveShapes {
    Mesh Circle (float radius, int sides = 20);
    Mesh Quad(float x, float y);
    Mesh Line(glm::vec3& startPos, glm::vec3& endPos);
    Mesh Sphere(float radius);
};

#endif
