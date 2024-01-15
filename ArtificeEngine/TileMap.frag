#version 330 core

uniform sampler2D image;
in vec2 texCoord;
out vec4 FragColor;

void main()
{
    FragColor = texture(image, texCoord);
    //FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); // white color
    //FragColor=vec4(texCoord.x*4,texCoord.y*4,0,1);
}