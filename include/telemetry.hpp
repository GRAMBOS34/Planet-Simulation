#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "object.hpp"

namespace Logs{
    void ShowPlanetTelemetryInPX(Object& planet);
    void ShowPlanetTelemetryInMeters(Object& planet, float distanceScalingFactor);
}

#endif
