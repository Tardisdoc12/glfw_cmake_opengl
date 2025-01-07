#version 330 core

layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec2 aTex; // the color variable has attribute position 1

out vec2 texPos; // specify a color output to the fragment shader

uniform mat4 ModelMatrix;

void main()
{
    gl_Position = vec4(ModelMatrix * vec4(aPos, 1.0)); // see how we directly give a vec3 to vec4's constructor
    texPos = aTex;
}