#include "window.h"

#include <iostream>



namespace cgj {
	namespace graphics {

		window::window(int major, int minor,
			int winx, int winy, const char* title, int is_fullscreen, int is_vsync) {
			Window = window::setup(major, minor, winx, winy, title, is_fullscreen, is_vsync);
		}

		GLFWwindow* window::setup(int major, int minor,
			int winx, int winy, const char* title, int is_fullscreen, int is_vsync) {
			Window =
				window::setupGLFW(major, minor, winx, winy, title, is_fullscreen, is_vsync);
			window::setupGLEW();
			window::setupOpenGL(winx, winy);
			return Window;
		}

		GLFWwindow* window::setupWindow(int winx, int winy, const char* title,
			int is_fullscreen, int is_vsync)
		{
			GLFWmonitor* monitor = is_fullscreen ? glfwGetPrimaryMonitor() : 0;
			GLFWwindow* win = glfwCreateWindow(winx, winy, title, monitor, 0);
			if (!win)
			{
				glfwTerminate();
				exit(EXIT_FAILURE);
			}
			glfwMakeContextCurrent(win);
			glfwSwapInterval(is_vsync);
			return win;
		}

		GLFWwindow* window::setupGLFW(int gl_major, int gl_minor,
			int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
		{
			glfwSetErrorCallback(glfw_error_callback);
			if (!glfwInit())
			{
				exit(EXIT_FAILURE);
			}
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

			GLFWwindow* win = window::setupWindow(winx, winy, title, is_fullscreen, is_vsync);
			window::setupCallbacks(win);

#if _DEBUG
			std::cout << "GLFW " << glfwGetVersionString() << std::endl;
#endif
			return win;
		}

		void window::setupGLEW()
		{
			glewExperimental = GL_TRUE;
			// Allow extension entry points to be loaded even if the extension isn't 
			// present in the driver's extensions string.
			GLenum result = glewInit();
			if (result != GLEW_OK)
			{
				std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
				exit(EXIT_FAILURE);
			}
			GLenum err_code = glGetError();
			// You might get GL_INVALID_ENUM when loading GLEW.
		}
		 
		void bindCam(camera cam) {
			cam = cam;
		}
		
		void window::setupCallbacks(GLFWwindow* win) {
			glfwSetWindowSizeCallback(win, window_size_callback);
		}

		void window_size_callback(GLFWwindow* win, int winx, int winy) {
			glViewport(0, 0, winx, winy);
		}

		void glfw_error_callback(int error, const char* description)
		{
			std::cerr << "GLFW Error: " << description << std::endl;
		}


		void window::checkOpenGLInfo()
		{
			const GLubyte* renderer = glGetString(GL_RENDERER);
			const GLubyte* vendor = glGetString(GL_VENDOR);
			const GLubyte* version = glGetString(GL_VERSION);
			const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
			std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
			std::cerr << "OpenGL version " << version << std::endl;
			std::cerr << "GLSL version " << glslVersion << std::endl;
		}

		void window::setupOpenGL(int winx, int winy)
		{
#if _DEBUG
			window::checkOpenGLInfo();
#endif
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glDepthMask(GL_TRUE);
			glDepthRange(0.0, 1.0);
			glClearDepth(1.0);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
			glViewport(0, 0, winx, winy);
		}


		auto getCurrentTime() {
			auto time = std::chrono::system_clock::now();
			return time;
		}


		void window::update() {
			std::chrono::time_point<std::chrono::system_clock> currentFrameTime = getCurrentTime();
			delta = (currentFrameTime - lastFrameTime) / 1000.0f;
			lastFrameTime = currentFrameTime;
		}


	}
}