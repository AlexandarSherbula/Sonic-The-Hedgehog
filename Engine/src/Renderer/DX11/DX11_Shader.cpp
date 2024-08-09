#include "aio_pch.h"

#if defined(AIO_API_DX11)
#include "DX11_Shader.h"
#include "DX11_Backend.h"

#include "Alexio/Engine.h"

namespace Alexio
{
	static DXGI_FORMAT ShaderDataTypeSizeToDX11BaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return DXGI_FORMAT_R32_FLOAT;
		case ShaderDataType::Float2:   return DXGI_FORMAT_R32G32_FLOAT;
		case ShaderDataType::Float3:   return DXGI_FORMAT_R32G32B32_FLOAT;
		case ShaderDataType::Float4:   return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ShaderDataType::Int:      return DXGI_FORMAT_R32_SINT;
		case ShaderDataType::Int2:     return DXGI_FORMAT_R32G32_SINT;
		case ShaderDataType::Int3:     return DXGI_FORMAT_R32G32B32_SINT;
		case ShaderDataType::Int4:     return DXGI_FORMAT_R32G32B32A32_SINT;
		}

		AIO_ASSERT(false, "Unknown ShaderDataType!");
		return DXGI_FORMAT_UNKNOWN;
	}

	DX11_Shader::DX11_Shader(const std::string& name, const Ref<VertexArray>& vertexArray)
	{
		mName = name;
		mVertexSource = mPixelSource = "assets/shaders/DX11/" + name + ".hlsl";

		Compile(vertexArray);
	}

	DX11_Shader::DX11_Shader(const std::string& name, const std::string& filepath, const Ref<VertexArray>& vertexArray)
	{
		mName = name;
		mVertexSource = filepath;
		mPixelSource = filepath;

		Compile(vertexArray);
	}

	DX11_Shader::DX11_Shader(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc, const Ref<VertexArray>& vertexArray)
	{
		mName = name;
		mVertexSource = vertexSrc;
		mPixelSource = pixelSrc;

		Compile(vertexArray);
	}

	DX11_Shader::~DX11_Shader()
	{
	}

	void DX11_Shader::Compile(const Ref<VertexArray>& vertexArray)
	{
		////////// VERTEX SHADER /////////////////
		ID3DBlob* vertexErrorMessage;
		HRESULT hr = D3DCompileFromFile(StringToWide(mVertexSource).c_str(), NULL, NULL, "VSMain", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS,
			0, &mVertexShaderBuffer, &vertexErrorMessage);
		AIO_ASSERT(SUCCEEDED(hr), "Failed to load shader: " + mVertexSource + "\n" + reinterpret_cast<const char*>(vertexErrorMessage->GetBufferPointer()));

		std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDesc;
		for (auto& vertexBuffer : vertexArray->GetVertexBuffers())
		{
			auto& layout = vertexBuffer->GetLayout();
			for (auto& element : layout)
			{
				layoutDesc.push_back({ element.name.c_str(), 0, ShaderDataTypeSizeToDX11BaseType(element.type), 0, element.offset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
			}
		}

		hr = AIO_DX11_RENDERER->GetDevice()->CreateInputLayout(layoutDesc.data(),
			layoutDesc.size(),
			mVertexShaderBuffer->GetBufferPointer(),
			mVertexShaderBuffer->GetBufferSize(),
			mVertexLayout.GetAddressOf());
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create vertex layout: " + mVertexSource + "\n" + ResultInfo(hr));

		hr = AIO_DX11_RENDERER->GetDevice()->CreateVertexShader(mVertexShaderBuffer->GetBufferPointer(), mVertexShaderBuffer->GetBufferSize(), NULL, &mVertexShader);
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create vertex shader: " + mVertexSource + "\n" + ResultInfo(hr));

		////////// PIXEL SHADER /////////////////
		ID3DBlob* pixelErrorMessage;
		hr = D3DCompileFromFile(StringToWide(mPixelSource).c_str(), NULL, NULL, "PSMain", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS,
			0, mPixelShaderBuffer.GetAddressOf(), &pixelErrorMessage);
		AIO_ASSERT(SUCCEEDED(hr), "Failed to load shader: " + mPixelSource + "\n" + reinterpret_cast<const char*>(pixelErrorMessage->GetBufferPointer()));

		hr = AIO_DX11_RENDERER->GetDevice()->CreatePixelShader(mPixelShaderBuffer->GetBufferPointer(), mPixelShaderBuffer->GetBufferSize(), NULL, &mPixelShader);
		AIO_ASSERT(SUCCEEDED(hr), "Failed to create pixel shader: " + mPixelSource + "\n" + ResultInfo(hr));
	}

	void DX11_Shader::Bind() const
	{
		AIO_DX11_RENDERER->GetDeviceContext()->IASetInputLayout(mVertexLayout.Get());

		AIO_DX11_RENDERER->GetDeviceContext()->VSSetShader(mVertexShader.Get(), NULL, 0);
		AIO_DX11_RENDERER->GetDeviceContext()->PSSetShader(mPixelShader.Get(), NULL, 0);
	}

	void DX11_Shader::Unbind() const
	{
		AIO_DX11_RENDERER->GetDeviceContext()->VSSetShader(nullptr, NULL, 0);
		AIO_DX11_RENDERER->GetDeviceContext()->PSSetShader(nullptr, NULL, 0);
	}
}
#endif