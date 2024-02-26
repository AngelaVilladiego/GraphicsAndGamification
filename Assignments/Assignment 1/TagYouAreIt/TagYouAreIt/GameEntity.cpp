#define _USE_MATH_DEFINES
#include "GameEntity.h"
#include "Camera.h"
#include <cmath>

GameEntity::GameEntity() 
{
	m_position = { 0, 0, 0 };
	m_angle = 0.f;
	m_speed = 0.05f;
}

GameEntity::~GameEntity()
{
}

void GameEntity::Create(Shader* _shader, Camera _camera)
{
	m_vertexData = { 0.0f, 1.0f, 0.0, -0.866f, -0.5f, 0.f, 0.866f, -0.5f, 0.f };
	Mesh::Create(_shader, _camera);
}

void GameEntity::Translate(glm::vec3 _direction)
{
	m_position += (_direction * m_speed);
}

void GameEntity::Render()
{
	//create the world matrix to pass to the renderer
	glm::mat4 world = glm::mat4(1.f);
	world = glm::translate(world, m_position);
	world = glm::rotate(world, m_angle, {0, 0, 1});

	m_world = world;

	Mesh::Render();
}