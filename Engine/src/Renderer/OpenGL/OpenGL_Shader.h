#pragma once

#include "Renderer/Shader.h"

#if defined(AIO_API_OPENGL)
namespace Alexio
{
	class OpenGL_Shader : public Shader
	{
	public:
		OpenGL_Shader(const std::string& name, const Ref<VertexArray>& vertexArray);
		OpenGL_Shader(const std::string& name, const std::string& filepath, const Ref<VertexArray>& vertexArray);
		OpenGL_Shader(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc, const Ref<VertexArray>& vertexArray);
		~OpenGL_Shader();


		void Bind() const override;
		void Unbind() const override;

		void SetInt(const std::string& name, int32_t value) override;
		void SetIntArray(const std::string& name, int32_t* values, uint32_t count) override;
		void SetFloat(const std::string& name, float value) override;
		void SetFloat2(const std::string& name, const glm::vec2& value) override;
		void SetFloat3(const std::string& name, const glm::vec3& value) override;
		void SetFloat4(const std::string& name, const glm::vec4& value) override;

		void SetMat3x3(const std::string& name, const glm::mat3x3& matrix) override;
		void SetMat4x4(const std::string& name, const glm::mat4x4& matrix) override;
	private:
		void Compile(const Ref<VertexArray>& vertexArray);
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	private:
		uint32_t mID;
		std::unordered_map<GLenum, std::string> mShaderSource;
	};
}
#endif