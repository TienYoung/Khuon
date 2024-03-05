#version 460

layout(location = 0) out vec4 FragColor;
 
layout(location = 0) in PerVertexData
{
  vec4 color;
  vec3 viewDirWS;  
  vec3 tangentWS;
} frag_in;  

layout(std140, binding = 1) uniform Light
{
	vec3 direction;
	float padding0;
	vec3 color;
	float padding1;
} Sun;
 
float StrandSpecular(vec3 T, vec3 V, vec3 L, float exponent)
{
	vec3 H = normalize(V + L);
	float ToH = dot(T, H);
	float sinToH = sqrt(1.0 - ToH * ToH);
	float dirAtten = smoothstep(-1.0, 0.0, ToH);

	return dirAtten * pow(sinToH, exponent);
}

void main()
{
	FragColor.rgb = frag_in.color.rgb * StrandSpecular(normalize(frag_in.tangentWS), normalize(frag_in.viewDirWS), normalize(Sun.direction), 16) + vec3(0.1);
	FragColor.a = frag_in.color.a + 0.3;
}