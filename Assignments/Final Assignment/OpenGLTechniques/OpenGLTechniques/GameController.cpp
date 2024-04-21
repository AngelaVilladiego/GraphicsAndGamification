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

	m_leftClickHandler = GestureManager(GLFW_MOUSE_BUTTON_LEFT);
	m_middleClickHandler = GestureManager(GLFW_MOUSE_BUTTON_MIDDLE);

	FPSCounter fpsCounter = FPSCounter();
	string fpsString = "FPS: 0";

	Resolution res = WindowController::GetInstance().GetResolution();
	glm::vec3 centerVec = { res.m_width / 2.0f, res.m_height / 2.0f, 0 };
	double mouseX = 0.0;
	double mouseY = 0.0;
	float maxSpeed = 0.003f;
	string mousePosString = "Mouse Pos: ";
	string leftBtnString = "Up";
	string middleBtnString = "Up";

	//convert resolution to vectors with 0 at center and positive y up 
	quadTopLeft = { -centerVec.x, centerVec.y, 0 };
	quadTopRight = { centerVec.x, centerVec.y, 0 };
	quadBottomLeft = { -centerVec.x, -centerVec.y, 0 };
	quadBottomRight = { centerVec.x, -centerVec.y, 0 };

	glm::mat4 pv = m_camera.GetProjection() * m_camera.GetView();
#pragma endregion 



#pragma region Loading shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

#pragma endregion



#pragma region Creating meshes
	Mesh light = Mesh();
	light.Create(&m_shaderColor, "../Assets/Models/Sphere.obj");
	light.SetPosition({ 0.0f, 0.0f, 0.1f });
	light.SetColor({ 1.0f, 1.0f, 1.0f });
	light.SetScale({ 0.005f, 0.005f, 0.005f });
	Mesh::Lights.push_back(light);

	Mesh fighter = Mesh();
	fighter.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	fighter.SetPosition({ 0.0f, 0.0f, 0.0f });
	fighter.SetScale({ 0.00008f, 0.00008f, 0.00008f });
	fighter.SetCameraPosition(m_camera.GetPosition());
	fighter.SetSpecularStrength(4.0f);
	fighter.SetSpecularColor({ 1.0f, 1.0f, 1.0f });

	Mesh fighterTransform = Mesh();
	fighterTransform.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	fighterTransform.SetPosition({ 0.0f, 0.0f, 0.0f });
	fighterTransform.SetScale({ 0.00008f, 0.00008f, 0.00008f });
	fighterTransform.SetCameraPosition(m_camera.GetPosition());
	fighterTransform.SetSpecularStrength(4.0f);
	fighterTransform.SetSpecularColor({ 1.0f, 1.0f, 1.0f });
	fighter.SetRotation({ 0.1f, 0.0f, 0.0f });


	Fonts fpsFont = Fonts();
	fpsFont.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts mousePosFont = Fonts();
	mousePosFont.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts leftBtnFont = Fonts();
	leftBtnFont.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts middleBtnFont = Fonts();
	middleBtnFont.Create(&m_shaderFont, "arial.ttf", 100);

#pragma endregion

	OpenGLTechniques::ToolWindow^ window = gcnew OpenGLTechniques::ToolWindow();
	window->Show();

	do
	{
		System::Windows::Forms::Application::DoEvents();// handle form events

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



#pragma region Updating values
		m_currScene = OpenGLTechniques::ToolWindow::SelectedSceneType;

		fpsCounter.Tick();
		fpsString = "FPS: " + to_string(fpsCounter.GetFPS());

		glfwGetCursorPos(WindowController::GetInstance().GetWindow(), &mouseX, &mouseY);
		mousePosString = "Mouse Pos: " + to_string(mouseX) + " " + to_string(mouseY);

		m_leftClickHandler.Tick();
		m_middleClickHandler.Tick();

		if (m_leftClickHandler.IsInProgress())
		{
			leftBtnString = "Down";
		}
		else
		{
			leftBtnString = "Up";
		}

		if (m_middleClickHandler.IsInProgress())
		{
			middleBtnString = "Down";
		}
		else
		{
			middleBtnString = "Up";
		}

		if (OpenGLTechniques::ToolWindow::ResetLightPosition)
		{
			Mesh::Lights[0].SetPosition({ 0.0f, 0.0f, 0.1f });
			OpenGLTechniques::ToolWindow::ResetLightPosition = false;
		}

		if (OpenGLTechniques::ToolWindow::ResetTransform)
		{
			//TODO RESET TRANSFORM
			OpenGLTechniques::ToolWindow::ResetTransform = false;
		}

		if (m_currScene == MOVE_LIGHT && glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			glm::vec3 mouseVec = { (float)mouseX, (float)mouseY, 0 };
			Mesh::Lights[0].SetPosition(CalculateQuadrantPosition(mouseVec, centerVec, Mesh::Lights[0].GetPosition(), maxSpeed));
		}

		if (m_currScene == TRANSFORM)
		{
			HandleTransform();
		}

		fighter.SetSpecularStrength((float)OpenGLTechniques::ToolWindow::SpecularStrength);
		fighter.SetSpecularColor({ OpenGLTechniques::ToolWindow::SpecularColorR, OpenGLTechniques::ToolWindow::SpecularColorG, OpenGLTechniques::ToolWindow::SpecularColorB });
#pragma endregion



#pragma region Rendering

		switch (m_currScene) {
		case MOVE_LIGHT:
			fighter.SetRotation(glm::vec3({ fighter.GetRotation().x + 0.001f, 0.0f, 0.0f }));
			fighter.Render(pv);
			for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
			{
				Mesh::Lights[count].Render(pv);
			}
			break;
		case TRANSFORM:

			break;

		case WATER_SCENE:
			break;
		
		case SPACE_SCENE:
			break;

		default:
			OpenGLTechniques::ToolWindow::SelectedSceneType = MOVE_LIGHT;
		}

		fpsFont.RenderText(fpsString, 50, 50, 0.2f, { 1.0f, 1.0f, 0.0f });
		mousePosFont.RenderText(mousePosString, 50, 70, 0.2f, { 1.0f, 1.0f, 0.0f });
		leftBtnFont.RenderText("Left Button: " + leftBtnString, 50, 90, 0.2f, {1.0f, 1.0f, 0.0f});
		middleBtnFont.RenderText("Middle Button: " + middleBtnString, 50, 110, 0.2f, {1.0f, 1.0f, 0.0f});
#pragma endregion


		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if window was closed



#pragma region Cleanup
	m_shaderColor.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderFont.Cleanup();

	fighter.Cleanup();
	fighterTransform.Cleanup();
	for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
	{
		Mesh::Lights[count].Cleanup();
	}

	fpsFont.Cleanup();
	mousePosFont.Cleanup();
	leftBtnFont.Cleanup();
	middleBtnFont.Cleanup();
#pragma endregion

}

void GameController::HandleTransform()
{	
}

glm::vec3 GameController::CalculateQuadrantPosition(glm::vec3 mousePos, glm::vec3 centerPos, glm::vec3 currPos, float maxSpeed)
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

float GameController::RandomFloat(float min, float max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}