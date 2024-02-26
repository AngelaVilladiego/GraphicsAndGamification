#include "NpcTriangle.h"
#include <random>
#include <math.h>

NpcTriangle::NpcTriangle()
{
	m_tagged = false;
}

NpcTriangle::~NpcTriangle()
{
}

void NpcTriangle::Create(Shader* _shader, Camera _camera)
{
	//randomizer retrieved from https://coliru.stacked-crooked.com/a/c5b94870fdcd13f2
	const float range_from = 2;
	const float range_to = 10;
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_real_distribution<float>  distr(range_from, range_to);


	for (int i = 0; i < 2; i++) {

		float coord = distr(generator);

		bool isNegative = rand() % 2;

		if (isNegative) {
			coord *= -1;
		}

		m_position[i] = coord;
	}

	m_position[2] = 0;

	m_color = { 0, 1, 0, 1 };

	m_speed = 0.02f;

	GameEntity::Create(_shader, _camera);
}

void NpcTriangle::Tag()
{
	m_tagged = true;
	Mesh::SetColor({ 0, 0, 1, 1 });
}

void NpcTriangle::ApplyBehaviour(glm::vec3 _playerPos)
{
	//apply necessary behaviour
	FaceLocation(_playerPos);
	KeepDistance(_playerPos);

	if (m_tagged)
	{
		return;
	}

	//check if needs to be tagged
	float distance = glm::distance(_playerPos, m_position);
	if (distance < 1)
	{
		Tag();
	}
}

void NpcTriangle::KeepDistance(glm::vec3 _playerPos)
{
	float distance = glm::distance(_playerPos, m_position);

	if (distance < 10)
	{
		// get "away" direction
		glm::vec3 direction = m_position - _playerPos;
		direction = glm::normalize(direction);
		Translate(direction);
	}
	else if (distance > 11)
	{
		// get "towards" direction
		glm::vec3 direction = _playerPos - m_position;
		direction = glm::normalize(direction);
		Translate(direction);
	}	
}
	
void NpcTriangle::FaceLocation(glm::vec3 _playerPos)
{
	//get angle to player triangle

	const glm::vec3 Y_VEC = { 0, 1, 0 };
	const glm::vec3 Z_VEC = { 0, 0, 1 };

	//vector from npc to player
	glm::vec3 direction = _playerPos - m_position;
	direction = glm::normalize(direction);

	//get angle between the up vector and the direction vector
	float newAngle = acos(glm::dot(Y_VEC, direction));

	//get the direction of the angle (clockwise or counterclockwise)
	glm::vec3 cross = glm::cross(Y_VEC, direction);
	bool clockwise = glm::dot(Z_VEC, cross) < 0;

	if (clockwise)
	{
		newAngle *= -1;
	}

	m_angle = newAngle;

	//demo rotates one degree per frame
	/*
	if (m_angle == 355) {
		m_angle = 0;
	}
	else {
		m_angle += 0.5;
	}
	*/
}

