#type vertex
#version 450 core
			
layout (location = 0) in vec3  aPosition;
layout (location = 1) in vec3  aLocalPosition;
layout (location = 2) in vec4  aColor;
layout (location = 3) in float aThickness;
layout (location = 4) in float aFade;

struct VertexOutput
{
	vec3  localPosition;
	vec4  color;
	float thickness;
	float fade;
};

layout(location = 0) out VertexOutput outVertex;

layout (std140, binding = 0) uniform Camera
{
	mat4 projection;
};

void main()
{
	outVertex.localPosition = aLocalPosition;
	outVertex.color = aColor;
	outVertex.thickness = aThickness;
	outVertex.fade = aFade;

	gl_Position = projection * vec4(aPosition, 1.0);
}

#type pixel
#version 450 core

struct VertexOutput
{
	vec3  localPosition;
	vec4  color;
	float thickness;
	float fade;
};

layout(location = 0) in VertexOutput inVertex;

out vec4 pixel;

void main()
{
	float distance = 1.0 - length(inVertex.localPosition);
	
	float circle = smoothstep(0.0, inVertex.fade, distance);
	circle *= smoothstep(inVertex.thickness + inVertex.fade, inVertex.thickness, distance);

	if (circle == 0.0)
		discard;
	
	pixel = inVertex.color;
	pixel.a *= circle;
}