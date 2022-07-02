#include "PCH.h"
#include "OpenGLShader.h"
#include <filesystem>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

static GLenum ShaderTypeFromString(const std::string& type)
{
	if (type == "vertex") return GL_VERTEX_SHADER;
	if (type == "fragment") return GL_FRAGMENT_SHADER;

	return 0;
}

OpenGLShader::OpenGLShader(const std::string& filepath)
{
	std::string source = ReadFile(filepath);
	auto shader_sources = PreProcess(source);
	Compile(shader_sources);

	std::filesystem::path path(filepath);
	m_Name = path.stem().string();
}

OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	:m_Name(name)
{
	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER] = vertexSrc;
	sources[GL_FRAGMENT_SHADER] = fragmentSrc;
	Compile(sources);
}

OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(m_RendererID);
}

void OpenGLShader::Bind()
{
	glUseProgram(m_RendererID);
}

void OpenGLShader::UnBind()
{
	glUseProgram(0);
}

void OpenGLShader::SetInt(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
{
	glUniform1iv(GetUniformLocation(name), count, values);
}

void OpenGLShader::SetFloat(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
{
	glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
{
	glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
{
	glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& value)
{
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::SetBool(const std::string& name, bool value)
{
	glUniform1i(GetUniformLocation(name), value);
}

std::string OpenGLShader::ReadFile(const std::string& filepath)
{
	std::string result;
	std::ifstream in(filepath, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		if (size != -1)
		{
			result.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(&result[0], size);
		}
		else
		{
			LOG_ERROR("Could not read from file {0}", filepath.c_str());
			CORE_ASSERT(false);
		}
	}
	else
	{
		LOG_ERROR("Could not open file {0}", filepath.c_str());
		CORE_ASSERT(false);
	}

	return result;
}

std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
{
	std::unordered_map<GLenum, std::string> shader_sources;

	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0);
	while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos);
		CORE_ASSERT(eol != std::string::npos, "Syntax error");
		size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);
		CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

		size_t nextLinePos = source.find_first_not_of("\r\n", eol);
		CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");

		pos = source.find(typeToken, nextLinePos);

		shader_sources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) :
			source.substr(nextLinePos, pos - nextLinePos);
	}

	return shader_sources;
}

void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{
	GLuint program = glCreateProgram();

	std::array<GLenum, 2> glShaderIDs;

	int glShaderIDIndex = 0;
	for (auto& kv : shaderSources)
	{
		GLenum type = kv.first;
		const std::string& source = kv.second;

		GLuint shader = glCreateShader(type);

		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			LOG_ERROR("{0}", infoLog.data());
			CORE_ASSERT(false);

			break;
		}

		glAttachShader(program, shader);
		glShaderIDs[glShaderIDIndex++] = shader;
	}

	m_RendererID = program;

	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*) & isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(program);

		for (auto id : glShaderIDs)
			glDeleteShader(id);

		LOG_ERROR("{0}", infoLog.data());
		CORE_ASSERT(false);

		return;
	}

	for (auto id : glShaderIDs)
	{
		glDetachShader(program, id);
		glDeleteShader(id);
	}
}

GLint OpenGLShader::GetUniformLocation(const std::string& name)
{
	return glGetUniformLocation(m_RendererID, name.c_str());
}
