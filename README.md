# C++ Physics Simulation with OpenGL

This is a gravity simulation using OpenGL.

# Info

This project is mainly for me to learn OpenGL, graphics programming, and physics.

# Project To-do list

- Draw stuff on the screen ✅
- Add camera controls (zoom, pan, rotate)
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
- Add a time scale manipulation thing
- Simulate the orbit of the Moon around the Earth to prove it works (with some leniency, the values just have to be accurate and fit on the screen for the most part)

## Keeping things pretty
- Create a utils directory and put the debug stuff there (?) ✅
- Have that utils directory also show the units in km/s rather than px/s 
- Add better documentation or even make a separate file for documentation

## Time Scale Requirements
- Make stuff move faster
- However, make sure it doesn't affect calculations in weird ways
