#include <cmath>
#include <string>
#include <vector>
#include <iostream>

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


// Physics constants
const double GRAVITATIONAL_CONSTANT = 2;

int main() {
   Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Physics Sim"); // Initialize the display window

   Shader shader("res/basicShader"); // Initialize the vertex and fragment shaders

   float aspectRatio = DISPLAY_WIDTH/DISPLAY_HEIGHT;
   Camera camera(glm::vec3(0.5f, 0, 10.0f), glm::radians(70.0f), aspectRatio, 0.01f, 100.0f); // initialize the camera

   Renderer renderer(&camera, &shader); // initialize the renderer

   float lastFrame = 0.0f; // used to calculate deltaTime

   // Array of objects in the scene
   // This is both to manage it all and to release the memory before ending the process
   // idk if doing this would be redundant since from what i've seen, the destructor
   // is already called when the program is killed but idk, just to be safe ig
   std::vector<Object> SceneObjects;

   // Create the objects in the scene
   Mesh circle = Circle(0.2f, 18);
   Object planet(&circle, GL_TRIANGLE_FAN, glm::vec3(0.5f, 0.5f, 0));

   Object otherPlanet(&circle, GL_TRIANGLE_FAN, glm::vec3(0, 0, 0));

   planet.SetMass(10);
   otherPlanet.SetMass(10);

   while (!display.IsClosed()){
        glClearColor(0.0f, 0.15f, 0.3f, 1.0f); // Sets the background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the buffer every frame

        // Bind the shader
        shader.Bind();

        // * Calculate deltaTime
        float currentFrame = SDL_GetTicks() / 1000.0f;
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // * Initialize a line
        glLineWidth(LINE_WIDTH_PIXELS); // Set line width
        Mesh line = Line(planet.transform.GetPosition(), otherPlanet.transform.GetPosition());
        Object distLine(&line, GL_LINES);

        // * Physics stuff
        // Let's start with something simple:
        // Given a force vector F, calculate the velocity vector of the object and apply it to the object
        // a = F * m

        glm::vec3 force(0.2f, 0, 0);

        glm::vec3 acceleration = force * planet.GetMass();

        planet.Move(acceleration, deltaTime);

        // ! std::cout << "Planet at: (" << planet.transform.GetPosition().x << ", " << planet.transform.GetPosition().y << ")\n";

        // * Draw the planet
        otherPlanet.SetColor(glm::vec3(1.0f, 0, 0));
        distLine.SetColor(glm::vec3(0,0,0));

        renderer.Draw(planet);
        renderer.Draw(otherPlanet);
        renderer.Draw(distLine);

        display.Update();
    }

   return 0;
}
