# C++ Physics Simulation with OpenGL

This is a gravity simulation using OpenGL.

# Info

This project is mainly for me to learn OpenGL, graphics programming, and physics.

# Project To-do list

- Draw stuff on the screen ✅
- Add camera controls (zoom, pitch, and yaw) ✅
- Show fps count
- Have a way to delete objects outside a certain area during runtime (For collisions, not occlusion culling, that's a different beast)
- Implement quaternions for rotation instead of Euler angles
- Introduce 3D
- Create a debug logger of some sort to track pertinent values of planets ✅

## Gravity To-do list

- Calculate the distance between different objects/planets ✅
- Influence the path of the objects using a force vector ✅
- Influence the path of the objects using gravity ✅
- Use the real values for mass in the simulation (Meaning I have to scale the grid somehow) ✅
- Implement Verlet integration but understand how Euler integration works first
- Add a time scale manipulation thing
- Simulate the orbit of the Moon around the Earth to prove it works (with some leniency, the values just have to be accurate and fit on the screen for the most part)

## Keeping things pretty

- Create a utils directory and put the debug stuff there (?) ✅
- Have that utils directory also show the units in km/s rather than px/s
- Create a function in the telemetery files that lets us pick how to clear the terminal (but really we want to display this stuff to the screen)
- Add better documentation or even make a separate file for documentation

## Time Scale Requirements

- Make stuff move faster
- However, make sure it doesn't affect calculations in weird ways

## Tracking Telemetry Requirements
- Position ✅
- Velocity ✅
- Acceleration ✅
- Distance from the nearest planet
- Vector of gravity force (render an arrow in the scene later)
