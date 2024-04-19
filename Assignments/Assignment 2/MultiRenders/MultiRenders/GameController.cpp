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
	m_meshes.clear();
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand((unsigned int)time(0));

	WindowController::GetInstance().SetWindowTitle(title.c_str());

	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	// variables
	GLFWwindow* win = WindowController::GetInstance().GetWindow();

	FPSCounter fpsCounter = FPSCounter();
	string fpsString = "FPS: 0";

	Resolution res = WindowController::GetInstance().GetResolution();
	glm::vec3 centerVec = { res.m_width / 2.0f, res.m_height / 2.0f, 0 };
	double mouseX = 0.0;
	double mouseY = 0.0;
	float maxSpeed = 0.05f;
	string mousePosString = "Mouse Pos: ";

	//convert resolution to vectors with 0 at center and positive y up 
	quadTopLeft ={ -centerVec.x, centerVec.y, 0 };
	quadTopRight = { centerVec.x, centerVec.y, 0 };
	quadBottomLeft = { -centerVec.x, -centerVec.y, 0 };
	quadBottomRight = { centerVec.x, -centerVec.y, 0 };

	glm::mat4 pv = m_camera.GetProjection() * m_camera.GetView();
	


	// Loading shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");



	// Creating Meshes
	Mesh light = Mesh();
	light.Create(&m_shaderColor, "../Assets/Models/Sphere.obj");
	light.SetPosition({ 0.0f, 0.0f, 1.0f });
	light.SetColor({ 1.0f, 1.0f, 1.0f });
	light.SetScale({ 0.2f, 0.2f, 0.2f });
	Mesh::Lights.push_back(light);

	Fonts fpsFont = Fonts();
	fpsFont.Create(&m_shaderFont, "arial.ttf", 100);
	Fonts mousePosFont = Fonts();
	mousePosFont.Create(&m_shaderFont, "arial.ttf", 100);



	MultiRenders::ToolWindow^ window = gcnew MultiRenders::ToolWindow();
	window->Show();

	do
	{
		System::Windows::Forms::Application::DoEvents();// handle form events

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		//Updating values
		fpsCounter.Tick();
		fpsString = "FPS: " + to_string(fpsCounter.GetFPS());

		glfwGetCursorPos(WindowController::GetInstance().GetWindow(), &mouseX, &mouseY);
		mousePosString = "Mouse Pos: " + to_string(mouseX) + " " + to_string(mouseY);
		
		if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			glm::vec3 mouseVec = { (float)mouseX, (float)mouseY, 0 };
			Mesh::Lights[0].SetPosition(CalculatePosition(mouseVec, centerVec, Mesh::Lights[0].GetPosition(), maxSpeed));
		}



		//Rendering
		for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
		{
			Mesh::Lights[count].Render(pv);
		}

		fpsFont.RenderText(fpsString, 50, 50, 0.25f, {1.0f, 1.0f, 0.0f});
		mousePosFont.RenderText(mousePosString, 50, 100, 0.25f, { 1.0f, 1.0f, 0.0f });



		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if window was closed

	// Cleanup

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