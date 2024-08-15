#include "Water.h"

static std::array<Alexio::Vector3, 4> localPosition =
{
	Alexio::Vector3(-0.5f, -0.5f, 0.0f),
	Alexio::Vector3(0.5f, -0.5f, 0.0f),
	Alexio::Vector3(0.5f,  0.5f, 0.0f),
	Alexio::Vector3(-0.5f,  0.5f, 0.0f),
};

Water::Water()
{
}

Water::Water(const Alexio::Vector2& position, int widthRadius, int heightRadius)
{
	this->position = position;
	mHitbox.widthRad = widthRadius;
	mHitbox.heightRad = heightRadius;
	
	uint32_t* indices = new uint32_t[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;

	vertexArray =  Alexio::VertexArray::Create();
	vertexBuffer = Alexio::VertexBuffer::Create(4 * sizeof(Alexio::QuadVertex));
	indexBuffer = Alexio::IndexBuffer::Create(indices, 6);
	delete[] indices;

	Alexio::BufferLayout layout =
	{
		{Alexio::ShaderDataType::Float3, "aPosition" },
		{Alexio::ShaderDataType::Float4, "aColor"    },
		{Alexio::ShaderDataType::Float2, "aTexCoord" },
		{Alexio::ShaderDataType::Int,    "aTexIndex" }
	};
	vertexBuffer->SetLayout(layout);

	vertexArray->AddVertexBuffer(vertexBuffer);
	vertexArray->SetIndexBuffer(indexBuffer);

	shader = Alexio::Shader::Create("water", vertexArray);
}

void Water::Draw()
{
	Draw(position, { 160.0f, 160.0f });
}

void Water::Draw(const Alexio::Vector2& position, const Alexio::Vector2& size, const Alexio::Vector4& color)
{
	vertexData[0].position = { position.x, position.y, 0.0f };
	vertexData[0].color = color;
	vertexData[0].texCoord = { 0.0f, 0.0f };
	vertexData[0].textureIndex = 0;

	vertexData[1].position = { position.x + size.x, position.y, 0.0f };
	vertexData[1].color = color;
	vertexData[1].texCoord = { 1.0f, 0.0f };
	vertexData[1].textureIndex = 0;

	vertexData[2].position = { position.x + size.x, position.y + size.y, 0.0f };
	vertexData[2].color = color;
	vertexData[2].texCoord = { 1.0f, 1.0f };
	vertexData[2].textureIndex = 0;

	vertexData[3].position = { position.x, position.y + size.y, 0.0f };
	vertexData[3].color = color;
	vertexData[3].texCoord = { 0.0f, 1.0f };
	vertexData[3].textureIndex = 0;

	vertexBuffer->SetData(vertexData.data(), sizeof(vertexData));

	vertexArray->Bind();
	shader->Bind();
	Alexio::QuadRenderer::GetWhiteTexture()->Bind(0);

	Alexio::Renderer::DrawIndexed(6);

	Alexio::QuadRenderer::GetWhiteTexture()->Unbind();
	shader->Unbind();
	vertexArray->Unbind();
}
