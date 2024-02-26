#include "GameController.h"
#include "WindowController.h"
#include "PlayerTriangle.h"

GameController::GameController()
{
	m_shader = { };
	m_camera = { };
	m_player = { };	
	m_npcs = { };
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
	m_player.Create(&m_shader, m_camera);

	for (int i = 0; i < NPC_COUNT; i++)
	{
		m_npcs.push_back(NpcTriangle());
		m_npcs[i].Create(&m_shader, m_camera);
	}

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

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

		m_player.Render();

		for (int i = 0; i < NPC_COUNT; i++)
		{
			m_npcs[i].ApplyBehaviour(m_player.GetPosition());
			m_npcs[i].Render();
		}

		glfwSwapBuffers(win); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if ESC key was pressed
		glfwWindowShouldClose(win) == 0); // Check if window was closed

	m_player.Cleanup();

	for (int i = 0; i < NPC_COUNT; i++) {
		m_npcs[i].Cleanup();
	}

	m_shader.Cleanup();
}