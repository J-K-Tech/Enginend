#version 460 core

layout (location = 0) in vec2 inPos;
uniform vec3 light;
uniform vec3 lightpos;
uniform mat4 model;
out vec2 UV;
void main()
{
    gl_Position = vec4(inPos.x/2, inPos.y/2, 0.0, 1.0);
    UV=vec2(inPos.x-2,inPos.y+2);
    UV/=4;
}  


