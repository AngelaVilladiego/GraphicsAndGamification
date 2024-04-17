#include "GameController.h"
#include "WindowController.h"
#include "Fonts.h"
#include "ToolWindow.h"

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderFont = { };
	m_camera = { };
	m_meshes.clear();
}

void GameController::Initialize(string title = "Sample", bool fullscreen = true)
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(fullscreen); // Call this first as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	
	GLenum err = glGetError();

	if (err != GL_NO_ERROR)
	{
		std::cout << "initialization errors: " << err << std::endl;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand((unsigned int)time(0));

	WindowController::GetInstance().SetWindowTitle(title.c_str());

	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	OpenGLTechniques::ToolWindow^ window = gcnew OpenGLTechniques::ToolWindow();
	window->Show();

#pragma region DefineShaders
	
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

#pragma endregion DefineShaders


#pragma region MovieLights
	
	Mesh light = Mesh();
	light.Create(&m_shaderColor, "../Assets/Models/Sphere.obj");
	light.SetPosition({ 0.0f, 0.0f, 1.0f });
	light.SetColor({ 1.0f, 1.0f, 1.0f });
	light.SetScale({ 0.1f, 0.1f, 0.1f });
	Mesh::Lights.push_back(light);	

	Mesh fighter = Mesh();
	fighter.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	fighter.SetCameraPosition(m_camera.GetPosition());
	fighter.SetPosition({ 0.0f, 0.0f, 0.0f });
	fighter.SetScale({ 0.0008f, 0.0008f, 0.0008f });
	fighter.SetSpecularStrength((float)OpenGLTechniques::ToolWindow::SpecularStrength);
	fighter.SetSpecularColor({ (float)OpenGLTechniques::ToolWindow::SpecularColorR, (float)OpenGLTechniques::ToolWindow::SpecularColorG, (float)OpenGLTechniques::ToolWindow::SpecularColorB });
	m_meshes.push_back(fighter);

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 100);

#pragma endregion MovieLights

	do
	{
		System::Windows::Forms::Application::DoEvents(); // handle form events

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		for (unsigned int count = 0; count < m_meshes.size(); count++)
		{			
			m_meshes[count].SetSpecularStrength((float)OpenGLTechniques::ToolWindow::SpecularStrength);
			m_meshes[count].SetSpecularColor({ (float)OpenGLTechniques::ToolWindow::SpecularColorR, (float)OpenGLTechniques::ToolWindow::SpecularColorG, (float)OpenGLTechniques::ToolWindow::SpecularColorB });
			m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
		{
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		f.RenderText("Testing text", 10, 500, 0.5f, { 1.0f, 1.0f, 0.0f });

		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();
	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if window was closed

	for (unsigned int count = 0; count < m_meshes.size(); count++)
	{
		m_meshes[count].Cleanup();
	}

	for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
	{
		Mesh::Lights[count].Cleanup();
	}

	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
}