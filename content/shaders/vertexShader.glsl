#version 330 core

in vec3 coordPositions;

void main()
{
    gl_Position =  vec4(coordPositions ,  1.0f);
}