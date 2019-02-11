#include <iostream>
#include <glad/glad.h> // for openGL functions
#include <GLFW/glfw3.h> // for window creation, input handling and openGL context
#include <glm/glm.hpp> // math for openGL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../src/OpenGL/Shader.h"
#include "../src/OpenGL/QuadRenderer.h"
#include "../src/FluidSolver.h"

int width = 512;
int height = 512;
int gridSize = 64;
int cellSize = 8;
double mouse_xpos, mouse_ypos;
int omx = 0;
int omy = 0;

double mass = 0.0;
double massPrev = 0.0;

Shader shader;
GLFWwindow* mainWindow;
FluidSolver fluidSolver;

// GLFW3 callbacks
static void glfw3ErrorCallback(int error, const char* description){
    std::cout << "Error:" << error << " " << description << std::endl;
}
static void glfw3KeyCallback(GLFWwindow* window, int key, int scancode,
                             int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// Forward declaration
void initOpenGL();
void getInput();
bool outsideGrid();

int main(int argc, char* argv[]){
    initOpenGL();
    QuadRenderer quadRenderer(shader.getShaderProgramID());
    
    while (!glfwWindowShouldClose(mainWindow)){
        glfwGetFramebufferSize(mainWindow, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
        getInput();

        fluidSolver.timeStep();
        
        // for each grid cell, draw density as quad
        for(int x(0); x < width; x+=cellSize){
            for(int y(0); y < height; y+=cellSize){
                double colorDensity = fluidSolver.getDensityAt(x/cellSize, y/cellSize);
                quadRenderer.DrawQuad(glm::vec2(x,y), glm::vec2(cellSize), glm::vec3(colorDensity));
            }
        }
        
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
        mass = fluidSolver.totalMass();
        std::cout << "Mass difference from prev step: " << mass - massPrev << std::endl;
        massPrev = mass;
    }
    // Terminate GLFW3
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
	return 0;
}



void getInput(){
    glfwGetCursorPos(mainWindow, &mouse_xpos, &mouse_ypos);
    int stateL = glfwGetMouseButton(mainWindow, GLFW_MOUSE_BUTTON_LEFT);
    int stateR = glfwGetMouseButton(mainWindow, GLFW_MOUSE_BUTTON_RIGHT);
    if (stateL == GLFW_PRESS || stateR == GLFW_PRESS){
        
        int i = (int)((mouse_xpos / 512)*gridSize);
        int j = (int)((mouse_ypos / 512)*gridSize);
        
        if (!( i<1 || i>gridSize || j<1 || j>gridSize )){
            
            if (stateL == GLFW_PRESS) {
                fluidSolver.addVelocity(i, j, mouse_xpos-omx, mouse_ypos-omy);
            }
            
            if (stateR == GLFW_PRESS) {
                fluidSolver.addDensity(i, j);
            }
            omx = mouse_xpos;
            omy = mouse_ypos;
        }
    }
}

void initOpenGL(){
    if(!glfwInit()){
        // Initialization failed
        // TODO: add proper error messaging code here...
        std::cout << "GLFW3 failed to initialize" << std::endl;
        }
        glfwSetErrorCallback(glfw3ErrorCallback);
        
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // Mac essential
        glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
        
        mainWindow = glfwCreateWindow(width, height, "FireSim", NULL, NULL);
        if(!mainWindow){
            std::cout << "GLFW3 failed to create the main window" << std::endl;
        }
    glfwSetKeyCallback(mainWindow, glfw3KeyCallback);
    glfwMakeContextCurrent(mainWindow);
    glfwSwapInterval(1); // v-sync, 0 is without
        
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        
    shader.addShader("src/OpenGL/basic.vert", GL_VERTEX_SHADER);
    shader.addShader("src/OpenGL/basic.frag", GL_FRAGMENT_SHADER);
    shader.compileShaderProgram();
        
    glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
    glUseProgram(shader.getShaderProgramID());
    glUniformMatrix4fv(glGetUniformLocation(shader.getShaderProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

