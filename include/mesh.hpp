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
    Mesh(Vertex *vertices, unsigned int numVertices);

    // ! Might have to figure out how to extend this to textures
    // Although that's a problem for another time
    void Draw(GLenum glShapeType) const;

    virtual ~Mesh();

    // Getters
    inline GLuint GetVBO() { return m_vertexArrayObject; }

private:
    Mesh(const Mesh& other) = delete;
    void operator=(const Mesh& other) = delete;

    enum {
        POSITION_VB,
        NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;

};

namespace PrimitiveShapes {
    Mesh Circle (float radius, int sides = 20);
    Mesh Quad(float x, float y);
    Mesh Line(glm::vec3& startPos, glm::vec3& endPos);
};

#endif
