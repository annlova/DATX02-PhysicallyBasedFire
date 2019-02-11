#ifndef QuadRenderer_h
#define QuadRenderer_h

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../src/OpenGL/Shader.h"

class QuadRenderer{
public:
    QuadRenderer(GLuint shader);
    QuadRenderer();
    ~QuadRenderer();
    
    void DrawQuad(glm::vec2 position,
                    glm::vec2 size = glm::vec2(8, 8),
                    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
private:
    GLuint shader;
    GLuint quadVAO;
    void initRenderData();
};

#endif
