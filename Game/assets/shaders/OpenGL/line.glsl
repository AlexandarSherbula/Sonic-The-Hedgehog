#type vertex
#version 450 core

layout (std140, binding = 0) uniform Camera
{
	mat4 projection;
};
			
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;

out vec4 vertexColor;

void main()
{	
	vertexColor = aColor;
	gl_Position = projection * vec4(aPosition, 1.0);
}

#type pixel
#version 450 core
			
out vec4 pixel;

in vec4 vertexColor;

void main()
{
	pixel = vertexColor;
}