#include "shader.h"
#include <vector>
#include <iostream>

using namespace cgj::util;



#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2

namespace cgj {
	namespace graphics {

		shader::shader(){

		}


		/*shader::shader(const char* vertix_path, const char* fragment_path) : vert_path(vertix_path), frag_path(fragment_path)
		{
			//shader_id = load(false, false);			
		}*/

		shader::~shader() {
			glDeleteProgram(shader_id);
		}

		const std::string read(const std::string& filename)
		{
			std::ifstream ifile(filename);
			std::string shader_string, line;
			while (std::getline(ifile, line))
			{
				shader_string += line + "\n";
			}
			return shader_string;
		}

		const GLuint checkCompilation(const GLuint shader_id, const std::string& filename)
		{
			GLint compiled;
			glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
			if (compiled == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
				GLchar* const log = new char[length];
				glGetShaderInfoLog(shader_id, length, &length, log);
				std::cerr << "[" << filename << "] " << std::endl << log;
				delete[] log;
			}
			return compiled;
		}

		const GLuint addShader(const GLuint program_id, const GLenum shader_type, const std::string& filename)
		{
			const GLuint shader_id = glCreateShader(shader_type);
			const std::string scode = read(filename);
			const GLchar* code = scode.c_str();
			glShaderSource(shader_id, 1, &code, 0);
			glCompileShader(shader_id);
			checkCompilation(shader_id, filename);
			glAttachShader(program_id, shader_id);
			return shader_id;
		}

		GLuint shader::load(std::string& vs_file, std::string& fs_file) {
			shader_id = glCreateProgram();

			GLuint VertexShaderId = addShader(shader_id, GL_VERTEX_SHADER, vs_file);
			GLuint FragmentShaderId = addShader(shader_id, GL_FRAGMENT_SHADER, fs_file);

			glBindAttribLocation(shader_id, VERTICES, "in_Position");
			//if (TexcoordsLoaded)
			glBindAttribLocation(shader_id, TEXCOORDS, "inTexcoord");
			//if (NormalsLoaded)
			glBindAttribLocation(shader_id, NORMALS, "inNormal");

			glLinkProgram(shader_id);
			

			GLint linked;
			glGetProgramiv(shader_id, GL_LINK_STATUS, &linked);
			if (linked == GL_FALSE)
			{
				GLint length;
				glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &length);
				GLchar* const log = new char[length];
				glGetProgramInfoLog(shader_id, length, &length, log);
				std::cerr << "[LINK] " << std::endl << log << std::endl;
				delete[] log;
			}

			glDetachShader(shader_id, VertexShaderId);
			glDetachShader(shader_id, FragmentShaderId);
			glDeleteShader(VertexShaderId);
			glDeleteShader(FragmentShaderId);

			modelMatrix_UId = glGetUniformLocation(shader_id, "ModelMatrix");
			viewMatrix_UId = glGetUniformLocation(shader_id, "ViewMatrix");
			projectionMatrix_UId = glGetUniformLocation(shader_id, "ProjectionMatrix");

			return shader_id;
		}

		void shader::enable() const {
			glUseProgram(shader_id);

		}

		void shader::disable() const {
			glUseProgram(0);

		}

		GLint shader::getUniformLocation(const GLchar* name) {
			//a melhorar
			return glGetUniformLocation(shader_id, name);
		}

		void shader::setUniform1f(const GLchar* name, float value) {
			glUniform1f(getUniformLocation(name), value);
		}

		void shader::setUniform1i(const GLchar* name, int value) {
			glUniform1i(getUniformLocation(name), value);
		}

		void shader::setUniform2f(const GLchar* name, const vec2& vec) {
			glUniform2f(getUniformLocation(name), vec.x, vec.y);
		}

		void shader::setUniform3f(const GLchar* name, const vec3& vec) {
			glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
		}

		void shader::setUniform4f(const GLchar* name, const vec4& vec) {
			glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
		}

		void shader::setUniform4fv(const GLchar* name, const vec4& vec) {
			float color[4] = { vec.x, vec.y, vec.z, vec.w };
			glUniform4fv(getUniformLocation(name), 1, color);
		}

		void shader::setUniformMat4(const GLchar* name, const mat4& matrix) {
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.data);
		}

		void shader::bindUniformBlock(const GLchar* sharedMatrices, const GLuint UBO_BP) {
			glUniformBlockBinding(shader_id, glGetUniformBlockIndex(shader_id, sharedMatrices), UBO_BP);
		}


		//SKYBOX SHADER

		skyboxShader::skyboxShader() {

		}

		skyboxShader::~skyboxShader() {
			glDeleteProgram(shader_id);
		}



		GLuint skyboxShader::load(std::string& vs_file, std::string& fs_file) {
			shader_id = glCreateProgram();

			GLuint VertexShaderId = addShader(shader_id, GL_VERTEX_SHADER, vs_file);
			GLuint FragmentShaderId = addShader(shader_id, GL_FRAGMENT_SHADER, fs_file);

			glBindAttribLocation(shader_id, VERTICES, "in_Position");

			glLinkProgram(shader_id);


			GLint linked;
			glGetProgramiv(shader_id, GL_LINK_STATUS, &linked);
			if (linked == GL_FALSE)
			{
				GLint length;
				glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &length);
				GLchar* const log = new char[length];
				glGetProgramInfoLog(shader_id, length, &length, log);
				std::cerr << "[LINK] " << std::endl << log << std::endl;
				delete[] log;
			}

			glDetachShader(shader_id, VertexShaderId);
			glDetachShader(shader_id, FragmentShaderId);
			glDeleteShader(VertexShaderId);
			glDeleteShader(FragmentShaderId);

			viewMatrix_UId = glGetUniformLocation(shader_id, "ViewMatrix");
			projectionMatrix_UId = glGetUniformLocation(shader_id, "ProjectionMatrix");

			return shader_id;
		}

		void skyboxShader::enable() const {
			glUseProgram(shader_id);

		}

		void skyboxShader::disable() const {
			glUseProgram(0);

		}

		GLint skyboxShader::getUniformLocation(const GLchar* name) {
			//a melhorar
			return glGetUniformLocation(shader_id, name);
		}

		void skyboxShader::setUniform1f(const GLchar* name, float value) {
			glUniform1f(getUniformLocation(name), value);
		}

		void skyboxShader::setUniform1i(const GLchar* name, int value) {
			glUniform1i(getUniformLocation(name), value);
		}

		void skyboxShader::setUniform2f(const GLchar* name, const vec2& vec) {
			glUniform2f(getUniformLocation(name), vec.x, vec.y);
		}

		void skyboxShader::setUniform3f(const GLchar* name, const vec3& vec) {
			glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
		}

		void skyboxShader::setUniform4f(const GLchar* name, const vec4& vec) {
			glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
		}

		void skyboxShader::setUniform4fv(const GLchar* name, const vec4& vec) {
			float color[4] = { vec.x, vec.y, vec.z, vec.w };
			glUniform4fv(getUniformLocation(name), 1, color);
		}

		void skyboxShader::setUniformMat4(const GLchar* name, const mat4& matrix) {
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.data);
		}

		void skyboxShader::bindUniformBlock(const GLchar* sharedMatrices, const GLuint UBO_BP) {
			glUniformBlockBinding(shader_id, glGetUniformBlockIndex(shader_id, sharedMatrices), UBO_BP);
		}
	}
}