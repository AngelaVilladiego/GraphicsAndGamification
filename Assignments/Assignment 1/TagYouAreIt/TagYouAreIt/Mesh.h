#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
class Shader;

class Mesh
{
public:
	// Constructors / Destructors
	Mesh();
	virtual ~Mesh();

	// Methods
	virtual void Create(Shader* _shader, std::vector<GLfloat> _vertexData);
	void Cleanup();
	void Render(glm::mat4 _wvp);
	virtual void Translate(glm::vec3 _trans);
	virtual void Rotate();

	// accessors/mutators
	


protected:
	Shader* m_shader;
	GLuint m_vertexBuffer;
	std::vector<GLfloat> m_vertexData;
	glm::mat4 m_world;

	void SetVertexData(std::vector<GLfloat> _vertexData) { m_vertexData = _vertexData; }
};

#endif // MESH_H

