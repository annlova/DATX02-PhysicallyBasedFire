#include "QuadRenderer.h"

QuadRenderer::QuadRenderer(GLuint s){
    shader = s;
    initRenderData();
}

QuadRenderer::~QuadRenderer(){}

void QuadRenderer::initRenderData(){
    GLuint VBO;
    
    GLfloat vertices[] = {
        //X   Y     Z
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };
    
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(this->quadVAO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void QuadRenderer::DrawQuad(glm::vec2 position,
                            glm::vec2 size,
                            glm::vec3 color){
    glUseProgram(shader);
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    // rotate
    model = glm::scale(model, glm::vec3(size, 1.0f));
    
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform3f(glGetUniformLocation(shader, "colorIn"), color.x, color.y, color.z);
    
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
