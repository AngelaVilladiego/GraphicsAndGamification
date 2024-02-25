#include "GameController.h"
#include "WindowController.h"
#include "PlayerTriangle.h"
//#include "ToolWindow.h"

GameController::GameController()
{
	m_shader = { };
	m_camera = { };
	m_mesh = { };
}

void GameController::Initialize(string title = "Sample")
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background
	glEnable(GL_CULL_FACE);

	WindowController::GetInstance().SetWindowTitle(title.c_str());

	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	// Create and compile our GLSL program from the shaders
	m_shader = Shader();
	m_shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	m_mesh = Mesh();
	m_mesh.Create(&m_shader, PlayerTriangle::GetInstance().GetVertexData());

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
		m_mesh.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(win); // Swap the front and back buffers
		glfwPollEvents();
	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if ESC key was pressed
		glfwWindowShouldClose(win) == 0); // Check if window was closed

	m_mesh.Cleanup();
	m_shader.Cleanup();
}