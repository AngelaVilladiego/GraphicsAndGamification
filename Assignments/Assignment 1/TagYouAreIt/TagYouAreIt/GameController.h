#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "PlayerTriangle.h"
#include "NpcTriangle.h"

#include <array>

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
	Shader m_shader;
	Camera m_camera;
	PlayerTriangle m_player;
	std::vector<NpcTriangle> m_npcs;

	const int NPC_COUNT = 10;

	const glm::vec3 UP_VEC = { 0, 1, 0 };
	const glm::vec3 DOWN_VEC = { 0, -1, 0 };
	const glm::vec3 LEFT_VEC = { -1, 0, 0 };	
	const glm::vec3 RIGHT_VEC = { 1, 0, 0 };	
};

#endif // GAME_CONTROLLER_H

