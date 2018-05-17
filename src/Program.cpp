#include <iostream>
#include "../header/glad/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

using namespace std;


float vertices[] = 
{
    -0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

string ReadShader(char const *filePath)
{
    string res("");
    ifstream shaderStream(filePath, ios::in);
    if (shaderStream.is_open())
    {
        stringstream sstr;
        sstr << shaderStream.rdbuf();
        res = sstr.str();
        shaderStream.close();
    }
    else
    {
        cout << "Impossible to find your shader : " << filePath << "\n";
        getchar();
    }
    return res;
}




int main()
{
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int vertexShaderID(glCreateShader(GL_VERTEX_SHADER));
    string vertexShader(ReadShader("shaders/vertexShader.glsl"));
    char const *vertexSource = vertexShader.c_str();    
    glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
    glCompileShader(vertexShaderID);

    unsigned int fragmentShaderID(glCreateShader(GL_FRAGMENT_SHADER));
    string fragmentShader(ReadShader("shaders/fragmentShader.glsl"));
    char const *fragmentSource = fragmentShader.c_str();
    
    glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShaderID);



    unsigned int shaderProgramID(glCreateProgram());
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);



    unsigned int VAO(0);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    // ============================================
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //=============================



    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);        

        glUseProgram(shaderProgramID);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}