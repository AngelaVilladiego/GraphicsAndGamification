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
	m_lightSpeed = 10.0f;
	m_currScene = MOVIE_LIGHT;
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

	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	m_shaderSkybox = Shader();
	m_shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");


#pragma region SpaceMeshes

	Mesh light = Mesh();
	light.Create(&m_shaderColor, "../Assets/Models/Sphere.obj");
	light.SetPosition({ 0.0f, 0.0f, 1.0f });
	light.SetColor({ 1.0f, 1.0f, 1.0f });
	light.SetScale({ 0.1f, 0.1f, 0.1f });
	Mesh::Lights.push_back(light);


	Skybox skybox = Skybox();
	skybox.Create(&m_shaderSkybox, "../Assets/Models/Skybox.obj",
		{
			"../Assets/Textures/Skybox/right.jpg",
			"../Assets/Textures/Skybox/left.jpg",
			"../Assets/Textures/Skybox/top.jpg",
			"../Assets/Textures/Skybox/bottom.jpg",
			"../Assets/Textures/Skybox/front.jpg",
			"../Assets/Textures/Skybox/back.jpg",
		});



	Mesh fighter = Mesh();
	fighter.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	fighter.SetCameraPosition(m_camera.GetPosition());
	fighter.SetPosition({ 0.0f, 0.0f, 0.0f });
	fighter.SetScale({ 0.0008f, 0.0008f, 0.0008f });
	fighter.SetRotation({ 0.0f, glm::radians(180.0f), 0.0f });
	fighter.SetSpecularStrength((float)OpenGLTechniques::ToolWindow::SpecularStrength);
	fighter.SetSpecularColor({ (float)OpenGLTechniques::ToolWindow::SpecularColorR, (float)OpenGLTechniques::ToolWindow::SpecularColorG, (float)OpenGLTechniques::ToolWindow::SpecularColorB });
	m_spaceMeshes.push_back(fighter);
#pragma endregion SpaceMeshes


	do
	{
		System::Windows::Forms::Application::DoEvents();// handle form events

		m_currScene = OpenGLTechniques::ToolWindow::SelectedSceneType;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		if (m_currScene == SPACE_SCENE)
		{
			glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
			skybox.Render(m_camera.GetProjection() * view);

			for (unsigned int count = 0; count < m_spaceMeshes.size(); count++)
			{
				m_spaceMeshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
			}
		}
		else {

			for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
			{
				Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
			}
		}

		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();
	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if window was closed

	skybox.Cleanup();

	for (unsigned int count = 0; count < m_meshes.size(); count++)
	{
		m_meshes[count].Cleanup();
	}

	for (unsigned int count = 0; count < m_spaceMeshes.size(); count++)
	{
		m_spaceMeshes[count].Cleanup();
	}

	for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
	{
		Mesh::Lights[count].Cleanup();
	}

	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderSkybox.Cleanup();
}

void GameController::ShowMovieLights() 
{

#pragma region DefineShaders

	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

#pragma endregion DefineShaders


#pragma region MovieLights

	Resolution res = WindowController::GetInstance().GetResolution();

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

#pragma region MousePos
		// get mouse position
		/*
		double mouseX;
		double mouseY;
		glfwGetCursorPos(WindowController::GetInstance().GetWindow(), &mouseX, &mouseY);

		m_mousePos.x = (float)mouseX;
		m_mousePos.y = (float)mouseY;

		float screenMouseX = m_mousePos.x / res.m_width;
		float screenMouseY = m_mousePos.y / res.m_height;

		glm::mat4 inversePV = inverse(m_camera.GetProjection() * m_camera.GetView());
		glm::vec4 clipFar = inversePV * glm::vec4({ screenMouseX, screenMouseY, 1, 1 });
		glm::vec4 clipNear = inversePV * glm::vec4({ screenMouseX, screenMouseY, 0, 1 });
		glm::vec3 ray = glm::normalize(glm::vec3({ clipFar.x - clipNear.x, clipFar.y - clipNear.y, clipFar.z - clipNear.z }));
		std::string mouseText = "Mouse Position: " + std::to_string(mouseX) + "   " + std::to_string(mouseY);


		glm::vec3 lightPosition = m_camera.GetPosition() - ray;
		*/

		double mouseX;
		double mouseY;
		glfwGetCursorPos(WindowController::GetInstance().GetWindow(), &mouseX, &mouseY);

		m_mousePos.x = (float)mouseX;
		m_mousePos.y = (float)mouseY;
		float centerX = res.m_width / 2.0f;
		float centerY = res.m_height / 2.0f;

		glm::vec3 dir = glm::normalize(glm::vec3({ m_mousePos.x - centerX, m_mousePos.y - centerY, 0 }));
		std::string mouseText = "Mouse Position: " + std::to_string(mouseX) + "   " + std::to_string(mouseY);


#pragma endregion MousePos

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		for (unsigned int count = 0; count < m_meshes.size(); count++)
		{
			m_meshes[count].SetSpecularStrength((float)OpenGLTechniques::ToolWindow::SpecularStrength);
			m_meshes[count].SetSpecularColor({ (float)OpenGLTechniques::ToolWindow::SpecularColorR, (float)OpenGLTechniques::ToolWindow::SpecularColorG, (float)OpenGLTechniques::ToolWindow::SpecularColorB });
			m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
		{
			Mesh::Lights[count].SetPosition(Mesh::Lights[count].GetPosition() + (dir * m_lightSpeed));
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		f.RenderText(mouseText, 10, 500, 0.5f, { 1.0f, 1.0f, 0.0f });

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