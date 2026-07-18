#include "../include/mesh.hpp"

/**
 * @brief Construct a new Mesh:: Mesh object
 *
 * @param vertices - Vertex data of the mesh
 * @param numVertices - the number of verticies
 */
Mesh::Mesh(Vertex *vertices, unsigned int numVertices){
    m_drawCount = numVertices;

    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    // Basically move data to the GPU
    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(
        GL_ARRAY_BUFFER,
        (numVertices * sizeof(vertices[0])),
        vertices,
        GL_DYNAMIC_DRAW // Optimizes for any frequent overwrites to vertex data
    );

    // Tell the GPU how to interpret said data
    glEnableVertexAttribArray(0); // 0 here is the id of the vertex shader (i think i just followed a tutorial tbh)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

// Delete the mesh
Mesh::~Mesh(){
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

// Draw something
void Mesh::Draw(GLenum glShapeType) const {
    glBindVertexArray(m_vertexArrayObject);

    glDrawArrays(glShapeType, 0, m_drawCount);

    glBindVertexArray(0);
}
