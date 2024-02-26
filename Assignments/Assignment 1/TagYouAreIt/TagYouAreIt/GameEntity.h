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
	void Create(Shader* _shader, Camera _camera);
	std::vector<GLfloat> GenerateVertexData();
	void Translate(glm::vec3 _direction);
	void Render(glm::mat4 _wvp) override;

	// accessors/modifiers
	glm::vec3 GetPosition() { return m_position; }
	float GetSpeed() { return m_speed; }
	void SetColor(std::vector<GLfloat> _color);

protected:
	glm::vec3 m_position;
	std::vector<GLfloat> m_color;
	std::vector<GLfloat> m_vertices;
	float m_angle;
	float m_speed;
};

#endif // GAME_ENTITY_H

