#include "GameController.h"
#include "WindowController.h"
#include "Fonts.h"
#include "ToolWindow.h"
#include "FPSCounter.h"
#include "Vec3ToString.h"
#include <random>

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderFont = { };
	m_shaderPost = { };

	m_camera = { };
	m_lightSpeed = 10.0f;
	m_currScene = MOVE_LIGHT;

	m_centerVec = { };

	quadTopLeft = { 0, 0, 0 };
	quadTopRight = { 0, 0, 0 };
	quadBottomLeft = { 0, 0, 0 };
	quadBottomRight = { 0, 0, 0 };

	fighterTranslation = { 0, 0, 0 };
	fighterRotation = { 0, 0, 0 };
	fighterScale = { 0, 0, 0 };

	m_time = 0.0f;
}

void GameController::Initialize(string title = "Sample", bool fullscreen = true)
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(fullscreen); // Call this first as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW

	glfwSetInputMode(window, GLFW_STICKY_KEYS | GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand((unsigned int)time(0));

	WindowController::GetInstance().SetWindowTitle(title.c_str());

	// Create a default perspective camera
	Resolution r = WindowController::GetInstance().GetResolution();
	glViewport(0, 0, r.m_width, r.m_height);
	m_camera = Camera(r);
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
	m_centerVec = { res.m_width / 2.0f, res.m_height / 2.0f, 0 };
	double mouseX = 0.0;
	double mouseY = 0.0;
	float maxSpeed = 0.003f;
	string mousePosString = "Mouse Pos: ";
	string leftBtnString = "Up";
	string middleBtnString = "Up";

	//convert resolution to vectors with 0 at center and positive y up 
	quadTopLeft = { -m_centerVec.x, m_centerVec.y, 0 };
	quadTopRight = { m_centerVec.x, m_centerVec.y, 0 };
	quadBottomLeft = { -m_centerVec.x, -m_centerVec.y, 0 };
	quadBottomRight = { m_centerVec.x, -m_centerVec.y, 0 };

	glm::mat4 pv = m_camera.GetProjection() * m_camera.GetView();
#pragma endregion 



#pragma region Loading shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	m_shaderPost = Shader();
	m_shaderPost.LoadShaders("PostProcess.vertexshader", "PostProcess.fragmentshader");
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

	Mesh* currFighter = &fighter;

	Mesh fighterTransform = Mesh();
	fighterTransform.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	fighterTransform.SetPosition({ 0.0f, 0.0f, 0.0f });
	fighterTransform.SetScale({ 0.00008f, 0.00008f, 0.00008f });
	fighterTransform.SetRotation({ 1.0f, 0.0f, 0.0f });
	fighterTransform.SetCameraPosition(m_camera.GetPosition());
	fighterTransform.SetSpecularStrength(4.0f);
	fighterTransform.SetSpecularColor({ 1.0f, 1.0f, 1.0f });

	fighterTranslation = fighterTransform.GetPosition();
	fighterRotation = fighterTransform.GetRotation();
	fighterScale = fighterTransform.GetScale();

	Mesh fish = Mesh();
	fish.Create(&m_shaderDiffuse, "../Assets/Models/Fish.obj");
	fish.SetCameraPosition(m_camera.GetPosition());
	fish.SetScale({ 0.003f, 0.003f, 0.003f });
	fish.SetPosition({ 0.0f, 0.0f, 0.0f });
	fish.SetSpecularStrength(4.0f);
	fish.SetSpecularColor({ 1.0f, 1.0f, 1.0f });
	fish.SetRotation({ 0.0f, glm::radians(180.0f), 0.0f });

	Fonts fpsFont = Fonts();
	fpsFont.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts mousePosFont = Fonts();
	mousePosFont.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts leftBtnFont = Fonts();
	leftBtnFont.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts middleBtnFont = Fonts();
	middleBtnFont.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts fighterPositionFont = Fonts();
	fighterPositionFont.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts fighterRotationFont = Fonts();
	fighterRotationFont.Create(&m_shaderFont, "arial.ttf", 100);

	Fonts fighterScaleFont = Fonts();
	fighterScaleFont.Create(&m_shaderFont, "arial.ttf", 100);

	m_postProcessor = PostProcessor();
	m_postProcessor.Create(&m_shaderPost);

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
			OpenGLTechniques::ToolWindow::ResetTransform = false;
			glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
			glm::vec3 rot = { 1.0f, 0.0f, 0.0f };
			glm::vec3 scale = { 0.00008f, 0.00008f, 0.00008f };
			fighterTransform.SetPosition(pos);
			fighterTransform.SetRotation(rot);
			fighterTransform.SetScale(scale);
			fighterTranslation = pos;
			fighterRotation = rot;
			fighterScale = scale;
		}

		if (m_currScene == MOVE_LIGHT)
		{
			currFighter = &fighter;
			if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				glm::vec3 mouseVec = { (float)mouseX, (float)mouseY, 0 };
				Mesh::Lights[0].SetPosition(CalculateQuadrantPosition(mouseVec, m_centerVec, Mesh::Lights[0].GetPosition(), maxSpeed));
			}
		}

		if (m_currScene == TRANSFORM)
		{
			currFighter = &fighterTransform;
			if (m_leftClickHandler.IsInProgress() || m_middleClickHandler.IsInProgress())
			{
				HandleTransform();
				fighterTransform.SetPosition(fighterTranslation);
				fighterTransform.SetRotation(fighterRotation);
				fighterTransform.SetScale(fighterScale);
			}
		} 

		if (m_currScene == WATER_SCENE)
		{
			m_time += 0.01f;
			m_postProcessor.SetFrequency(OpenGLTechniques::ToolWindow::Frequency);
			m_postProcessor.SetAmplitude(OpenGLTechniques::ToolWindow::Amplitude);
			m_postProcessor.SetTime(m_time);

			m_postProcessor.SetWireframeMode(OpenGLTechniques::ToolWindow::WireframeRenderChecked);
			m_postProcessor.SetTintBlue(OpenGLTechniques::ToolWindow::TintBlueChecked);
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
			fighterTransform.Render(pv);
			break;

		case WATER_SCENE:
			m_postProcessor.Start();
			fish.Render(pv);
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
		fighterPositionFont.RenderText("Fighter Position: " + vec3_to_string(currFighter->GetPosition()), 50, 130, 0.2f, { 1.0f, 1.0f, 0.0f });
		fighterRotationFont.RenderText("Fighter Rotation: " + vec3_to_string(glm::degrees(currFighter->GetRotation())), 50, 150, 0.2f, { 1.0f, 1.0f, 0.0f });
		fighterScaleFont.RenderText("Fighter Scale: " + vec3_to_string(currFighter->GetScale()), 50, 170, 0.2f, { 1.0f, 1.0f, 0.0f });

		if (m_currScene == WATER_SCENE) {
			m_postProcessor.End();
		}
#pragma endregion


		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if window was closed



#pragma region Cleanup
	m_shaderColor.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderFont.Cleanup();
	m_shaderPost.Cleanup();

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

	m_postProcessor.Cleanup();
#pragma endregion

}

void GameController::HandleTransform()
{	
	if (OpenGLTechniques::ToolWindow::TranslateChecked)
	{
		glm::vec3 axes = { m_leftClickHandler.IsInProgress(), 1, m_middleClickHandler.IsInProgress() };
		double mouseX;
		double mouseY;

		glfwGetCursorPos(WindowController::GetInstance().GetWindow(), &mouseX, &mouseY);

		glm::vec3 clickVector = glm::vec3({ (float)mouseX, WindowController::GetInstance().GetResolution().m_height - (float)mouseY, 0 }) - m_centerVec;
		float maxDistance = glm::length(quadBottomRight);
		float distance = min(glm::length(clickVector), maxDistance);
		float speed = 0.003f * (distance / maxDistance);
		clickVector = glm::normalize(clickVector);

		float newX = fighterTranslation.x + (axes.x * (clickVector.x * speed));
		float newY = fighterTranslation.y + (clickVector.y * speed);
		float newZ = fighterTranslation.z + (axes.z * (-clickVector.y * speed));

		fighterTranslation = glm::vec3({ newX, newY, newZ });
	}

	Resolution res = WindowController::GetInstance().GetResolution();
	float maxDistClamp = (float)max(res.m_width, res.m_height) / 2.0f;

	if (OpenGLTechniques::ToolWindow::RotateChecked)
	{		
		glm::vec3 rotationAdjustment = { 0.0f, 0.0f, 0.0f };

		float maxSpeed = 0.03f;

		if (m_leftClickHandler.IsInProgress())
		{
			glm::vec2 gesture = m_leftClickHandler.GetGestureVector();

			float yAmount = gesture.x / maxDistClamp;
			float xAmount = gesture.y / maxDistClamp;

			rotationAdjustment.x = xAmount * maxSpeed;
			rotationAdjustment.y = yAmount * maxSpeed;

		}

		if (m_middleClickHandler.IsInProgress())
		{
			glm::vec2 gesture = m_middleClickHandler.GetGestureVector();
			float zAmount = gesture.y / maxDistClamp;
			rotationAdjustment.z = zAmount * maxSpeed;
		}
		rotationAdjustment.x = -rotationAdjustment.x;
		fighterRotation = fighterRotation + rotationAdjustment;
	}

	if (OpenGLTechniques::ToolWindow::ScaleChecked)
	{
		glm::vec3 scaleAdjustment = { 0.0f, 0.0f, 0.0f };

		float maxSpeed = 0.000005f;

		if (m_leftClickHandler.IsInProgress())
		{
			glm::vec2 gesture = m_leftClickHandler.GetGestureVector();

			float xAmount = gesture.x / maxDistClamp;
			float yAmount = gesture.y / maxDistClamp;

			scaleAdjustment.x = xAmount * maxSpeed;
			scaleAdjustment.y = yAmount * maxSpeed;

		}

		if (m_middleClickHandler.IsInProgress())
		{
			glm::vec2 gesture = m_middleClickHandler.GetGestureVector();

			float zAmount = gesture.y / maxDistClamp;
			scaleAdjustment.z = zAmount * maxSpeed;
		}
		
		// do not allow scale to go into negatives
		float scaleX = max(maxSpeed, fighterScale.x + scaleAdjustment.x);
		float scaleY = max(maxSpeed, fighterScale.y + scaleAdjustment.y);
		float scaleZ = max(maxSpeed, fighterScale.z + scaleAdjustment.z);

		fighterScale = { scaleX, scaleY, scaleZ };
	}
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