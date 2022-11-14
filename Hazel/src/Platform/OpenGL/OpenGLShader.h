#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Hazel/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace Hazel
{

	class OpenGLShader : public Shader
	{
	public:


		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& name, const int value);

		void UploadUniformFloat1(const std::string& name, const float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);

		void UploadUniformMat4(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProsess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string> shaderSource);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}