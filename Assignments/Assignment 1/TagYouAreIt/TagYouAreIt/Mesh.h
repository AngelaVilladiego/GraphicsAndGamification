#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Camera.h"
class Shader;

class Mesh
{
public:
	// Constructors / Destructors
	Mesh();
	virtual ~Mesh();

	// Methods
	virtual void Create(Shader* _shader, Camera _camera);
	void Cleanup();
	virtual void Render();

	// accessors/mutators
	void SetColor(glm::vec4 _color) { m_color = _color; }

protected:
	Shader* m_shader;
	GLuint m_vertexBuffer;
	std::vector<GLfloat> m_vertexData;
	glm::mat4 m_world;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::vec4 m_color;
};

#endif // MESH_H

