#include "GameController.h"
#include "WindowController.h"
//#include "ToolWindow.h"

GameController::GameController()
{
	m_shader = { };
	m_camera = { };
	m_mesh = { };
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background :(

	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	// Show the C++/CLI tool window
	/*
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	window->Show();
	*/
	

	// Create and compile our GLSL program from the shaders
	m_shader = Shader();
	m_shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	m_mesh = Mesh();
	m_mesh.Create(&m_shader);

	
	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		/*
		System::Windows::Forms::Application::DoEvents(); // Handle C++/CLI form events

		GLint loc = glGetUniformLocation(m_shader.GetProgramId(), "RenderRedChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderRedChannel);
		loc = glGetUniformLocation(m_shader.GetProgramId(), "RenderGreenChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderGreenChannel);
		loc = glGetUniformLocation(m_shader.GetProgramId(), "RenderBlueChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderBlueChannel);
		*/


		glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
		m_mesh.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(win); // Swap the front and back buffers
		glfwPollEvents();
	} 
	while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if ESC key was pressed
		glfwWindowShouldClose(win) == 0); // Check if window was closed

	m_mesh.Cleanup();
	m_shader.Cleanup();
}