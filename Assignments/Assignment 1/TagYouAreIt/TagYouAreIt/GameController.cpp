#include "GameController.h"
#include "WindowController.h"
#include "PlayerTriangle.h"

GameController::GameController()
{
	m_shader = { };
	m_camera = { };
	m_player = { };	
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

	m_player = PlayerTriangle();
	m_player.Create(&m_shader);

	for (int i = 0; i < m_npcs.size(); i++)
	{
		m_npcs[i] = NpcTriangle();
		m_npcs[i].Create(&m_shader);
	}

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		glm::vec3 playerDir = { 0, 0, 0 };

		//check button presses
		if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
			playerDir += UP_VEC;
		}
		if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
			playerDir += LEFT_VEC;
		}
		if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
			playerDir += DOWN_VEC;
		}
		if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
			playerDir += RIGHT_VEC;
		}

		if (glfwGetKey(win, GLFW_KEY_ENTER) == GLFW_PRESS) {
			m_player.SetColor({ 0, 0, 1, 1 });
		}

		

		if (glm::length(playerDir) != 0)
		{
			playerDir = glm::normalize(playerDir);
			m_player.Translate(playerDir);
		}		

		glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
		m_player.Render(m_camera.GetProjection() * m_camera.GetView());

		/*
		for (int i = 0; i < m_npcs.size(); i++)
		{
			m_npcs[i].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		*/

		glfwSwapBuffers(win); // Swap the front and back buffers
		glfwPollEvents();
	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if ESC key was pressed
		glfwWindowShouldClose(win) == 0); // Check if window was closed

	m_player.Cleanup();

	for (int i = 0; i < m_npcs.size(); i++) {
		m_npcs[i].Cleanup();
	}

	m_shader.Cleanup();
}