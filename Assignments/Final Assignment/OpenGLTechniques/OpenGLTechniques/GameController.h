#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Skybox.h"
#include "WindowController.h"
#include "Mesh.h"
#include "Camera.h"
#include "SceneType.h"

class GameController : public Singleton<GameController>
{
public:
	// Constructors / Destructors
	GameController();
	virtual ~GameController() { }

	//Methods
	void Initialize(string title, bool fullscreen);
	void ShowMovieLights();
	void RunGame();

private:
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Shader m_shaderSkybox;
	Camera m_camera;
	vector<Mesh> m_meshes;
	Skybox m_skybox;
	glm::vec2 m_mousePos;
	float m_lightSpeed;
	SceneType m_currScene;
	vector<Mesh> m_spaceMeshes;
};

#endif // GAME_CONTROLLER_H

