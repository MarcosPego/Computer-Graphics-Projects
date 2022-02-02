#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>



namespace cgj {
	

	struct skybox {
		GLuint textureID;
		GLuint skyboxVAO;
		GLuint skyboxVBO;


		skybox();

		void create_skybox();
		void loadSkybox(std::vector<std::string> faces);
		void bindSkyboxTexture();
		void unbindSkyboxTexture();
		void destroy_skybox_data();

		
	};

	struct textureLoader {

		static GLuint load_texture(std::string texture);
	};
}
