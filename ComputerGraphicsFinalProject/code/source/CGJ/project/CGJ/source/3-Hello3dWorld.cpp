///////////////////////////////////////////////////////////////////////////////
//
//					SKYBOX AND START OF WATER
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "maths/matrix.h"
#include "maths/quaternions.h"
#include "graphics/shader.h"
#include "graphics/camera.h"
#include "graphics/window.h"
#include "meshLoader/mesh.h"

#include <string>

#include "scene.h"

using namespace cgj;

#define VERTICES 0
#define COLORS 1

GLuint VaoId, VboId[1];
GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UboId, UniformId;
const GLuint UBO_BP = 0;


GLint ModelMatrix_UId, ViewMatrix_UId, ProjectionMatrix_UId;
graphics::shader shader = graphics::shader();

int gl_major = 4, gl_minor = 3;
int is_fullscreen = 0;
int is_vsync = 1;
float win_rx = 1280.0f;
float win_ry = 720.0f;

graphics::window window = graphics::window(gl_major, gl_minor,
	win_rx, win_ry, "Hello Modern 3D World", is_fullscreen, is_vsync);


bool is_ortho = true;
bool quaternion = true;

std::vector<mesh> mesh_list;


scenegraph* graph = new scenegraph();
////////////////////////////////////////////////// ERROR CALLBACK (OpenGL 4.3+)

static const std::string errorSource(GLenum source)
{
	switch (source) {
	case GL_DEBUG_SOURCE_API:				return "API";
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		return "window system";
	case GL_DEBUG_SOURCE_SHADER_COMPILER:	return "shader compiler";
	case GL_DEBUG_SOURCE_THIRD_PARTY:		return "third party";
	case GL_DEBUG_SOURCE_APPLICATION:		return "application";
	case GL_DEBUG_SOURCE_OTHER:				return "other";
	default:								exit(EXIT_FAILURE);
	}
}

static const std::string errorType(GLenum type)
{
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:				return "error";
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:	return "deprecated behavior";
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:	return "undefined behavior";
	case GL_DEBUG_TYPE_PORTABILITY:			return "portability issue";
	case GL_DEBUG_TYPE_PERFORMANCE:			return "performance issue";
	case GL_DEBUG_TYPE_MARKER:				return "stream annotation";
	case GL_DEBUG_TYPE_PUSH_GROUP:			return "push group";
	case GL_DEBUG_TYPE_POP_GROUP:			return "pop group";
	case GL_DEBUG_TYPE_OTHER_ARB:			return "other";
	default:								exit(EXIT_FAILURE);
	}
}

static const std::string errorSeverity(GLenum severity)
{
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:			return "high";
	case GL_DEBUG_SEVERITY_MEDIUM:			return "medium";
	case GL_DEBUG_SEVERITY_LOW:				return "low";
	case GL_DEBUG_SEVERITY_NOTIFICATION:	return "notification";
	default:								exit(EXIT_FAILURE);
	}
}

static void error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	std::cerr << "GL ERROR:" << std::endl;
	std::cerr << "  source:     " << errorSource(source) << std::endl;
	std::cerr << "  type:       " << errorType(type) << std::endl;
	std::cerr << "  severity:   " << errorSeverity(severity) << std::endl;
	std::cerr << "  debug call: " << std::endl << message << std::endl << std::endl;
}

void setupErrorCallback()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(error, 0);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
	// params: source, type, severity, count, ids, enabled
}


///////////////////////////////////////////////////////////////////////// SETUP

void glfw_error_callback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}


void destroyShaderProgram()
{
	glUseProgram(0);
	glDeleteProgram(graph->get_shader()->shader_id);
}

void window_close_callback(GLFWwindow* win) {
	destroyShaderProgram();
	graph->destroyScene();
}

void setWindowCloseCallback(GLFWwindow* win) {
	glfwSetWindowCloseCallback(win, window_close_callback);
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	switch (action) {
	case GLFW_PRESS:
		scene::KeyPressed(key, graph);
		break;
	case GLFW_RELEASE:
		scene::KeyReleased(key, graph);
		break;
	default:
		break;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	switch (action) {
	case GLFW_PRESS:
		scene::KeyPressed(button, graph);
		break;
	case GLFW_RELEASE:
		scene::KeyReleased(button, graph);
		break;
	default:
		break;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	graph->set_zoom(yoffset);
	graph->get_camera()->zoom(graph->get_zoom());
	graph->get_reflect_camera()->zoom(graph->get_zoom());
}

vec2 oldMousePos;
vec2 newMousePos;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{	
	newMousePos = vec2((float)xpos, (float)ypos);
	if (oldMousePos != NULL) {
		if (graph->scene_key_map[GLFW_MOUSE_BUTTON_RIGHT]) {
			graph->set_oldMousePos(oldMousePos);
			graph->set_newMousePos(newMousePos);
		}

	}
	oldMousePos = newMousePos;
}


void prepareWindow() {
	scene::createSceneGraph(graph, win_rx, win_ry);
	scene::createWaterSceneGraph(graph);
	scene::createSkyboxSceneGraph(graph);
	scene::createIslandSceneGraph(graph);

	glfwSetMouseButtonCallback(window.Window, mouse_button_callback);
	glfwSetKeyCallback(window.Window, key_callback);
	glfwSetCursorPosCallback(window.Window, cursor_position_callback);
	glfwSetScrollCallback(window.Window, scroll_callback);
	setWindowCloseCallback(window.Window);
}


////////////////////////////////////////////////////////////////////////// RUN

void display(GLFWwindow* win, double elapsed_sec)
{	
	window.update();
	scene::update(graph, window.delta.count());
	graph->draw();
}

void run(GLFWwindow* win)
{
	double last_time = glfwGetTime();
	while (!glfwWindowShouldClose(win))
	{
		double time = glfwGetTime();
		double elapsed_time = time - last_time;
		last_time = time;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display(win, elapsed_time);
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	glfwDestroyWindow(win);
	glfwTerminate();
}

////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[])
{

	prepareWindow();
	run(window.Window);
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////////////
