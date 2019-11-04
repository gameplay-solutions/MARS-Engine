#include "Rendering/Shader.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

MARS::Shader::Shader(const String& VertexShader, const String& FragShader)
{
	uint32 vShader = glCreateShader(GL_VERTEX_SHADER);

	const CHAR* Source = VertexShader.c_str();
	glShaderSource(vShader, 1, &Source, 0);
	glCompileShader(vShader);

	int32 bCompiled = 0;
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &bCompiled);

	if (!bCompiled)
	{
		int32 Length = 0;
		glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &Length);

		Array<CHAR> InfoLog(Length);
		glGetShaderInfoLog(vShader, Length, &Length, &InfoLog[0]);
		glDeleteShader(vShader);

		Log::Get(LogGraphics).Error("{}", InfoLog.data());

		return;
	}

	uint32 fShader = glCreateShader(GL_FRAGMENT_SHADER);
	Source = FragShader.c_str();
	glShaderSource(fShader, 1, &Source, 0);

	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &bCompiled);

	if (!bCompiled)
	{
		int32 Length = 0;
		glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &Length);

		Array<CHAR> InfoLog(Length);
		glGetShaderInfoLog(fShader, Length, &Length, &InfoLog[0]);
		glDeleteShader(fShader);

		Log::Get(LogGraphics).Error("{}", InfoLog.data());

		return;
	}

	RendererID = glCreateProgram();
	glAttachShader(RendererID, vShader);
	glAttachShader(RendererID, fShader);

	glLinkProgram(RendererID);

	int32 bLinked = 0;
	glGetProgramiv(RendererID, GL_LINK_STATUS, &bLinked);
	if (!bLinked)
	{
		int32 Length = 0;
		glGetProgramiv(RendererID, GL_INFO_LOG_LENGTH, &Length);

		Array<CHAR> InfoLog(Length);
		glGetProgramInfoLog(RendererID, Length, &Length, &InfoLog[0]);

		glDeleteProgram(RendererID);

		glDeleteShader(vShader);
		glDeleteShader(fShader);

		Log::Get(LogGraphics).Error("{}", InfoLog.data());

		return;
	}

	glDetachShader(RendererID, vShader);
	glDetachShader(RendererID, fShader);
}

MARS::Shader::~Shader()
{
	glDeleteShader(RendererID);
}

void MARS::Shader::Bind() const
{
	glUseProgram(RendererID);
}

void MARS::Shader::Unbind() const
{
	glUseProgram(0);
}

void MARS::Shader::UploadUniformMat4(const glm::mat4& Matrix, const String& UniformName)
{
	GLint Location = glGetUniformLocation(RendererID, UniformName.c_str());
	glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Matrix));
}
