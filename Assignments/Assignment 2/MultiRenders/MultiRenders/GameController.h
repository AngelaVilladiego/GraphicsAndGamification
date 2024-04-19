#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
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
	void RunGame();


private:
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderBasic;
	Shader m_shaderFont;
	Camera m_camera;
	vector<Mesh> m_meshes;
	float m_lightSpeed;
	SceneType m_currScene;	

	glm::vec3 quadTopLeft;
	glm::vec3 quadTopRight;
	glm::vec3 quadBottomLeft;
	glm::vec3 quadBottomRight;

	// Methods
	glm::vec3 CalculatePosition(glm::vec3 mousePos, glm::vec3 centerPos, glm::vec3 currPos, float maxSpeed);
};

#endif // GAME_CONTROLLER_H

