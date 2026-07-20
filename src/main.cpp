#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <string>
#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <SDL2/SDL_timer.h>
#include <glm/common.hpp>
#include <glm/trigonometric.hpp>

#include "../include/display.hpp"
#include "../include/shader.hpp"
#include "../include/mesh.hpp"
#include "../include/camera.hpp"
#include "../include/object.hpp"
#include "../include/renderer.hpp"
#include "../include/telemetry.hpp"

const float DISPLAY_WIDTH = 1600.0f;
const float DISPLAY_HEIGHT = 900.0f;
const float LINE_WIDTH_PIXELS = 2.5f;
const float TIME_SCALE_MULTIPLIER = 1.0e7f;

// Physics constants
const float GRAVITATIONAL_CONSTANT = 6.674e-11;
const float METERS_PER_PIXEL = 1.0e6f;

void UpdateLineMesh(glm::vec3& startPos, glm::vec3& endPos, Mesh& line);

int main() {
    Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Physics Sim"); // Initialize the display window

    glEnable(GL_DEPTH_TEST); // Ensure we enable the depth thing so that we dont draw primitives over each other

    // Initialize the vertex and fragment shaders
    // ! Make sure that the shaders have the same name
    Shader shader("res/basicShader");

    float aspectRatio = DISPLAY_WIDTH/DISPLAY_HEIGHT;
    Camera camera(glm::vec3(0.5f, 0, 300.0f), glm::radians(90.0f), aspectRatio, 0.01f, 500.0f); // initialize the camera

    Renderer renderer(&camera, &shader); // initialize the renderer

    float lastFrame = 0.0f; // used to calculate deltaTime

    // * Create the objects in the scene
    Mesh circle = PrimitiveShapes::Circle(20.0f);
    float moonDistMeters = 384.4e6f;
    Object Moon(&circle, glm::vec3(moonDistMeters/METERS_PER_PIXEL, 0, 0));
    Moon.SetColor(glm::vec3(0, 1.0f, 1.0f));
    Moon.SetMass(7.348e22); // in kg
    Moon.SetVelocity(glm::vec3(0, 1.0f, 0)); // Initial push velocity

    Object Earth(&circle, glm::vec3(0, 0, 0));
    Earth.SetColor(glm::vec3(1.0f, 1.0f, 0));

    Mesh square = PrimitiveShapes::Quad(40.0f, 20.0f);
    Object Cube(&square, glm::vec3(0, 0, 20.0f));
    Cube.SetColor(glm::vec3(0, 0, 0));

    Earth.SetMass(5.972e24); // in kg

    Mesh line = PrimitiveShapes::Line(Moon.transform.GetPosition(), Earth.transform.GetPosition());
    Object distLine(&line, glm::vec3(0, 0, 0));
    distLine.SetColor(glm::vec3(0, 0, 0));

    // * Scene object vector
    /*
     * A vector of pointers that show point to the object's address
     * This is done so that we can read the values even after they're updated.
     * I don't think smart pointers would be good here since this vector
     * is only needed to read data. so if I had to delete smth during runtime, I'd just
     * create a delete function which also manages this
     */
    std::vector<Object*> SceneObjects = {
        &Moon,
        &Earth,
        &Cube,
        &distLine
    };

    while (!display.IsClosed()){
        glClearColor(0.0f, 0.15f, 0.3f, 1.0f); // Sets the background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the buffer every frame

        // Bind the shader
        shader.Bind();

        // * Calculate deltaTime
        float currentFrame = SDL_GetTicks() / 1000.0f;
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        float simDeltaTime = TIME_SCALE_MULTIPLIER * deltaTime;

        // * Camera Input
        camera.UpdateCameraPosition();

        // * Move the line's endpoints
        glm::vec3 EarthPos = Earth.transform.GetPosition();
        glm::vec3 MoonPos = Moon.transform.GetPosition();

        UpdateLineMesh(EarthPos, MoonPos, line);
        glLineWidth(LINE_WIDTH_PIXELS); // Set line width

        // * Physics stuff
        float dx_meters = (EarthPos.x - MoonPos.x) * METERS_PER_PIXEL;
        float dy_meters = (EarthPos.y - MoonPos.y) * METERS_PER_PIXEL;

        float distance = std::hypot(dx_meters, dy_meters);
        if (distance < 0.05f) distance = 0.05f;

        float accelerationScalar = (GRAVITATIONAL_CONSTANT * Earth.GetMass()) / pow(distance, 2);

        glm::vec3 acc_meters = accelerationScalar * glm::vec3(dx_meters / distance, dy_meters / distance, 0);

        glm::vec3 acc_pixels = acc_meters / METERS_PER_PIXEL;

        Moon.Accelerate(acc_pixels, simDeltaTime);

        // * Draw stuff
        Moon.UpdatePosition(deltaTime); // Update positions
        // Logs::ShowPlanetTelemetryInMeters(Moon, METERS_PER_PIXEL);

        for (const auto& obj : SceneObjects){
            renderer.Draw(*obj);
        }

        display.Update();
    }
   return 0;
}

// * Updates the line mesh by changing the vertices stored in the buffer
// * This allows us to get around having to make a new line mesh every frame
void UpdateLineMesh(glm::vec3& startPos, glm::vec3& endPos, Mesh& line){
    std::vector<Vertex> lineVertices = {Vertex(startPos), Vertex(endPos)};

    glBindBuffer(GL_ARRAY_BUFFER, line.GetVBO());
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(lineVertices), lineVertices.data());
}
