#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <shaderc/shaderc.hpp>

class Shader
{
public:
	Shader(std::filesystem::path path)
	{
		if (std::filesystem::exists(path))
		{
			// Shader compilation.
			std::ifstream file(path);
			std::string source(std::istreambuf_iterator<char>(file), {});
			file.close();

			shaderc_shader_kind kind = shaderc_mesh_shader;
			GLenum type = GL_MESH_SHADER_NV;
			if (path.extension() == ".mesh")
			{
				kind = shaderc_mesh_shader;
				type = GL_MESH_SHADER_NV;
			}
			else if (path.extension() == ".frag")
			{
				kind = shaderc_fragment_shader;
				type = GL_FRAGMENT_SHADER;
			}

			shaderc::Compiler compiler;
			shaderc::CompileOptions options;
			options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
			options.SetOptimizationLevel(shaderc_optimization_level_zero);
			options.SetGenerateDebugInfo();
			shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(source, kind, path.filename().string().c_str(), options);
			if (result.GetCompilationStatus() != shaderc_compilation_status_success)
				spdlog::error("\n" + result.GetErrorMessage());

			m_Id = glCreateShader(type);
			GLsizei size = static_cast<GLsizei>(std::distance(result.begin(), result.end()) * sizeof(uint32_t));
			glShaderBinary(1, &m_Id, GL_SHADER_BINARY_FORMAT_SPIR_V, result.cbegin(), size);

			glSpecializeShader(m_Id, "main", 0, nullptr, nullptr);

			GLint compiled; glGetShaderiv(m_Id, GL_COMPILE_STATUS, &compiled);
			if (compiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(m_Id, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> compiler_log(maxLength);
				glGetShaderInfoLog(m_Id, static_cast<GLsizei>(compiler_log.size()), nullptr, compiler_log.data());
				glDeleteShader(m_Id);
				m_Id = 0;

				spdlog::error("shader {0} contains error(s):\n\n{1}", path.filename().string().c_str(), compiler_log.data());
			}
		}
		else
		{
			spdlog::error("Shader: {} not exists!", path.string().c_str());
		}
	}

	GLuint GetID() const
	{
		return m_Id;
	}

	static GLuint CreateProgram(const Shader& mesh, const Shader& frag)
	{
		GLuint program = glCreateProgram();
		glAttachShader(program, mesh.GetID());
		glAttachShader(program, frag.GetID());
		glLinkProgram(program);

		GLint linked; glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> compiler_log(maxLength);
			glGetProgramInfoLog(program, static_cast<GLsizei>(compiler_log.size()), nullptr, compiler_log.data());
			glDeleteProgram(program);
			program = 0;

			spdlog::error("program contains error(s):\n\n{}", compiler_log.data());
		}

		glDetachShader(program, mesh.GetID());
		glDetachShader(program, frag.GetID());
		return program;
	}

private:
	GLuint m_Id = 0;
};