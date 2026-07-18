#include "../../include/shader.h"
#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

static void CheckShaderError(
    GLuint shader,
    GLuint flag,
    bool isProgram,
    const std::string& errorMessage
);
static std::string LoadShader(const std::string& filename);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

/**
 * @brief Construct a new Shader:: Shader object
 *
 * @param filename
 */
Shader::Shader(const std::string& filename){
    // Load shaders
    program = glCreateProgram();
    shaders[0] = CreateShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);
    shaders[1] = CreateShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

    // Attatch shaders
    for (unsigned int i = 0; i < NUM_SHADER; i++){
        glAttachShader(program, shaders[i]);
    }

    glBindAttribLocation(program, 0, "position");

    // Linking
    glLinkProgram(program);
    CheckShaderError(program, GL_LINK_STATUS, true, "Error: Program linking failed");

    // Validation
    glValidateProgram(program);
    CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");

    // Access transform uniform
    uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
    uniforms[COLOR_U] = glGetUniformLocation(program, "objectColor");
}

Shader::~Shader(){
    // Delete shaders
    for (unsigned int i = 0; i < NUM_SHADER; i++){
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }

    glDeleteProgram(program);
}

void Shader::Bind(){
    glUseProgram(program);
}

/**
 * @brief Update the shader
 *
 * @param transform - The transform matrix
 * @param camera - Camera object
 */
void Shader::Update(const Transform& transform, const Camera& camera){
    glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

    glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

/**
 * @brief Compile the shader
 *
 * @param text - Shader in a string format
 * @param shaderType
 * @return GLuint
 */
static GLuint CreateShader(const std::string& text, GLenum shaderType){
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0){
        std::cerr << "Error: Shader creation failed" << std::endl;
    }

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];

    shaderSourceStringLengths[0] = text.length();
    shaderSourceStrings[0] = text.c_str();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

    return shader;
}

/**
 * @brief Open the raw text file of the shader and convert to string
 *
 * @param filename - Filename of the raw text file of the shader
 * @return std::string - The shader in a raw string
 */
static std::string LoadShader(const std::string& filename){
    // Load the file
    std::ifstream file;
    file.open(filename.c_str());

    std::string output;
    std::string line;

    if (!file.is_open()){
        std::cerr << "Unable to load shader: " << filename << std::endl;
        return "";
    }

    while(std::getline(file, line)){
        // If we can open the file, read it and append each line to output
        // We can do this because the shader file is literally just a text
        // file even with a weird extension
        // I could literally write a shader in a string and it'll work the same
        output.append(line + "\n");
    }

    // Check if we actually read anything
    if (output.empty()) {
        std::cerr << "Warning: Shader file is empty: " << filename << std::endl;
        return "";
    }

    return output;
}

// * Checks if the shader loads
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage){
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if (isProgram){
        glGetProgramiv(shader, flag, &success);
    }
    else{
        glGetShaderiv(shader, flag, &success);
    }

    if (success == GL_FALSE){
        if (isProgram){
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        }
        else{
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        }

        std::cerr << errorMessage << ": '" << error << "' " << std::endl;
    }
}

// Change the color of the object to the given value
void Shader::SetColor(const glm::vec3& color){
    glUniform3f(uniforms[COLOR_U], color.x, color.y, color.z);
}
