#pragma once

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "StandardIncludes.h"
#include "Triangle.h"
#include "Mesh.h"

class GameEntity : public Mesh
{
public:
	GameEntity();
	virtual ~GameEntity();

	// methods
	//void Create(Shader* _shader, Camera _camera);
	//std::vector<GLfloat> GenerateVertexData();
	void Translate(glm::vec3 _direction);
	void Render() override;
	virtual void Create(Shader* _shader, Camera _camera) override;

	// accessors/modifiers
	glm::vec3 GetPosition() { return m_position; }
	float GetSpeed() { return m_speed; }

protected:
	glm::vec3 m_position;
	//std::vector<GLfloat> m_vertices;
	float m_angle;
	float m_speed;
};

#endif // GAME_ENTITY_H

