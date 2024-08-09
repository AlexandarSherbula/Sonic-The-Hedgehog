#include "aio_pch.h"
#include "RenderData.h"
#include "Renderer.h"

#include "ImGui/ImGuiLayer.h"

namespace Alexio
{
    Ref<VertexArray>  LineRenderer::vertexArray = nullptr;
    Ref<VertexBuffer> LineRenderer::vertexBuffer = nullptr;
    Ref<Shader>       LineRenderer::shader = nullptr;

    uint32_t LineRenderer::LineCount = 0;
    uint32_t LineRenderer::DrawingCount = 0;

    LineVertex* LineRenderer::CurrentVertexPtr = nullptr;
    LineVertex* LineRenderer::baseVertexBuffer = nullptr;

    void LineRenderer::Init()
    {
        const uint32_t maxVertexCount = 2 * MaxLinesPerBatch;

        baseVertexBuffer = new LineVertex[maxVertexCount];

        vertexArray = VertexArray::Create();
        vertexBuffer = VertexBuffer::Create(maxVertexCount * sizeof(LineVertex));

        BufferLayout layout =
        {
            {ShaderDataType::Float3, "aPosition" },
            {ShaderDataType::Float4, "aColor"    }
        };
        vertexBuffer->SetLayout(layout);

        vertexArray->AddVertexBuffer(vertexBuffer);

        shader = Shader::Create("line", vertexArray);
    }

    void LineRenderer::StartNewBatch()
    {
        LineCount = 0;
        DrawingCount = 0;
        CurrentVertexPtr = baseVertexBuffer;
    }

    void LineRenderer::SubmitBatch()
    {
        if (LineCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)CurrentVertexPtr - (uint8_t*)baseVertexBuffer);
            vertexBuffer->SetData(baseVertexBuffer, dataSize);

            vertexArray->Bind();
            shader->Bind();

            Renderer::Draw(LineCount * 2);
            DrawingCount++;
            Renderer::Stats.DrawLine++;

            shader->Unbind();
            vertexArray->Unbind();
        }
        StartNewBatch();
    }

    void LineRenderer::End()
    {
        delete[] baseVertexBuffer;
    }


    Ref<VertexArray>  QuadRenderer::vertexArray  = nullptr;
    Ref<VertexBuffer> QuadRenderer::vertexBuffer = nullptr;
    Ref<IndexBuffer>  QuadRenderer::indexBuffer  = nullptr;
    Ref<Shader>       QuadRenderer::shader       = nullptr;
    Ref<Texture>      QuadRenderer::WhiteTexture = nullptr;

    uint32_t QuadRenderer::QuadCount  = 0;
    uint32_t QuadRenderer::IndexCount = 0;
    uint32_t QuadRenderer::TextureSlotIndex = 0;
    uint32_t QuadRenderer::DrawingCount = 0;

    std::array<uint32_t, QuadRenderer::MaxTextureSlots> QuadRenderer::TextureIDs = { 0 };

    QuadVertex* QuadRenderer::CurrentVertexPtr = nullptr;
    QuadVertex* QuadRenderer::baseVertexBuffer = nullptr;

    void QuadRenderer::Init()
    {
        const uint32_t maxVertexCount = 4 * MaxQuadsPerBatch;
        const uint32_t maxIndexCount = 6 * MaxQuadsPerBatch;

        baseVertexBuffer = new QuadVertex[maxVertexCount];

        uint32_t* indices = new uint32_t[maxIndexCount];

        int32_t indexOffset = 0;
        for (size_t i = 0; i < MaxQuadsPerBatch; i++)
        {
            indices[i * 6 + 0] = 0 + indexOffset;
            indices[i * 6 + 1] = 1 + indexOffset;
            indices[i * 6 + 2] = 2 + indexOffset;
            indices[i * 6 + 3] = 2 + indexOffset;
            indices[i * 6 + 4] = 3 + indexOffset;
            indices[i * 6 + 5] = 0 + indexOffset;
        
            indexOffset += 4;
        }

        vertexArray  = VertexArray::Create();
        vertexBuffer = VertexBuffer::Create(maxVertexCount * sizeof(QuadVertex));
        indexBuffer  = IndexBuffer::Create(indices, maxIndexCount);
        delete[] indices;

        BufferLayout layout =
        {
            {ShaderDataType::Float3, "aPosition" },
            {ShaderDataType::Float4, "aColor"    },
            {ShaderDataType::Float2, "aTexCoord" },
            {ShaderDataType::Int,    "aTexIndex" }
        };
        vertexBuffer->SetLayout(layout);

        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);

        shader = Shader::Create("quad", vertexArray);

        WhiteTexture = Texture::Create(1, 1, 0xffffffff);
        WhiteTexture->Bind(TextureSlotIndex);
        TextureIDs[TextureSlotIndex] = WhiteTexture->GetID();
        TextureSlotIndex++;
	}

    void QuadRenderer::StartNewBatch()
    {
        QuadCount = 0;
        IndexCount = 0;
        TextureSlotIndex = 1;
        DrawingCount = 0;

        CurrentVertexPtr = baseVertexBuffer;
    }

    void QuadRenderer::SubmitBatch()
    {
        if (QuadCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)CurrentVertexPtr - (uint8_t*)baseVertexBuffer);
            vertexBuffer->SetData(baseVertexBuffer, dataSize);

            vertexArray->Bind();
            shader->Bind();

            Renderer::DrawIndexed(IndexCount);
            DrawingCount++;
            Renderer::Stats.DrawQuad++;

            shader->Unbind();
            vertexArray->Unbind();
        }
        StartNewBatch();
    }

    void QuadRenderer::End()
    {
        delete[] baseVertexBuffer;
    }

    Ref<VertexArray>  CircleRenderer::vertexArray = nullptr;
    Ref<VertexBuffer> CircleRenderer::vertexBuffer = nullptr;
    Ref<IndexBuffer>  CircleRenderer::indexBuffer = nullptr;
    Ref<Shader>       CircleRenderer::shader = nullptr;

    uint32_t CircleRenderer::CircleCount = 0;
    uint32_t CircleRenderer::IndexCount = 0;
    uint32_t CircleRenderer::DrawingCount = 0;

    CircleVertex* CircleRenderer::CurrentVertexPtr = nullptr;
    CircleVertex* CircleRenderer::baseVertexBuffer = nullptr;

    void CircleRenderer::Init()
    {
        const uint32_t maxVertexCount = 4 * MaxCirclesPerBatch;
        const uint32_t maxIndexCount = 6 * MaxCirclesPerBatch;

        baseVertexBuffer = new CircleVertex[maxVertexCount];

        uint32_t* indices = new uint32_t[maxIndexCount];

        int32_t indexOffset = 0;
        for (size_t i = 0; i < MaxCirclesPerBatch; i++)
        {
            indices[i * 6 + 0] = 0 + indexOffset;
            indices[i * 6 + 1] = 1 + indexOffset;
            indices[i * 6 + 2] = 2 + indexOffset;
            indices[i * 6 + 3] = 2 + indexOffset;
            indices[i * 6 + 4] = 3 + indexOffset;
            indices[i * 6 + 5] = 0 + indexOffset;

            indexOffset += 4;
        }

        vertexArray = VertexArray::Create();
        vertexBuffer = VertexBuffer::Create(maxVertexCount * sizeof(CircleVertex));
        indexBuffer = IndexBuffer::Create(indices, maxIndexCount);
        delete[] indices;

        BufferLayout layout =
        {
            {ShaderDataType::Float3, "aPosition"      },
            {ShaderDataType::Float3, "aLocalPosition" },
            {ShaderDataType::Float4, "aColor"         },
            {ShaderDataType::Float,  "aThickness"     },
            {ShaderDataType::Float,  "aFade"          }
        };
        vertexBuffer->SetLayout(layout);

        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);

        shader = Shader::Create("circle", vertexArray);
    }

    void CircleRenderer::StartNewBatch()
    {
        CircleCount = 0;
        IndexCount = 0;
        DrawingCount = 0;

        CurrentVertexPtr = baseVertexBuffer;
    }

    void CircleRenderer::SubmitBatch()
    {
        if (CircleCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)CurrentVertexPtr - (uint8_t*)baseVertexBuffer);
            vertexBuffer->SetData(baseVertexBuffer, dataSize);

            vertexArray->Bind();
            shader->Bind();

            Renderer::DrawIndexed(IndexCount);
            DrawingCount++;
            Renderer::Stats.DrawCircle++;

            shader->Unbind();
            vertexArray->Unbind();
        }
        StartNewBatch();
    }

    void CircleRenderer::End()
    {
        delete[] baseVertexBuffer;
    }
}

