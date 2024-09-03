#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

class Shader
{
public:
    //program ID
    unsigned int ID;
    //class constructor, takes in the shaders paths
    Shader(const char* vertexPath, const char* fragmentPath)
    {   
        //declaration of variables to contain the vertex/fragment shader code.
        std::string vertexCode;
        std::string fragmentCode;
        //declaration of input file stream variables to work on the shaders files.
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        //ensure ifstream objects can throw expections.
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            //opening the files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream;
            std::stringstream fShaderStream;
            //read file's buffer content into streams.
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            //close the file handlers.
            vShaderFile.close();
            fShaderFile.close();
            //convert the streams into strings.
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } 
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        //i need to research this.
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        //compiling the shaders
        int success;
        char infoLog[512];

        unsigned int vertex;
        unsigned int fragment;
        //creating the vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        //assigning the source code to the vertex variable
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        //compiling the shader
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        //creating the fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        //assigning the source code to the fragment variable
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        //compiling the shader
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        //creating the shader program
        ID = glCreateProgram();
        //attaching the shaders to the program
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        //linking the program
        glLinkProgram(ID);
        //printing if theres any linking errors.
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        //deleting the shaders once they're linked with the program.
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    };
    //function to use the shader program
    void use()
    {
        glUseProgram(ID);
    };
    // utility uniform functions, gotta research them.
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    } 
    
};
#endif