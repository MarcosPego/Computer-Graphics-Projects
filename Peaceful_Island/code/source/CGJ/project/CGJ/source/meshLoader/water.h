#pragma once

#include "mesh.h"
#include <GL/glew.h>

namespace cgj {
		struct waterFrameBuffers {
		static const int REFLECTION_WIDTH = 320;
		static const int REFLECTION_HEIGHT = 180;

		static const int REFRACTION_WIDTH = 1280;
		static const int REFRACTION_HEIGHT = 720;

		static const int WINDOW_WIDTH = 1280;
		static const int WINDOW_HEIGHT = 720;

		

		GLuint reflectionFrameBuffer;
		GLuint reflectionTexture;
		GLuint reflectionDepthBuffer;

		GLuint refractionFrameBuffer;
		GLuint refractionTexture;
		GLuint refractionDepthTexture;


		waterFrameBuffers();
		void destroy_buffer_data();

		void bindReflectionFrameBuffer();
		void bindRefractionFrameBuffer();

		void unbindCurrentFrameBuffer();

		void initialiseReflectionFrameBuffer();
		void initialiseRefractionFrameBuffer();


	};
}