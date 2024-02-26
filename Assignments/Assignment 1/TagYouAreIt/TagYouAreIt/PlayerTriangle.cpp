#include "PlayerTriangle.h"

PlayerTriangle::PlayerTriangle()
{
	m_color = { 1, 0, 0, 1 };
	m_speed = 0.05f;
}

PlayerTriangle::~PlayerTriangle()
{
}

void PlayerTriangle::Render(glm::mat4 _wvp)
{
	GameEntity::Render(_wvp);
}