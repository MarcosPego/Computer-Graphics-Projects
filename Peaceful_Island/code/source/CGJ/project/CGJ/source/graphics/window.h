#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <ctime>  

#include "shader.h"
#include "camera.h"

namespace cgj {
	namespace graphics {
		void glfw_error_callback(int error, const char* description);
		void window_close_callback(GLFWwindow* win);
		void window_size_callback(GLFWwindow* win, int winx, int winy);

		struct window {
			GLFWwindow* Window;
			//shader assoc_shader;
			std::chrono::time_point<std::chrono::system_clock> lastFrameTime;
			std::chrono::duration<double, std::milli> delta;

			window(int major, int minor,
				int winx, int winy, const char* title, int is_fullscreen, int is_vsync);

			static GLFWwindow* setupWindow(int winx, int winy, const char* title,
				int is_fullscreen, int is_vsync);
			//static GLFWwindow* setupGLFW(int gl_major, int gl_minor,
			//	int winx, int winy, const char* title, int is_fullscreen, int is_vsync);



			GLFWwindow* setup(int major, int minor,
				int winx, int winy, const char* title, int is_fullscreen, int is_vsync);


			//void window_close_callback(GLFWwindow* win);
			//void window_size_callback(GLFWwindow* win, int winx, int winy);
			static void setupCallbacks(GLFWwindow* win);

			static GLFWwindow* setupGLFW(int gl_major, int gl_minor,
				int winx, int winy, const char* title, int is_fullscreen, int is_vsync);
			static void setupGLEW();

			static void checkOpenGLInfo();
			static void setupOpenGL(int winx, int winy);

			void bindCam(camera cam);

			void update();
		};
	}
}