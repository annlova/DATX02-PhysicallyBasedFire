#ifndef Shader_h
#define Shader_h

#include <string>
#include <glad/glad.h>

class Shader{
public:
    static std::string readFile(std::string filePath);
    
    Shader();
    ~Shader();
    
    void addShader(std::string filePath, GLenum shaderType);
    void compileShaderProgram();
    
    GLuint getShaderProgramID() const { return m_shaderProgramID; }
    
private:
    GLuint m_shaderProgramID;
    GLuint m_vertexShader, m_fragmentShader;
    GLuint m_geometryShader;
};

#endif
