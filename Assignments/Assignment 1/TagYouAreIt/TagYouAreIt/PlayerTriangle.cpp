#include "PlayerTriangle.h"

PlayerTriangle::PlayerTriangle()
{	
}

PlayerTriangle::~PlayerTriangle()
{
}

void PlayerTriangle::Create(Shader* _shader, Camera _camera)
{
	m_color = { 1, 0, 0, 1 };
	m_speed = 0.05f;
	GameEntity::Create(_shader, _camera);
}