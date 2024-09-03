#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor2;
//out vec3 aPos2;

uniform float HorizontalOffset;

uniform float xPosition;
uniform float yPosition;

uniform float sinAngle;
uniform float cosAngle;


void main()
{

    //gl_Position = vec4(aPos.x + xPosition, aPos.y + yPosition, aPos.z, 1.0);

    //Rotation around the Y axis
    //gl_Position = vec4((cosAngle * aPos.x) + (sinAngle * aPos.z), aPos.y,(-sinAngle * aPos.x) + (cosAngle * aPos.z), 1.0f);
    //Rotation around the X axis
    gl_Position = vec4(aPos.x, (cosAngle * aPos.y) - (sinAngle * aPos.s), (sinAngle * aPos.y) + (cosAngle * aPos.z), 1.0f);
    //Rotation around the Z axis
    //gl_Position = vec4((cosAngle * aPos.x) - (sinAngle * aPos.y), (sinAngle * aPos.x) + (cosAngle * aPos.y), aPos.z, 1.0f);
    ourColor2 = aColor;
    //aPos2 = aPos;

}