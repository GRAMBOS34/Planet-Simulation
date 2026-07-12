#include <GL/glew.h>
#include <iostream>

#include "../include/display.h"

/**
 * @brief Construct a new Display:: Display object
 *
 * @param width - Screen/Window width
 * @param height - Screen/Window height
 * @param title - Title of the window
 */
Display::Display(int width, int height, const std::string& title){
    SDL_Init(SDL_INIT_EVERYTHING); // Initialize SDL

    // Set color attributes
    // Basically set how many bits we want to dedicate to each color
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // This would create 2^8 shades of red
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // This would create 2^8 shades of green
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // This would create 2^8 shades of blue
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // This would create 2^8 levels of alpha

    // Set buffer size
    // Data, in bits, that SDL will allocate for every pixel
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

    // Allocates space for two windows
    // So that during runtime, we can just draw to one of the windows and then swap
    // the windows to save some memory or to prevent weird flickering issues
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Create window
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );

    // Create context
    glContext = SDL_GL_CreateContext(window);

    GLenum status = glewInit(); // Finds every openGL command that is supported

    if (status != GLEW_OK) {
        std::cerr << "GLEW failed to initialize";
    }

    isClosed = false;
}

Display::~Display(){
    // Remember that the order here matters
    // So we don't get an error
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Display::IsClosed(){
    return isClosed;
}

void Display::Update(){
    SDL_GL_SwapWindow(window); // Swaps the buffers

    SDL_Event e;

    while (SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            isClosed = true;
        }
    }
}
