#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

#include <iostream>
#include <cmath>
#include "stb_image.h"


//---EXERCISES----
/* Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data: solution.
Now create the same 2 triangles using two different VAOs and VBOs for their data: solution.
Create two shader programs where the second program uses a different fragment shader that outputs the color yellow;
draw both triangles again where one outputs the color yellow: solution. */

//----WINDOW_SETTINGS----
unsigned int HEIGHT = 600;
unsigned int WIDTH = 800;



//----FUNCTIONS----
void framebuffer_size_callback(GLFWwindow* window, int height, int width);

void processInput(GLFWwindow* window);

//----DECLARATIONS----
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
    //Positions         //Colors           //Texture
    0.8f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    0.8f, 0.8f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    0.0f, 0.8f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
};
//Texture cordinates
/* float texCoords[] =
{
    0.0f, 0.0f,  
    1.0f, 0.0f,  
    0.5f, 1.0f   
}; */

float value = 0.0f;


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

    //----CREATING_AND_LOADING_TEXTURES----

    //We're generating the texture and binding it
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //Setting up the texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Setting up the texture filtering and mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //Using the stb_image library to load and read texture's data
    int tWidth, tHeigth, nrChannels;
    unsigned char *data = stbi_load("C:/Users/ricky/Desktop/Projects/OpenGL_HelloTriangle/src/textures/container.jpg", &tWidth, &tHeigth, &nrChannels, 0);
    
    if (data)
    {
        //Using the data we got earlier to generate the texture image and binding it to the object
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeigth, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    
    //Its good use to free the data
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    data = stbi_load("C:/Users/ricky/Desktop/Projects/OpenGL_HelloTriangle/src/textures/awesomeface.png", &tWidth, &tHeigth, &nrChannels, 0);
    
    if (data)
    {
        //Using the data we got earlier to generate the texture image and binding it to the object
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }



    //Declaring our Shader variable with the files paths AFTER OPENGL INITIALIZATION, otherwise it wont work!
    Shader ourShader("shader.vs", "shader.fs");
    
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Telling OpenGL which texture unit each shader sampler belongs to
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
 
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
        glUniform4f(vertexColorLocation, 1.0f, greenValue, 0.3f, 1.0f);

        //std::cout << timeValue << "\n";

        glBindVertexArray(VAO);

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        //Using our Shader Class shader
        ourShader.use();
        //glUseProgram(shaderProgram2);

        float xValue = sin(timeValue) / 2.0f;
        float yValue = sin(timeValue) / 2.5f;
        ourShader.setFloat("xPosition", xValue);
        ourShader.setFloat("yPosition", yValue);

        float angle = 0.45f;
        float sinAngleValue = sin(angle * timeValue);
        float cosAngleValue = cos(angle * timeValue);
        ourShader.setFloat("sinAngle", sinAngleValue);
        ourShader.setFloat("cosAngle", cosAngleValue);

        //Using our texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //ourShader.setFloat("HorizontalOffset", 0.3f);

        glBindVertexArray(VAO2);
        

        glDrawArrays(GL_TRIANGLES, 0, 3);

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {   
            value = value + 0.01f;
            ourShader.setFloat("vAmount", value);
            std::cout << value << "\n";
        }
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            value = value - 0.01f;
            ourShader.setFloat("vAmount", value);
            std::cout << value << "\n";
        }

        value = sin(timeValue);
        ourShader.setFloat("vAmount", value);
        std::cout << value << "\n";

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