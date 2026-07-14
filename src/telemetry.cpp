#include "../include/telemetry.h"

void Logs::ShowPlanetTelemetry(Object& planet){
    // Position, Velocity, Acceleration
    glm::vec3 position = planet.transform.GetPosition();
    glm::vec3 velocity = planet.GetVelocity();
    glm::vec3 acceleraton = planet.GetAcceleration();

    std::cout << "Position: " << position.x << ", " << position.y << "\n";

    std::cout << "Velocity: " << std::hypot(velocity.x, velocity.y)
        << "px/s pointing at (" << velocity.x << ", " << velocity.y << ")\n";

    std::cout << "Acceleration: " << std::hypot(acceleraton.x, acceleraton.y)
        << "px/s pointing at (" << acceleraton.x << ", " << acceleraton.y << ")\n \n";
}
