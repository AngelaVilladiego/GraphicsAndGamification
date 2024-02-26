#include "NpcTriangle.h"
#include <random>

NpcTriangle::NpcTriangle()
{

	m_tagged = false;
	m_position = { 0, 0, 0 };

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
}

NpcTriangle::~NpcTriangle()
{

}

void NpcTriangle::Tag()
{
	if (m_tagged) {
		return;
	}

	m_tagged = true;
	SetColor({ 0, 0, 1, 1 });
}

void NpcTriangle::Render(glm::mat4 _wvp)
{
	//apply necessary behaviour
	FaceLocation({ 0, 0, 0 });

	GameEntity::Render(_wvp);
}


void NpcTriangle::KeepDistance(glm::vec3 _playerPos)
{

}
	
void NpcTriangle::FaceLocation(glm::vec3 _playerPos)
{
	//demo rotates one degree per frame
	if (m_angle == 355) {
		m_angle = 0;
	}
	else {
		m_angle += 0.5;
	}
}

