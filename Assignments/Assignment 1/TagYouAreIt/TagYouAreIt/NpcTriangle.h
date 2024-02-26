#pragma once

#ifndef NPC_TRIANGLE_H
#define NPC_TRIANGLE_H

#include "GameEntity.h"

class NpcTriangle : public GameEntity
{
public:
	NpcTriangle();
	virtual ~NpcTriangle();

	void Tag();
	void Render(glm::mat4 _wvp) override;

private:
	void KeepDistance(glm::vec3 _playerPos);
	void FaceLocation(glm::vec3 _playerPos);

	bool m_tagged;
};

#endif // NPC_TRIANGLE_H