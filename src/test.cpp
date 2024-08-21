#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main ()
{

    std::cout << "Hello Test!";
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    
    return 0;
}