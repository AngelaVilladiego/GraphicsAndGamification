#include "PlayerTriangle.h"

PlayerTriangle::PlayerTriangle()
{
	m_position = { 0, 0, 0 };
	m_vertices = Triangle::GetVerticesAtPosition(m_position[0], m_position[1], m_position[2]);
	m_color = { 1, 0, 0, 1 };
	m_speed = 0.1f;
}

PlayerTriangle::~PlayerTriangle()
{
}

void PlayerTriangle::SetPosition(glm::vec3 position) 
{
	m_position = position;
	//m_vertices = Triangle::GetVerticesAtPosition(m_position[0], m_position[1], m_position[2]);
}

std::vector<GLfloat> PlayerTriangle::GetVertexData()
{
	std::vector<GLfloat> vertexData = {};

	for (int i = 0; i < m_vertices.size(); i++) 
	{
		vertexData.push_back(m_vertices[i]);

		if ((i + 1) % 3 == 0) {
			vertexData.insert(vertexData.end(), m_color.begin(), m_color.end());
		}
	}

	return vertexData;
}