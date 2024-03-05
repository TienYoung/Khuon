#version 450

layout(location = 0) out vec4 FragColor;
 
layout(location = 0) in PerVertexData
{
  vec4 color;
} frag_in;  
 
void main()
{
  FragColor = vec4(frag_in.color);
}