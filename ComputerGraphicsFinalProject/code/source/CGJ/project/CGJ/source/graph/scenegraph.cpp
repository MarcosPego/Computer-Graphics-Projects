#include "../graphics/camera.h"
#include "../graphics/shader.h"
#include "../meshLoader/mesh.h"
#include "../meshLoader/texture.h"
#include "../meshLoader/water.h"

#include <map>


#define _USE_MATH_DEFINES
#include <math.h>

using namespace cgj;

namespace cgj {
	typedef struct {
		vec3 parent_pos;
		float parent_rot;

		vec3 current_pos;
		float current_rot;


		vec3 scale;

		GLuint texture;

		

	} data;

	class scenenode {
	private:
		graphics::shader* shader;
		mesh current_mesh;
		mat4 matrix;
		vec4 color;
		std::vector< scenenode*> child_nodes;

		data* node_data;

		float tiling;


	public:
		scenenode() {}


		void set_tiling(float new_tiling) {
			tiling = new_tiling;
		}

		float get_tiling() {
			return tiling;
		}

		void set_data(data* new_node_data) {
			node_data = new_node_data;
		}

		data* get_data() {
			return node_data;
		}

		void set_shader(graphics::shader* new_shader) {
			shader = new_shader;
		}

		graphics::shader* get_shader() {
			return shader;
		}

		void set_mesh(mesh new_mesh) {
			current_mesh = new_mesh;
		}

		mesh get_mesh() {
			return current_mesh;
		}

		void set_color(vec4 new_color) {
			color = new_color;
		}

		vec4 get_color() {
			return color;
		}

		void set_matrix(mat4 new_matrix) {
			matrix = new_matrix;
		}

		mat4 get_matrix() {
			return matrix;
		}

		scenenode* createNode() {
			scenenode* node = new scenenode();
			node->set_shader(shader);
			child_nodes.push_back(node);
			return node;
		}


		void draw() {

			if (current_mesh.vao_id != NULL) {
				glUseProgram(shader->shader_id);

	

				shader->setUniformMat4("ModelMatrix", matrix);
				shader->setUniform4fv("color", color);
				shader->setUniform1f("tiling", tiling);
				current_mesh.draw();


				glUseProgram(0);


				for (scenenode* node : child_nodes) {

					glUseProgram(shader->shader_id);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, node->get_data()->texture);
					glUseProgram(0);

					node->draw();
				}
			}
		}

		void destroyScene() {
			current_mesh.destroy_mesh_data();
			for (scenenode* node : child_nodes) {
				node->destroyScene();
			}
		}

		void set_current_matrix() {
			for (scenenode* node : child_nodes) {
				node->set_matrix(MatrixFactory::createModelMatrix(node->get_data()->scale, node->get_data()->current_rot, node->get_data()->current_pos, node->get_data()->parent_pos, node->get_data()->parent_rot));
				if (child_nodes.size() > 0) node->set_current_matrix();
			}
		}
	};

	class scenegraph : scenenode {
	private:
		float WAVE_SPEED = 0.3f;
		float moveFactor = 0.0f;

		GLuint vaoId;
		graphics::camera* camera;
		graphics::camera* reflect_camera;
		graphics::shader* shader;
		graphics::shader* water_shader;

		graphics::skyboxShader* skybox_shader;
		std::vector< scenenode*> water_child_nodes;
		std::vector< scenenode*> child_nodes;

		vec3 oldMousePos;
		vec3 newMousePos;

		float zoom;

		skybox* scene_skybox;
		waterFrameBuffers* frame_buffers;


	public:
		std::map<int, int> scene_key_map;
		int to_flip_again = true;
		GLuint dudv_id = textureLoader::load_texture("source/assets/dudv_t.png");
		GLuint dudv_n_id = textureLoader::load_texture("source/assets/dudv_n.png");
		GLuint caustics = textureLoader::load_texture("source/assets/caustics.png");
		//GLuint floor = textureLoader::load_texture("source/assets/sand_shell.png");
		//GLuint coral = textureLoader::load_texture("source/assets/coral/coral_tex.png");
		float time;

		scenegraph() {}



		void set_water_shader(graphics::shader* new_water_shader) {
			water_shader = new_water_shader;
		}

		graphics::shader* get_water_shader() {
			return water_shader;
		}


		waterFrameBuffers* get_frame_buffers() {
			return frame_buffers;
		}

		void set_frame_buffers(waterFrameBuffers* new_frame_buffers) {
			frame_buffers = new_frame_buffers;
		}

		float get_zoom() {
			return zoom;
		}

		void set_zoom(float new_zoom) {
			zoom = new_zoom;
		}

		vec3 get_oldMousePos() {
			return oldMousePos;
		}

		vec3 get_newMousePos() {
			return newMousePos;
		}

		void set_oldMousePos(vec3 new_oldMousePos) {
			oldMousePos = new_oldMousePos;
		}

		void set_newMousePos(vec3 new_newMousePos) {
			newMousePos = new_newMousePos;
		}

		void set_skybox(skybox* new_skybox) {
			scene_skybox = new_skybox;
		}

		skybox* get_skybox() {
			return scene_skybox;
		}

		void set_camera(graphics::camera* new_camera) {
			camera = new_camera;
		}

		graphics::camera* get_camera() {
			return camera;
		}

		void set_reflect_camera(graphics::camera* new_camera) {
			reflect_camera = new_camera;
		}

		graphics::camera* get_reflect_camera() {
			return reflect_camera;
		}

		void set_shader(graphics::shader* new_shader) {
			shader = new_shader;
		}

		graphics::shader* get_shader() {
			return shader;
		}

		void set_skybox_shader(graphics::skyboxShader* new_skybox_shader) {
			skybox_shader = new_skybox_shader;
		}

		graphics::skyboxShader* get_skybox_shader() {
			return skybox_shader;
		}

		scenenode* createNode() {
			scenenode* node = new scenenode();
			node->set_shader(shader);
			child_nodes.push_back(node);
			return node;
		}

		scenenode* createWaterNode() {
			scenenode* node = new scenenode();
			node->set_shader(water_shader);
			water_child_nodes.push_back(node);
			return node;
		}

		void draw() {
			glEnable(GL_CLIP_DISTANCE0);

			glBindVertexArray(vaoId);
			glUseProgram(shader->shader_id);

			

			shader->setUniformMat4("ViewMatrix", camera->viewMatrix);
			shader->setUniformMat4("ProjectionMatrix", camera->projectionMatrix);
			shader->setUniform4f("clipPlane", vec4(0, -1, 0, 100000));

			glUseProgram(0);


			

			mat4 new_viewMatrix;
			for (scenenode* node : water_child_nodes) {

				moveFactor += time / 100 * WAVE_SPEED;
				moveFactor = fmod(moveFactor, 1);


				water_shader->enable();
				water_shader->setUniform1f("moveFactor", moveFactor);
				water_shader->disable();

				glUseProgram(shader->shader_id);
				shader->setUniform1f("moveFactor", moveFactor);
				shader->setUniformMat4("ViewMatrix", reflect_camera->viewMatrix);
				shader->setUniform4f("clipPlane", vec4(0, 1, 0, 0));
				glUseProgram(0);

				frame_buffers->bindReflectionFrameBuffer();

				renderScene(reflect_camera->viewMatrix);

				glUseProgram(shader->shader_id);
				shader->setUniformMat4("ViewMatrix", camera->viewMatrix);
				shader->setUniform4f("clipPlane", vec4(0, -1, 0, 0));

				glUseProgram(0);
				frame_buffers->bindRefractionFrameBuffer();
				renderScene(camera->viewMatrix);


				frame_buffers->unbindCurrentFrameBuffer();



				water_shader->enable();
				water_shader->setUniformMat4("ReflectedViewMatrix", reflect_camera->viewMatrix);
				water_shader->setUniformMat4("ViewMatrix", camera->viewMatrix);
				water_shader->setUniformMat4("ProjectionMatrix", camera->projectionMatrix);


				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frame_buffers->reflectionTexture);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, frame_buffers->refractionTexture);
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, dudv_id);
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, dudv_n_id);
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_2D, frame_buffers->refractionDepthTexture);


				node->draw();

				water_shader->disable();
			}

			glUseProgram(shader->shader_id);

			shader->setUniformMat4("ViewMatrix", camera->viewMatrix);
			shader->setUniformMat4("ProjectionMatrix", camera->projectionMatrix);
			shader->setUniform4f("clipPlane", vec4(0, -1, 0, 100000));

			glUseProgram(0);

			renderScene(camera->viewMatrix);

		}

		void renderScene(const mat4& view) {

			/*glUseProgram(shader->shader_id);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, floor);
			glUseProgram(0);*/



			for (scenenode* node : child_nodes) {

				glUseProgram(shader->shader_id);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, node->get_data()->texture);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, caustics);
				glUseProgram(0);

				node->draw();
			}

			glDepthFunc(GL_LEQUAL);
			skybox_shader->enable();

			mat4 fixed_view = mat4(mat3(view));

			skybox_shader->setUniformMat4("ViewMatrix", fixed_view);
			skybox_shader->setUniformMat4("ProjectionMatrix", camera->projectionMatrix);

			scene_skybox->bindSkyboxTexture();
			glDepthFunc(GL_LESS);

			skybox_shader->disable();

		}

		void destroyScene() {
			for (scenenode* node : child_nodes) {
				node->destroyScene();
			}
			for (scenenode* node : water_child_nodes) {
				node->destroyScene();
			}
		}

		void set_current_matrix() {
			for (scenenode* node : child_nodes) {
				node->set_matrix(MatrixFactory::createModelMatrix(node->get_data()->scale, node->get_data()->current_rot, node->get_data()->current_pos, node->get_data()->parent_pos, node->get_data()->parent_rot));
				node->set_current_matrix();
			}
		}
	};
}
