#include <cmath>
#include <string>
#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <SDL2/SDL_timer.h>
#include <glm/common.hpp>
#include <glm/trigonometric.hpp>

#include "../include/display.h"
#include "../include/shader.h"
#include "../include/mesh.h"
#include "../include/camera.h"
#include "../include/object.h"
#include "../include/renderer.h"
#include "../include/telemetry.h"

// * This function only creates a 2D circle
// The sphere will be a bit more complicated although somewhat the same
Mesh Circle(float radius, int edges){
    std::vector<Vertex> verticies;
    verticies.reserve(edges + 2);

    verticies.emplace_back(glm::vec3(0,0,0)); // Add the centre point

    for (int i = 0; i <= edges; i++){
        float angle = 2.0f * 3.14159f * i / edges; // Calculate angle in radians
        float x_point = (radius * cos(angle));
        float y_point = (radius * sin(angle));

        verticies.emplace_back(glm::vec3(x_point, y_point, 0)); // (x,y,z)
    }

    return Mesh(verticies.data(), verticies.size());
}

Mesh Line(glm::vec3& startPos, glm::vec3& endPos){
    std::vector<Vertex> vertices = {
        Vertex(startPos), Vertex(endPos)
    };

    return Mesh(vertices.data(), vertices.size());
}

const float DISPLAY_WIDTH = 1600.0f;
const float DISPLAY_HEIGHT = 900.0f;
const float LINE_WIDTH_PIXELS = 2.5f;
const float TIME_SCALE_MULTIPLIER = 1.0e7f;

// Physics constants
const float GRAVITATIONAL_CONSTANT = 6.674e-11;
const float METERS_PER_PIXEL = 1.0e6f;

int main() {
   Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Physics Sim"); // Initialize the display window

   // Initialize the vertex and fragment shaders
   // ! Make sure that the shaders have the same name
   // Also idk what it'd do if there's multiple shaders but you'd probably never do that right?
   Shader shader("res/basicShader");

   float aspectRatio = DISPLAY_WIDTH/DISPLAY_HEIGHT;
   Camera camera(glm::vec3(0.5f, 0, 300.0f), glm::radians(90.0f), aspectRatio, 0.01f, 500.0f); // initialize the camera

   Renderer renderer(&camera, &shader); // initialize the renderer

   float lastFrame = 0.0f; // used to calculate deltaTime

   // Create the objects in the scene
   Mesh circle = Circle(10.0f, 18);
   float moonDistMeters = 384.4e6f;
   Object Moon(&circle, GL_TRIANGLE_FAN, glm::vec3(moonDistMeters/METERS_PER_PIXEL, 0, 0));

   Object Earth(&circle, GL_TRIANGLE_FAN, glm::vec3(0, 0, 0));

   Moon.SetMass(7.348e22); // in kg
   Moon.SetVelocity(glm::vec3(0, 1.0f, 0)); // Initial push velocity

   Earth.SetMass(5.972e24); // in kg

   // TODO: Array of objects in the scene
   // This is both to manage it all and to release the memory before ending the process
   // idk if doing this would be redundant since from what i've seen, the destructor
   // is already called when the program is killed but idk, just to be safe ig
   std::vector<Object> SceneObjects;

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

        // * Create a line
        glLineWidth(LINE_WIDTH_PIXELS); // Set line width
        Mesh line = Line(Moon.transform.GetPosition(), Earth.transform.GetPosition());
        Object distLine(&line, GL_LINES);

        // * Physics stuff
        float dx_meters = (Earth.transform.GetPosition().x - Moon.transform.GetPosition().x) * METERS_PER_PIXEL;
        float dy_meters = (Earth.transform.GetPosition().y - Moon.transform.GetPosition().y) * METERS_PER_PIXEL;

        float distance = std::hypot(dx_meters, dy_meters);
        if (distance < 0.05f) distance = 0.05f;

        // Squaring the distance makes the acceleration pretty much zero for some reason
        // This is wrong so somewhere along the calculation is wrong
        float accelerationScalar = (GRAVITATIONAL_CONSTANT * Earth.GetMass()) / pow(distance, 2);
        std::cout << "Distance: " << distance << "\n";

        glm::vec3 acc_meters = accelerationScalar * glm::vec3(dx_meters / distance, dy_meters / distance, 0);
        std::cout << "Normal Vector: " << dx_meters / distance << ", " << dy_meters / distance << "\n";

        glm::vec3 acc_pixels = acc_meters / METERS_PER_PIXEL;

        Moon.Accelerate(acc_pixels, simDeltaTime);

        // * Draw stuff
        // Set colors
        Earth.SetColor(glm::vec3(1.0f, 1.0f, 0));
        Moon.SetColor(glm::vec3(0, 1.0f, 1.0f));
        distLine.SetColor(glm::vec3(0,0,0));

        Moon.UpdatePosition(deltaTime); // Update positions
        Logs::ShowPlanetTelemetryInMeters(Moon, METERS_PER_PIXEL);

        // TODO: Change this draw call thing into a loop where each object is in an array
        renderer.Draw(Moon);
        renderer.Draw(Earth);
        renderer.Draw(distLine);

        display.Update();
}

   return 0;
}
