#type vertex
#version 450 core
			
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTexIndex;

struct VertexOutput
{
	vec4 color;
	vec2 texCoord;
	float texIndex;
};

layout(location = 0) out VertexOutput outVertex;

layout (std140, binding = 0) uniform Camera
{
	mat4 projection;
};

void main()
{	
	outVertex.color = aColor;
	outVertex.texCoord = aTexCoord;
	outVertex.texIndex = aTexIndex;
	gl_Position = projection * vec4(aPosition, 1.0);
}

#type pixel
#version 450 core
			
out vec4 pixel;

struct VertexOutput
{
	vec4 color;
	vec2 texCoord;
	float texIndex;
};

layout(location = 0) in VertexOutput inVertex;

layout(binding = 0) uniform sampler2D uTexture[32];

void main()
{
    int index = int(inVertex.texIndex);
    pixel = vec4(1.0, 1.0, 1.0, 1.0);

	switch (index)
    {
        case 0:  pixel = texture(uTexture[0], inVertex.texCoord) * vec4(inVertex.color); break;
        case 1:  pixel = texture(uTexture[1], inVertex.texCoord) * vec4(inVertex.color); break;
        case 2:  pixel = texture(uTexture[2], inVertex.texCoord) * vec4(inVertex.color); break;
        case 3:  pixel = texture(uTexture[3], inVertex.texCoord) * vec4(inVertex.color); break;
        case 4:  pixel = texture(uTexture[4], inVertex.texCoord) * vec4(inVertex.color); break;
        case 5:  pixel = texture(uTexture[5], inVertex.texCoord) * vec4(inVertex.color); break;
        case 6:  pixel = texture(uTexture[6], inVertex.texCoord) * vec4(inVertex.color); break;
        case 7:  pixel = texture(uTexture[7], inVertex.texCoord) * vec4(inVertex.color); break;
        case 8:  pixel = texture(uTexture[8], inVertex.texCoord) * vec4(inVertex.color); break;
        case 9:  pixel = texture(uTexture[9], inVertex.texCoord) * vec4(inVertex.color); break;
        case 10: pixel = texture(uTexture[10], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 11: pixel = texture(uTexture[11], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 12: pixel = texture(uTexture[12], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 13: pixel = texture(uTexture[13], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 14: pixel = texture(uTexture[14], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 15: pixel = texture(uTexture[15], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 16: pixel = texture(uTexture[16], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 17: pixel = texture(uTexture[17], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 18: pixel = texture(uTexture[18], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 19: pixel = texture(uTexture[19], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 20: pixel = texture(uTexture[20], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 21: pixel = texture(uTexture[21], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 22: pixel = texture(uTexture[22], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 23: pixel = texture(uTexture[23], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 24: pixel = texture(uTexture[24], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 25: pixel = texture(uTexture[25], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 26: pixel = texture(uTexture[26], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 27: pixel = texture(uTexture[27], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 28: pixel = texture(uTexture[28], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 29: pixel = texture(uTexture[29], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 30: pixel = texture(uTexture[30], inVertex.texCoord) * vec4(inVertex.color);  break;
        case 31: pixel = texture(uTexture[31], inVertex.texCoord) * vec4(inVertex.color);  break;
    }
}