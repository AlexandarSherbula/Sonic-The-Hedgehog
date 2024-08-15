#pragma once

#include "Object.h"
#include "Alexio/Engine.h"

class Water : public Object
{
public:
	Water();
	Water(const Alexio::Vector2& position, int widthRadius, int heightRadius);
	

	void Draw() override;
private:
	void Draw(const Alexio::Vector2& position, const Alexio::Vector2& size, const Alexio::Vector4& color = Alexio::Vector4(1.0f));
private:
	std::array<Alexio::QuadVertex, 4> vertexData;

	Alexio::Ref<Alexio::VertexArray>  vertexArray;
	Alexio::Ref<Alexio::VertexBuffer> vertexBuffer;
	Alexio::Ref<Alexio::IndexBuffer>  indexBuffer;
	Alexio::Ref<Alexio::Shader>       shader;
};