#ifndef PLAYER_TRIANGLE_H
#define PLAYER_TRIANGLE_H

#include "Triangle.h"
#include "Mesh.h"

class PlayerTriangle : public Mesh
{
public:
	// Constructors / Destructors
	PlayerTriangle();
	virtual ~PlayerTriangle();

	// methods
	std::vector<GLfloat> GetVertexData();
	void Create(Shader* _shader);
	void Translate(glm::vec3 _direction) override;

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

