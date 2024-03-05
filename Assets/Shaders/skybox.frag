#version 450

layout(location = 0) out vec4 FragColor;
 
layout(location = 0) in PerVertexData
{
  vec3 uvw;
} frag_in;  

layout(location = 0) uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, frag_in.uvw);
}