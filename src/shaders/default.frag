#version 330 core

out vec4 FragColor; // the output variable that goes to the next stage
  
in vec2 texPos; // the input variable from the vertex shader (same name and same type)  

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, texPos);
}