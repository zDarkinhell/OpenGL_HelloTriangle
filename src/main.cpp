#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//In the process of learning OpenGL, expect comments like "i dont know what that is".
int main()
{
    //GLFW initialization
    glfwInit(); //This function initializes the GLFW library, we need to in order to do anything related to GLFW.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //This function is used to set values to different ENUMS
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //In this case we're telling GLFW what version of OpenGL we're using
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Here we're telling GLFW what profile we want to use.

    //GLFW window creation, the first two arguments are width and height
    //The third argument is the window title, the rest i still dont know, leave it NULL.
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to initialize GLFW window!" << std::endl;
        glfwTerminate();//This function destroys any GLFW window, frees the memory allocated and then we're
                    //required to call glfwInit() again in order to continue doing anything with GLFW.
        return -1;

    }
    //We tell GLFW to make the context of our window the main context on the current thread.
    glfwMakeContextCurrent(window);

    //GLAD initialization, im still trying to understand how it works.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        //We pass GLAD the function to load the address of the OpenGL function pointers which is OS-specific.
        //GLFW gives us glfwGetProcAddress that defines the correct function based on which OS we're compiling for.
        std::cout << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }

    //Before we start rendering, we have to tell OpenGL the size of the rendering window.
    //The first two parameters will set the location of the bottom left corner of the window
    //The last two parameters are the width and heigth of the rendering window
    //We can set the rendering window to be smaller than the GLFW window if we want
    glViewport(0, 0, 800, 600);

    //Then we should also handle the case where the user resizes the window, so we resize the viewport accordingly
    //We're creating a callback function, the values will be filled automatically by GLFW everytime the function
    //gets called, this happens everytime the user resizes the window.

    //We're telling GLFW what function to call on every window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //The function checks at each iteration if GLFW has been instructed to close.
    //If this is the case, the function returns true and the render loop stops working.

    //Now we want to create the render loop since we dont want to just create a window, render something and
    //close it as soon as it finishes rendering.

    //----RENDER LOOP----
    while (!glfwWindowShouldClose(window))
    {
        //----INPUT----
        processInput(window);

        //----RENDERING COMMANDS----

        //Here we're clearing the screen with a color.
        //glClearColor is to set what color we want to clear the screen with.
        glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        //glClear is used to clear the screen and specify what buffer we want to clear, in this case the color buffer.
        glClear(GL_COLOR_BUFFER_BIT);

        

        //----CHECK AND CALL EVENTS---BUFFER SWAP----

        //This function swaps the color buffer that is used to render during this iteration and shows it as output to the screen.
        //This is a Double buffer, it is used to prevent artifacts to show on the screen during the rendering.
        //Artifacts may happen when rendering on a single buffer.
        glfwSwapBuffers(window);
        //This function checks if any events are triggered (keyboard input, mouse movement, ect..)
        glfwPollEvents();
    }

    //Now, as soon as we exit the render loop, we want to properly clean all the resources that were allocated.
    glfwTerminate();
    return 0;
}

//The callback function.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

//Input control on the GLFW window
void processInput(GLFWwindow* window)
{
    //The glfwGetKey function takes the window and the button as input, this will be checked in the render loop every frame.
    //When the key is pressed, the function glfwSetWindowShouldClose will set the option TRUE on the window and
    //it will close.
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

