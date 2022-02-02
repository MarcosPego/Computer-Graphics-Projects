#pragma once

#include "../util/filereader.h"
#include "../maths/matrix.h"
#include <GL/glew.h>

namespace cgj{
	namespace graphics {
		
		struct shader {
			GLuint shader_id;
			GLint modelMatrix_UId, viewMatrix_UId, projectionMatrix_UId;

			//const char* vert_path;
			//const char* frag_path;
			bool TexcoordsLoaded, NormalsLoaded;


			shader();
			~shader();

			GLint getUniformLocation(const GLchar * name);

			void setUniform1f(const GLchar* name, float value);
			void setUniform1i(const GLchar* name, int value);
			void setUniform2f(const GLchar* name, const vec2& vec);
			void setUniform3f(const GLchar* name, const vec3& vec);
			void setUniform4f(const GLchar* name, const vec4& vec);
			void setUniform4fv(const GLchar* name, const vec4& vec);
			void setUniformMat4(const GLchar* name, const mat4& matrix);

			void bindUniformBlock(const GLchar* sharedMatrices, const GLuint UBO_BP);

			void enable() const;
			void disable() const;

			GLuint load(std::string& vs_file, std::string& fs_file);
		};

		struct skyboxShader {
			GLuint shader_id;
			GLint modelMatrix_UId, viewMatrix_UId, projectionMatrix_UId;

			//const char* vert_path;
			//const char* frag_path;
			bool TexcoordsLoaded, NormalsLoaded;


			skyboxShader();
			~skyboxShader();

			GLint getUniformLocation(const GLchar* name);

			void setUniform1f(const GLchar* name, float value);
			void setUniform1i(const GLchar* name, int value);
			void setUniform2f(const GLchar* name, const vec2& vec);
			void setUniform3f(const GLchar* name, const vec3& vec);
			void setUniform4f(const GLchar* name, const vec4& vec);
			void setUniform4fv(const GLchar* name, const vec4& vec);
			void setUniformMat4(const GLchar* name, const mat4& matrix);

			void bindUniformBlock(const GLchar* sharedMatrices, const GLuint UBO_BP);

			void enable() const;
			void disable() const;

			GLuint load(std::string& vs_file, std::string& fs_file);
		};
	}
}