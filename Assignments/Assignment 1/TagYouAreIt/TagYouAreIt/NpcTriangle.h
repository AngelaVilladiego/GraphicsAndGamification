#pragma once

#ifndef NPC_TRIANGLE_H
#define NPC_TRIANGLE_H

#include "GameEntity.h"

class NpcTriangle : public GameEntity
{
public:
	// constructors/destructors
	NpcTriangle();
	virtual ~NpcTriangle();

	//methods
	virtual void Create(Shader* _shader, Camera _camera) override;	
	void ApplyBehaviour(glm::vec3 _playerPos);

private:
	//methods
	void Tag();
	void KeepDistance(glm::vec3 _playerPos);
	void FaceLocation(glm::vec3 _playerPos);

	//attributes
	bool m_tagged;
};

#endif // NPC_TRIANGLE_H