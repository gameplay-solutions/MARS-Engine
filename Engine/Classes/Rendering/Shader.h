#pragma once

#include "CoreMinimal.h"
#include "glm\ext\matrix_float4x4.hpp"

inline namespace MARS
{
	class Shader
	{
	public:

		Shader() = default;
		Shader(const String& VertexShader, const String& FragShader);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const glm::mat4& Matrix, const String& UniformName);

	private:

		uint32 RendererID;
	};
}