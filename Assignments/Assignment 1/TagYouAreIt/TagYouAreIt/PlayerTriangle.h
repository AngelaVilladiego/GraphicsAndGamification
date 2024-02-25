#ifndef PLAYER_TRIANGLE_H
#define PLAYER_TRIANGLE_H

#include "Triangle.h"

class PlayerTriangle
{
public:
	// Constructors / Destructors
	PlayerTriangle();
	virtual ~PlayerTriangle();

	// methods
	std::vector<GLfloat> GetVertexData();

	// accessors/modifiers
	glm::vec3 GetPosition() { return m_position; }
	void SetPosition(glm::vec3 position);
	float GetSpeed() { return m_speed; }

private:
	glm::vec3 m_position;
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_color;
	float m_speed;
};

#endif // TRIANGLE_H

