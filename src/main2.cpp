#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>

#include <iostream>
#include <cmath>


//---EXERCISES----
/* Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data: solution.
Now create the same 2 triangles using two different VAOs and VBOs for their data: solution.
Create two shader programs where the second program uses a different fragment shader that outputs the color yellow;
draw both triangles again where one outputs the color yellow: solution. */

//----WINDOW_SETTINGS----
unsigned int HEIGHT = 600;
unsigned int WIDTH = 800;



//----DECLARATIONS----
void framebuffer_size_callback(GLFWwindow* window, int height, int width);
void processInput(GLFWwindow* window);

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor2;\n"
"void main(){\n"
"gl_Position = vec4(aPos, 1.0);\n"
"ourColor2 = aColor;\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main(){\n"
"FragColor = ourColor;\n"
"}\0";

const char *fragmentShaderSourceYellow = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor2;\n"
"void main(){\n"
"FragColor = vec4(ourColor2, 1.0f);\n"
"}\0";

/* float vertices[] = 
{
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
   -0.5f,  0.5f, 0.0f
};

int indices[] =
{
    0, 1, 3,
    1, 2, 3
}; */

//First Triangle
float vertices[] =
{
    //Positions       
    -0.3f, 0.0f, 0.0f,    
    -0.2f, 0.3f, 0.0f,    
    -0.1f, 0.0f, 0.0f,   
};
//Second Triangle
float vertices2[] =
{
    //Positions         //Colors
    0.3f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
    0.2f, 0.3f, 0.0f,   0.0f, 1.0f, 0.0f,
    0.1f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f
};




int main()
{

    //----GLFW_INITIALIZATION_AND_CONFIGURATION----
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //----GLFW_WINDOW_CREATION----
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL_Triangle", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "GLFW window initialization was not successfull." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //----GLAD_INITIALIZATION----
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD initialization was not successfull." << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    //----VERTEX_SHADERS----
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //----FRAGMENT_SHADERS----
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
    glCompileShader(fragmentShaderYellow);

    //----SHADERS_LINKING----//----SHADERS_PROGRAM_BUILDING_AND_COMPILING----
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShaderYellow);
    glLinkProgram(shaderProgram2);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShaderYellow);

    //----VERTEX_DATA_AND_VERTEX_ATTRIBUTES_CONFIGURATION----
    //FIRST GENERATE AND BIND THE VAO, THEN THE BUFFERS AND THEN CONFIGURE THE VERTEX ATTRIBUTES.
    //ALL THE DATA MUST BE SET BETWEEN THE BIND AND UNBIND.
    
    //A better way to do is, is to create VAOs and VBOs as Arrays instead of doing multiple declarations.

    //unsigned int VAOs[2], VBOs[2];
    //glGenVertexArrays(2, VAOs);
    //glGenBUffers(2, VBOs);
    //glBindVertexArray(VAOs[0]);
    //glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); */

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    unsigned int VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //----RENDER_LOOP----
    while(!glfwWindowShouldClose(window))
    {
        //----INPUT----
        processInput(window);
        //----RENDERING----
        glClearColor(0.5f, 0.2f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(VAO);

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glUseProgram(shaderProgram2);

        glBindVertexArray(VAO2);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        //----GLFW_BUFFERS_SWAP_AND_POLL_I/O_EVENTS----
        glfwSwapBuffers(window);

        glfwPollEvents();

    }
    //DE-ALLOCATE RESOURCES BEFORE THE MAIN FUNCTION ENDS.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

//----FUNCTIONS----
 
void framebuffer_size_callback(GLFWwindow* window, int height, int width)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}