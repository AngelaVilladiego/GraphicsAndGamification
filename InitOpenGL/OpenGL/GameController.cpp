#include "GameController.h"
#include "WindowController.h"
#include "Fonts.h"
//#include "ToolWindow.h"

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderFont = { };
	m_shaderPost = { };
	m_camera = { };
	m_meshes.clear();
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0, 0, 0, 1); // Black
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand((unsigned int)time(0));
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// create default perspective camera
	Resolution r = WindowController::GetInstance().GetResolution();
	glViewport(0, 0, r.m_width, r.m_height);
	m_camera = Camera(r);
}

void GameController::RunGame()
{

	// Create and compile our GLSL program from the shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	m_shaderSkybox = Shader();
	m_shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	m_shaderPost = Shader();
	m_shaderPost.LoadShaders("PostProcess.vertexshader", "PostProcess.fragmentshader");


	// Create meshes
	Mesh m = Mesh();
	m.Create(&m_shaderColor, "../Assets/Models/Teapot.obj");
	m.SetPosition({ 0.0f, 0.8f, 1.0f });
	m.SetColor({ 1.0f, 1.0f, 1.0f });
	m.SetScale({ 0.01f, 0.01f, 0.01f });
	Mesh::Lights.push_back(m);

	Mesh box = Mesh();
	box.Create(&m_shaderDiffuse, "../Assets/Models/Cube.obj", 10);
	box.SetCameraPosition(m_camera.GetPosition());
	box.SetScale({ 0.1f, 0.1f, 0.1f });
	box.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes.push_back(box);

	/*
	Mesh fighter = Mesh();
	fighter.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	fighter.SetCameraPosition(m_camera.GetPosition());
	fighter.SetScale({ 0.002f, 0.002f, 0.002f });
	fighter.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshBoxes.push_back(fighter);
	*/

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 40);

	m_postProcessor = PostProcessor();
	m_postProcessor.Create(&m_shaderPost);
	 
	//fps counting
	double lastTime = glfwGetTime();
	int fps = 0;
	string fpsS = "0";

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		m_postProcessor.Start();
		for (unsigned int count = 0; count < m_meshes.size(); count++)
		{
			m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
		{
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}


		double currentTime = glfwGetTime();
		fps++;
		if (currentTime - lastTime >= 1.0)
		{
			fpsS = "FPS: " + to_string(fps);
			fps = 0;
			lastTime += 1.0;
		}

		f.RenderText(fpsS, 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });
		m_postProcessor.End();		



		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();
	} 
	while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if window was closed


	//cleanup

	for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
	{
		Mesh::Lights[count].Cleanup();
	}
	for (unsigned int count = 0; count < m_meshes.size(); count++)
	{
		m_meshes[count].Cleanup();
	}
	f.Cleanup();
	m_postProcessor.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderSkybox.Cleanup();
	m_shaderPost.Cleanup();
}