#ifndef PLAYER_TRIANGLE_H
#define PLAYER_TRIANGLE_H

#include "Triangle.h"

class PlayerTriangle : public Singleton<PlayerTriangle>
{
public:
	// Constructors / Destructors
	PlayerTriangle();
	virtual ~PlayerTriangle();

	// methods
	std::vector<GLfloat> GetVertexData();

	// accessors/modifiers
	std::vector<GLfloat> GetPosition() { return m_position; }
	void SetPosition(std::vector<GLfloat> position);

private:
	std::vector<GLfloat> m_position;
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_color;
	GLfloat speed;
};

#endif // TRIANGLE_H

