#version 330 core

out vec4 FragColor;

in vec3 ourColor2;
//in vec3 aPos2;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    //FragColor = vec4(ourColor2, 1.0f);
    //FragColor = vec4(aPos2, 1.0f);
    FragColor = texture(ourTexture, TexCoord);
}