#pragma once

#ifndef NPC_TRIANGLE_H
#define NPC_TRIANGLE_H

#include "GameEntity.h"

class NpcTriangle : public GameEntity
{
public:
	NpcTriangle();
	virtual ~NpcTriangle();

	virtual void Create(Shader* _shader, Camera _camera) override;

	void Tag();
	void ApplyBehaviour(glm::vec3 _playerPos);

private:
	void KeepDistance(glm::vec3 _playerPos);
	void FaceLocation(glm::vec3 _playerPos);

	bool m_tagged;
};

#endif // NPC_TRIANGLE_H