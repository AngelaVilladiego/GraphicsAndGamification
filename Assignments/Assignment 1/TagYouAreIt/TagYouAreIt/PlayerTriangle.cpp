#include "PlayerTriangle.h"

PlayerTriangle::PlayerTriangle()
{
	m_position = { 0, 0, 0 };
	m_color = { 1, 0, 0, 1 };
	m_speed = 0.05f;
	m_vertices = Triangle::GetVerticesAtPosition(m_position[0], m_position[1], m_position[2]);
}

PlayerTriangle::~PlayerTriangle()
{
}