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
	void Create(Shader* _shader, std::vector<GLfloat> _vertexData);
	void Cleanup();
	void Render(glm::mat4 _wvp);
	void Translate(glm::vec3 _pos);

	// accessors/mutators
	

private:
	Shader* m_shader;
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	std::vector<GLfloat> m_vertexData;
	std::vector<GLubyte> m_indexData;
	glm::mat4 m_world;
};

#endif // MESH_H

