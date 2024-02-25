#include "WindowController.h"

WindowController::WindowController()
{
	m_window = nullptr;
}

WindowController::~WindowController()
{
	if (m_window != nullptr)
	{
		glfwTerminate();
		m_window = nullptr;
	}
}

Resolution WindowController::GetResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	return Resolution(mode->width, mode->height);
}

void WindowController::NewWindow()
{
	M_ASSERT(glfwInit(), "Failed to initialize GLFW."); // Initialise GLFW

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	// Open a window and create its OpenGL context
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	M_ASSERT((m_window = glfwCreateWindow(mode->width, mode->height, "Sample scene", monitor, NULL)) != nullptr, "Failed to open GLFW window.");
	glfwMakeContextCurrent(m_window);
}

void WindowController::SetWindowFullscreen()
{
	Resolution res = GetResolution();
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	glfwSetWindowSize(m_window, res.m_width, res.m_height);
}

void WindowController::SetWindowTitle(string title)
{
	glfwSetWindowTitle(m_window, title.c_str());
}