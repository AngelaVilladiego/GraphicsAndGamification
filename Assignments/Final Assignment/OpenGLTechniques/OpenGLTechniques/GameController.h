#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "WindowController.h"
#include "Mesh.h"
#include "Camera.h"
#include "SceneType.h"
#include "GestureManager.h"
#include "PostProcessor.h"
#include "Skybox.h"

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
	Shader m_shaderFont;
	Shader m_shaderPost;
	Shader m_shaderSkybox;

	GLuint vao;

	PostProcessor m_postProcessor;
	Camera m_camera;
	float m_lightSpeed;
	SceneType m_currScene;

	glm::vec3 m_centerVec;

	glm::vec3 quadTopLeft;
	glm::vec3 quadTopRight;
	glm::vec3 quadBottomLeft;
	glm::vec3 quadBottomRight;

	glm::vec3 fighterTranslation;
	glm::vec3 fighterRotation;
	glm::vec3 fighterScale;

	GestureManager m_leftClickHandler;
	GestureManager m_middleClickHandler;

	float m_time;

	// Methods
	glm::vec3 CalculateQuadrantPosition(glm::vec3 mousePos, glm::vec3 centerPos, glm::vec3 currPos, float maxSpeed);
	void HandleTransform();
	float RandomFloat(float min, float max);
};

#endif // GAME_CONTROLLER_H

