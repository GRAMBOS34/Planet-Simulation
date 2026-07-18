#include "../../include/telemetry.h"

#include <cstdlib> // #linuxsupremacy

void Logs::ShowPlanetTelemetryInPX(Object& planet){
    // Position, Velocity, Acceleration
    glm::vec3 position = planet.transform.GetPosition();
    glm::vec3 velocity = planet.GetVelocity();
    glm::vec3 acceleraton = planet.GetAcceleration();

    std::cout << "Position: " << position.x << ", " << position.y << "\n";

    std::cout << "Velocity: " << std::hypot(velocity.x, velocity.y) // done like this because its only in 2 axes
        << " px/s pointing at (" << velocity.x << ", " << velocity.y << ")\n";

    std::cout << "Acceleration: " << std::hypot(acceleraton.x, acceleraton.y)
        << " px/s^2 pointing at (" << acceleraton.x << ", " << acceleraton.y << ")\n \n";

    system("clear"); // ! Linux only, will have to figure out some way to clear for other platforms (Mainly windows)

}

void Logs::ShowPlanetTelemetryInMeters(Object &planet, float distanceScalingFactor){
    glm::vec3 position = planet.transform.GetPosition();
    glm::vec3 velocity = planet.GetVelocity() * distanceScalingFactor;
    glm::vec3 acceleration = planet.GetAcceleration() * distanceScalingFactor;

    std::cout << "Position: " << position.x << ", " << position.y << "\n";

    std::cout << "Velocity: " << std::hypot(velocity.x, velocity.y)
        << " m/s pointing at (" << velocity.x << ", " << velocity.y << ")\n";

    std::cout << "Acceleration: " << std::hypot(acceleration.x, acceleration.y)
        << " m/s^2 pointing at (" << acceleration.x << ", " << acceleration.y << ")\n \n";

    system("clear"); // ! Linux only, will have to figure out some way to clear for other platforms (Mainly windows)
}
