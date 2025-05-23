#include "GameController.h"
#include "WindowController.h"
#include "Fonts.h"
#include "ToolWindow.h"
#include "FPSCounter.h"
#include <random>

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderPositionColor = { };
	m_shaderFont = { };

	m_camera = { };
	m_cubes.clear();
	m_lightSpeed = 10.0f;
	m_currScene = MOVE_LIGHT;

	quadTopLeft = { 0, 0, 0 };
	quadTopRight = { 0, 0, 0 };
	quadBottomLeft = { 0, 0, 0 };
	quadBottomRight = { 0, 0, 0 };
}

void GameController::Initialize(string title = "Sample", bool fullscreen = true)
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(fullscreen); // Call this first as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW

	glfwSetInputMode(window, GLFW_STICKY_KEYS | GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // Gray background
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand((unsigned int)time(0));

	WindowController::GetInstance().SetWindowTitle(title.c_str());

	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
#pragma region Declaring variables
	GLFWwindow* win = WindowController::GetInstance().GetWindow();

	FPSCounter fpsCounter = FPSCounter();
	string fpsString = "FPS: 0";

	Resolution res = WindowController::GetInstance().GetResolution();
	glm::vec3 centerVec = { res.m_width / 2.0f, res.m_height / 2.0f, 0 };
	double mouseX = 0.0;
	double mouseY = 0.0;
	float maxSpeed = 0.003f;
	string mousePosString = "Mouse Pos: ";

	//convert resolution to vectors with 0 at center and positive y up 
	quadTopLeft ={ -centerVec.x, centerVec.y, 0 };
	quadTopRight = { centerVec.x, centerVec.y, 0 };
	quadBottomLeft = { -centerVec.x, -centerVec.y, 0 };
	quadBottomRight = { centerVec.x, -centerVec.y, 0 };

	float cubeSpeed = 0.0002f;
	float touchRadius = 0.001f;
	vector<Mesh>::iterator cubeIt;

	glm::mat4 pv = m_camera.GetProjection() * m_camera.GetView();
#pragma endregion 



#pragma region Loading shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	m_shaderPositionColor = Shader();
	m_shaderPositionColor.LoadShaders("PositionColor.vertexshader", "PositionColor.fragmentshader");
#pragma endregion



#pragma region Creating meshes
	Mesh light = Mesh();
	light.Create(&m_shaderColor, "../Assets/Models/Sphere.obj");
	light.SetPosition({ 0.0f, 0.0f, 0.1f });
	light.SetColor({ 1.0f, 1.0f, 1.0f });
	light.SetScale({ 0.005f, 0.005f, 0.005f });
	Mesh::Lights.push_back(light);

	Mesh teapot = Mesh();
	teapot.Create(&m_shaderDiffuse, "../Assets/Models/Teapot.obj");
	teapot.SetPosition({ 0.0f, 0.0f, 0.0f });
	teapot.SetScale({ 0.0035f, 0.0035f, 0.0035f });
	teapot.SetCameraPosition(m_camera.GetPosition());
	teapot.SetSpecularStrength(4.0f);
	teapot.SetSpecularColor({ 1.0f, 1.0f, 1.0f });

	Mesh sphere = Mesh();
	sphere.Create(&m_shaderDiffuse, "../Assets/Models/Sphere.obj");
	sphere.SetPosition({ 0.0f, 0.0f, 0.0f });
	sphere.SetScale({ 0.02f, 0.02f, 0.02f });
	sphere.SetCameraPosition(m_camera.GetPosition());
	sphere.SetSpecularStrength(2.0f);
	sphere.SetSpecularColor({ 0.5f, 0.5f, 0.5f });

	Fonts fpsFont = Fonts();
	fpsFont.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts mousePosFont = Fonts();
	mousePosFont.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts cubesFont = Fonts();
	cubesFont.Create(&m_shaderFont, "arial.ttf", 100);
#pragma endregion



	MultiRenders::ToolWindow^ window = gcnew MultiRenders::ToolWindow();
	window->Show();

	do
	{
		System::Windows::Forms::Application::DoEvents();// handle form events

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



#pragma region Updating values
		m_currScene = MultiRenders::ToolWindow::SelectedSceneType;

		fpsCounter.Tick();
		fpsString = "FPS: " + to_string(fpsCounter.GetFPS());

		glfwGetCursorPos(WindowController::GetInstance().GetWindow(), &mouseX, &mouseY);
		mousePosString = "Mouse Pos: " + to_string(mouseX) + " " + to_string(mouseY);

		if (MultiRenders::ToolWindow::ResetLightPosition)
		{
			Mesh::Lights[0].SetPosition({ 0.0f, 0.0f, 0.1f });
			MultiRenders::ToolWindow::ResetLightPosition = false;
		}
		
		if (MultiRenders::ToolWindow::ResetTeapotPosition)
		{
			teapot.SetPosition({ 0.0f, 0.0f, 0.0f });
			MultiRenders::ToolWindow::ResetTeapotPosition = false;
		}

		if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			glm::vec3 mouseVec = { (float)mouseX, (float)mouseY, 0 };

			if (m_currScene == MOVE_LIGHT)
			{
				Mesh::Lights[0].SetPosition(CalculatePosition(mouseVec, centerVec, Mesh::Lights[0].GetPosition(), maxSpeed));
			}

			if (m_currScene == COLOR)
			{
				teapot.SetPosition(CalculatePosition(mouseVec, centerVec, teapot.GetPosition(), maxSpeed));
			}

			if (m_currScene == CUBES)
			{
				AddCube();
			}
		}

		teapot.SetSpecularStrength((float)MultiRenders::ToolWindow::SpecularStrength);
		teapot.SetSpecularColor({ MultiRenders::ToolWindow::SpecularColorR, MultiRenders::ToolWindow::SpecularColorG, MultiRenders::ToolWindow::SpecularColorB });
#pragma endregion



#pragma region Rendering

		switch (m_currScene) {
		case MOVE_LIGHT:
			teapot.SetShader(&m_shaderDiffuse);
			teapot.Render(pv);

			for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
			{
				Mesh::Lights[count].Render(pv);
			}

			break;

		case COLOR:
			teapot.SetShader(&m_shaderPositionColor);
			teapot.Render(pv);

			break;

		case CUBES:
			sphere.Render(pv);

			for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
			{
				Mesh::Lights[count].Render(pv);
			}

			for (cubeIt = m_cubes.begin(); cubeIt != m_cubes.end();)
			{
				cubeIt->SetPosition(MoveToCenter(cubeIt->GetPosition(), cubeSpeed));
				cubeIt->Render(pv);


				if (glm::distance(cubeIt->GetPosition(), glm::vec3({ 0, 0, 0 })) <= touchRadius)
				{
					cubeIt->Cleanup();
					cubeIt = m_cubes.erase(cubeIt);
				}
				else
				{
					++cubeIt;
				}
			}

			cubesFont.RenderText("Cubes: " + to_string(m_cubes.size()), 50, 150, 0.25, { 1.0f, 1.0f, 0.0f });

			break;

		default:
			MultiRenders::ToolWindow::SelectedSceneType = MOVE_LIGHT;
		}



		fpsFont.RenderText(fpsString, 50, 50, 0.25f, {1.0f, 1.0f, 0.0f});
		mousePosFont.RenderText(mousePosString, 50, 100, 0.25f, { 1.0f, 1.0f, 0.0f });
#pragma endregion


		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if window was closed



#pragma region Cleanup
	m_shaderColor.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderFont.Cleanup();
	m_shaderPositionColor.Cleanup();

	for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
	{
		Mesh::Lights[count].Cleanup();
	}
	for (unsigned int count = 0; count < m_cubes.size(); count++)
	{
		m_cubes[count].Cleanup();
	}
	teapot.Cleanup();

	fpsFont.Cleanup();
	mousePosFont.Cleanup();
	cubesFont.Cleanup();
#pragma endregion



}


glm::vec3 GameController::CalculatePosition(glm::vec3 mousePos, glm::vec3 centerPos, glm::vec3 currPos, float maxSpeed)
{

	// identify which quadrant the mouse was clicked in	
	glm::vec3 clickedQuadrant = quadTopLeft;

	if (mousePos.x >= centerPos.x)
	{
		if (mousePos.y >= centerPos.y)
		{
			clickedQuadrant = quadBottomRight;
		}
		else
		{
			clickedQuadrant = quadTopRight;
		}
	}
	else if (mousePos.y >= centerPos.y)
	{
		clickedQuadrant = quadBottomLeft;
	}

	// get distance into quadrant relative from center, clamped to be a maximum of the distance from center to corner
	float maxDistance = glm::length(clickedQuadrant);
	float distance = min(glm::distance(mousePos, centerPos), maxDistance);
	
	// calculate speed based off of depth of click into quadrant
	float speed = (distance / maxDistance) * maxSpeed;

	// calculate new position this frame based off speed, quadrant, and current position
	glm::vec3 direction = glm::normalize(clickedQuadrant);
	glm::vec3 newPosition = currPos + (direction * speed);

	return newPosition;	
}

glm::vec3 GameController::MoveToCenter(glm::vec3 currPos, float speed)
{
	glm::vec3 direction = glm::normalize(glm::vec3({ 0, 0, 0 }) - currPos);
	glm::vec3 newPosition = currPos + (direction * speed);
	
	return newPosition;
}

void GameController::AddCube()
{
	glm::vec3 min = { -0.2f, -0.1f, -0.5f };
	glm::vec3 max = { 0.2f, 0.1f, 0.2f };

	float x = RandomFloat(min.x, max.x);
	float y = RandomFloat(min.y, max.y);
	float z = RandomFloat(min.z, max.z);

	Mesh cube = Mesh();
	cube.Create(&m_shaderDiffuse, "../Assets/Models/Box.obj");
	cube.SetPosition({ x, y, z });
	cube.SetScale({ 0.001f, 0.001f, 0.001f });
	cube.SetCameraPosition(m_camera.GetPosition());
	cube.SetSpecularStrength(32.0f);
	cube.SetSpecularColor({ 1.0f, 1.0f, 1.0f });
	m_cubes.push_back(cube);
}

float GameController::RandomFloat(float min, float max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}