#include "../include/telemetry.hpp"

#include <iostream>

// ! The ANSI clear is only good for UNIX-like systems
// so basically this won't work for anything before Windows 11

void Logs::ShowPlanetTelemetryInPX(Object& planet){
    // Clear entire screen and move cursor home
    // Full ANSI clear (using ANSI escape code)
    std::cout << "\033[2J\033[H";

    // Position, Velocity, Acceleration
    glm::vec3 position = planet.transform.GetPosition();
    glm::vec3 velocity = planet.GetVelocity();
    glm::vec3 acceleraton = planet.GetAcceleration();

    std::cout << "Position: " << position.x << ", " << position.y << "\n";

    std::cout << "Velocity: " << std::hypot(velocity.x, velocity.y) // done like this because its only in 2 axes
        << " px/s pointing at (" << velocity.x << ", " << velocity.y << ")\n";

    std::cout << "Acceleration: " << std::hypot(acceleraton.x, acceleraton.y)
        << " px/s^2 pointing at (" << acceleraton.x << ", " << acceleraton.y << ")\n \n";

    // There's probably a better way to do this fr
    std::cout << std::flush; // Flush the output sequence
}

void Logs::ShowPlanetTelemetryInMeters(Object &planet, float distanceScalingFactor){
    // Clear entire screen and move cursor home
    // Full ANSI clear (using ANSI escape code)
    std::cout << "\033[2J\033[H";

    glm::vec3 position = planet.transform.GetPosition();
    glm::vec3 velocity = planet.GetVelocity() * distanceScalingFactor;
    glm::vec3 acceleration = planet.GetAcceleration() * distanceScalingFactor;

    std::cout << "Position: " << position.x << ", " << position.y << "\n";

    std::cout << "Velocity: " << std::hypot(velocity.x, velocity.y)
        << " m/s pointing at (" << velocity.x << ", " << velocity.y << ")\n";

    std::cout << "Acceleration: " << std::hypot(acceleration.x, acceleration.y)
        << " m/s^2 pointing at (" << acceleration.x << ", " << acceleration.y << ")\n \n";

    std::cout << std::flush; // Flush the output sequence
}
