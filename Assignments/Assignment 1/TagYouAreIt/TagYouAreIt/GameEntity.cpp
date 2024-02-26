#include "GameEntity.h"

GameEntity::GameEntity() 
{
	
}

GameEntity::~GameEntity()
{
}

void GameEntity::Create(Shader* _shader)
{
	Mesh::Create(_shader, GenerateVertexData());
}

std::vector<GLfloat> GameEntity::GenerateVertexData()
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

void GameEntity::Translate(glm::vec3 _direction)
{
	Mesh::Translate(_direction * m_speed);
}

void GameEntity::SetColor(std::vector<GLfloat> _color)
{
	m_color = _color;

	for (int i = 0; i < m_vertices.size() / 3; i++)
	{
		m_vertexData[i * 7 + 3] = m_color[0];
		m_vertexData[i * 7 + 4] = m_color[1];
		m_vertexData[i * 7 + 5] = m_color[2];
		m_vertexData[i * 7 + 6] = m_color[3];
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}