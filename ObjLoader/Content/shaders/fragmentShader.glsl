
#version 330 core

in vec3 outColor;
in vec2 texCoords;

out vec4 finalColor;

uniform sampler2D ourTexture;



void main()
{
    
    finalColor =  texture(ourTexture, texCoords) *  vec4( outColor ,1.0);

}

