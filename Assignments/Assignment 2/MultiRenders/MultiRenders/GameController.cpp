#include "GameController.h"
#include "WindowController.h"
#include "Fonts.h"
#include "ToolWindow.h"
#include "FPSCounter.h"

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderFont = { };
	m_camera = { };
	m_mousePos = { };
	m_meshes.clear();
	m_lightSpeed = 10.0f;
	m_currScene = MOVE_LIGHT;
}

void GameController::Initialize(string title = "Sample", bool fullscreen = true)
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(fullscreen); // Call this first as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // Gray background
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand((unsigned int)time(0));

	WindowController::GetInstance().SetWindowTitle(title.c_str());

	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	MultiRenders::ToolWindow^ window = gcnew MultiRenders::ToolWindow();
	window->Show();

	FPSCounter fpsCounter = FPSCounter();

	do
	{
		System::Windows::Forms::Application::DoEvents();// handle form events



		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();
	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if window was closed

}