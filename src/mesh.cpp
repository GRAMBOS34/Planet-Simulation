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

// ? ---------------- PRIMITIVE SHAPES -------------------------

const int SECTOR_COUNT = 20; // Determines how "sharp" curves look
const float PI = 3.14159f;

// * This function only creates a 2D circle
Mesh PrimitiveShapes::Circle(float radius, int edges){
    std::vector<Vertex> verticies;
    verticies.reserve(edges + 2);

    verticies.emplace_back(glm::vec3(0,0,0)); // Add the centre point

    for (int i = 0; i <= edges; i++){
        float angle = 2.0f * PI * i / edges; // Calculate angle in radians
        float x_point = (radius * cos(angle));
        float y_point = (radius * sin(angle));

        verticies.emplace_back(glm::vec3(x_point, y_point, 0)); // (x,y,z)
    }

    return Mesh(verticies.data(), verticies.size(), GL_TRIANGLE_FAN);
}

Mesh PrimitiveShapes::Quad(Vertex v0, Vertex v1, Vertex v2, Vertex v3){
    std::vector<Vertex> vertices = {v0, v1, v2, v1, v2, v3};

    return Mesh(vertices.data(), vertices.size(), GL_TRIANGLES);
}

void GenerateQuad(std::vector<Vertex>& vertices, Vertex v0, Vertex v1, Vertex v2, Vertex v3){
    // Bottom left triangle
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);

    // Top right triangle
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
}

Mesh PrimitiveShapes::Line(glm::vec3& startPos, glm::vec3& endPos){
    std::vector<Vertex> vertices = {
        Vertex(startPos), Vertex(endPos)
    };

    return Mesh(vertices.data(), vertices.size(), GL_LINES);
}

const int STACK_COUNT = 10;

Mesh PrimitiveShapes::Sphere(float radius){
    std::vector<Vertex> vertices;

    // TODO: Make a function to make spheres

    for (int i = 0; i <= STACK_COUNT; i++){
        float stackAngle = PI / 2.0f - i * (PI / STACK_COUNT); // From PI/2 to -PI/2

        for (int j = 0; j <= SECTOR_COUNT; j++){
            float angle = 2.0f * PI * j / SECTOR_COUNT; // Calculate angle in radians
            float x_point = (radius * cos(angle));
            float z_point = (radius * sin(angle));

            vertices.emplace_back(glm::vec3(x_point, 0, z_point)); // (x,y,z)
        }
    }

    return Mesh(vertices.data(), vertices.size(), GL_TRIANGLES);
}

/**
 * gridSegNumPerAxis is in number of segments rather than pixels
 * segmentSideLengthPX is in pixels
 */
Mesh PrimitiveShapes::SquareGrid(float segmentSideLengthPX, glm::vec2 gridSegNumPerAxis){
    std::vector<Vertex> vertices;

    float lineLengthHorizontal = segmentSideLengthPX * gridSegNumPerAxis.x;
    float lineLengthVertical = segmentSideLengthPX * gridSegNumPerAxis.y;

    // Loop for the horizontal axis/vertical lines
    // Starts at index 1 to avoid creating two borders
    for (int i = 1; i < gridSegNumPerAxis.x; i++){
        float segmentDistFromFirstLine = segmentSideLengthPX * i;

        vertices.emplace_back(glm::vec3(segmentDistFromFirstLine, 0, 0)); // Start point

        vertices.emplace_back(glm::vec3(segmentDistFromFirstLine, 0, lineLengthHorizontal)); // End Point
    }

    // Loop for vertical axis/horizontal lines
    // Starts at index 1 to avoid creating two borders
    for (int j = 1; j < gridSegNumPerAxis.y; j++){
        float segmentDistFromFirstLine = segmentSideLengthPX * j;

        vertices.emplace_back(glm::vec3(0, 0, segmentDistFromFirstLine)); // Start point

        vertices.emplace_back(glm::vec3(lineLengthHorizontal, 0, segmentDistFromFirstLine)); // End Point
    }

    return Mesh(vertices.data(), vertices.size(), GL_LINES);
}
