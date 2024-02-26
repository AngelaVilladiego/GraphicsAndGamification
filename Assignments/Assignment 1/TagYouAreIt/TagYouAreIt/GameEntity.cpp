#define _USE_MATH_DEFINES
#include "GameEntity.h"
#include "Camera.h"
#include <cmath>

GameEntity::GameEntity() 
{
	m_position = { 0, 0, 0 };
	//m_vertices = Triangle::GetVerticesAtPosition(m_position[0], m_position[1], m_position[2]);
	m_vertices = { 0.0f, 1.0f, 0.0, -0.866f, -0.5f, 0.f, 0.866f, -0.5f, 0.f };
	m_angle = 0.f;
	m_speed = 0.005f;
}

GameEntity::~GameEntity()
{
}

void GameEntity::Create(Shader* _shader, Camera _camera)
{
	m_vertexData = GenerateVertexData();
	Mesh::Create(_shader, _camera);
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
	m_position += (_direction * m_speed);
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

void GameEntity::Render(glm::mat4 _wvp)
{
	//create the world matrix to pass to the renderer
	glm::mat4 world = glm::mat4(1.f);
	world = glm::translate(world, m_position);
	world = glm::rotate(world, float(m_angle * (M_PI/180)), {0, 0, 1});

	m_world = world;


	Mesh::Render(_wvp);
}