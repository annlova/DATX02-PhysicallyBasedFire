#include <iostream>
#include <fstream>

#include "Shader.h"

std::string Shader::readFile(std::string filePath){
    std::string fileContent;
    std::ifstream fileStream(filePath, std::ios::in);
    
    if(!fileStream.is_open()){
        // TODO: proper error handling
        std::cout << "Failed to read file: " << filePath << ". File not found" << std::endl;
        return "";
    }
    
    std::string line = "";
    while(!fileStream.eof()){
        std::getline(fileStream, line);
        fileContent.append(line + "\n");
    }
    
    fileStream.close();
    return fileContent;
}

Shader::Shader(){
}

void Shader::addShader(std::string filePath, GLenum shaderType){
    GLuint shader = glCreateShader(shaderType);
    
    std::string shaderContent = readFile(filePath);
    
    const GLchar* shaderCode[1];
    shaderCode[0] = shaderContent.c_str();
    
    GLint codeLength[1];
    codeLength[0] = static_cast<GLint>(strlen(shaderCode[0]));
    
    glShaderSource(shader, 1, shaderCode, codeLength);
    glCompileShader(shader);
    
    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog( shader, 512, nullptr, infoLog );
        std::cout << "[Error] Shader failed to compile:\n" << infoLog << "\n";
    }
    
    switch (shaderType) {
        case GL_VERTEX_SHADER:
            m_vertexShader = shader;
            break;
        case GL_GEOMETRY_SHADER:
            m_geometryShader = shader;
            break;
        case GL_FRAGMENT_SHADER:
            m_fragmentShader = shader;
            break;
        default:
            shader = 0;
            break;
    }
}

void Shader::compileShaderProgram(){
    // Link all the shaders
    m_shaderProgramID = glCreateProgram();
    glAttachShader(m_shaderProgramID, m_vertexShader);
    if(m_geometryShader){
        glAttachShader(m_shaderProgramID, m_geometryShader);
    }
    glAttachShader(m_shaderProgramID, m_fragmentShader);
    
    glLinkProgram(m_shaderProgramID);
    
    // Check for linking errors
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(m_shaderProgramID, 512, nullptr, infoLog);
        std::cout << "[Error] Shader failed to link:\n" << infoLog << "\n";
        return;
    }
    
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_geometryShader);
    glDeleteShader(m_fragmentShader);
}

Shader::~Shader(){
}

