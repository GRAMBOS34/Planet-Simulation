#include "../include/mesh.hpp"

/**
 * @brief Construct a new Mesh:: Mesh object
 *
 * @param vertices - Vertex data of the mesh
 * @param numVertices - the number of verticies
 */
Mesh::Mesh(Vertex *vertices, unsigned int numVertices, GLenum glShapeType){
    m_drawCount = numVertices;
    m_shapeType = glShapeType;

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
void Mesh::Draw() const {
    glBindVertexArray(m_vertexArrayObject);

    glDrawArrays(m_shapeType, 0, m_drawCount);

    glBindVertexArray(0);
}

// ! ---------------- PRIMITIVE SHAPES -------------------------

// * This function only creates a 2D circle
Mesh PrimitiveShapes::Circle(float radius, int edges){
    std::vector<Vertex> verticies;
    verticies.reserve(edges + 2);

    verticies.emplace_back(glm::vec3(0,0,0)); // Add the centre point

    for (int i = 0; i <= edges; i++){
        float angle = 2.0f * 3.14159f * i / edges; // Calculate angle in radians
        float x_point = (radius * cos(angle));
        float y_point = (radius * sin(angle));

        verticies.emplace_back(glm::vec3(x_point, y_point, 0)); // (x,y,z)
    }

    return Mesh(verticies.data(), verticies.size(), GL_TRIANGLE_FAN);
}

// TODO: Make this form a quad given only x and y lengths
Mesh PrimitiveShapes::Quad(float len_x, float len_y){
    std::vector<Vertex> vertices;

    vertices = {
        // Quad
        // ! CAN ONLY BE WRITTEN LIKE THIS WHEN USING GL_TRIANGLE_STRIP
        Vertex(glm::vec3(0, 0, 0)), Vertex(glm::vec3(len_x, 0, 0)), Vertex(glm::vec3(0, len_y, 0)), Vertex(glm::vec3(len_x, len_y, 0))
    };

    return Mesh(vertices.data(), vertices.size(), GL_TRIANGLE_STRIP);
}

Mesh PrimitiveShapes::Line(glm::vec3& startPos, glm::vec3& endPos){
    std::vector<Vertex> vertices = {
        Vertex(startPos), Vertex(endPos)
    };

    return Mesh(vertices.data(), vertices.size(), GL_LINES);
}

Mesh PrimitiveShapes::Sphere(float radius){
    std::vector<Vertex> vertices;

    // TODO: Make a function to make spheres

    return Mesh(vertices.data(), vertices.size(), GL_TRIANGLE_STRIP);
}
