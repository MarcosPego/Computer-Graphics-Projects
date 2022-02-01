#include "water.h"
#include <iostream>


namespace cgj {

	waterFrameBuffers::waterFrameBuffers() {
		initialiseReflectionFrameBuffer();
		initialiseRefractionFrameBuffer();
	}

	void waterFrameBuffers::destroy_buffer_data() {
		glDeleteFramebuffers(1, &reflectionFrameBuffer);
		glDeleteTextures(1, &reflectionTexture);
		glDeleteRenderbuffers(1, &reflectionDepthBuffer);
		glDeleteFramebuffers(1, &refractionFrameBuffer);
		glDeleteTextures(1, &refractionTexture);
		glDeleteTextures(1, &refractionDepthTexture);
	}

	void waterFrameBuffers::initialiseReflectionFrameBuffer() {
		// CREATE FRAME BUFFER
		glGenFramebuffers(1, &reflectionFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, reflectionFrameBuffer);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);

		// CREATE TEXTURE ATTACHMENT 
		glGenTextures(1, &reflectionTexture);
		glBindTexture(GL_TEXTURE_2D, reflectionTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFLECTION_WIDTH, REFLECTION_HEIGHT,
			0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, reflectionTexture, 0);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		//	reflectionTexture, 0);


		//apagar se for preciso
		//GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		//glDrawBuffers(1, DrawBuffers);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << "Water buffer failed" << std::endl;



		// CREATE DEPTH BUFFER

		glGenRenderbuffers(1, &reflectionDepthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, reflectionDepthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, REFLECTION_WIDTH,
			REFLECTION_HEIGHT);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_RENDERBUFFER, reflectionDepthBuffer);

		unbindCurrentFrameBuffer();
	}



	void waterFrameBuffers::initialiseRefractionFrameBuffer() {

		// CREATE FRAME BUFFER
		glGenFramebuffers(1, &refractionFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, refractionFrameBuffer);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);

		// CREATE TEXTURE ATTACHMENT 
		glGenTextures(1, &refractionTexture);
		glBindTexture(GL_TEXTURE_2D, refractionTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, REFRACTION_WIDTH, REFRACTION_HEIGHT,
			0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			refractionTexture, 0);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//apagar se for preciso
		//GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		//glDrawBuffers(1, DrawBuffers);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << "Water buffer failed" << std::endl;


		// CREATE DEPTH TEXTURE

		glGenTextures(1, &refractionDepthTexture);
		glBindTexture(GL_TEXTURE_2D, refractionDepthTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, REFRACTION_WIDTH, REFRACTION_HEIGHT,
			0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			refractionDepthTexture, 0);

		unbindCurrentFrameBuffer();
	}

	void waterFrameBuffers::bindReflectionFrameBuffer() {
		glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
		glBindFramebuffer(GL_FRAMEBUFFER, reflectionFrameBuffer);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, REFLECTION_WIDTH, REFLECTION_HEIGHT);
	}

	void waterFrameBuffers::bindRefractionFrameBuffer() {
		glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
		glBindFramebuffer(GL_FRAMEBUFFER, refractionFrameBuffer);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, REFRACTION_WIDTH, REFRACTION_HEIGHT);
	}

	void waterFrameBuffers::unbindCurrentFrameBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	}



}