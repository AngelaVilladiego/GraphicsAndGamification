#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_world = glm::mat4(1.0f);
}

Mesh::~Mesh()
{
}

void Mesh::Create(Shader* _shader, std::vector<GLfloat> _vertexData)
{
	m_shader = _shader;

	m_vertexData = _vertexData;

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//vector<>.data() Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Render(glm::mat4 _wvp)
{
	glUseProgram(m_shader->GetProgramId()); // Use our shader

	// First attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3,			/*size*/
		GL_FLOAT,	/*type*/
		GL_FALSE,	/*normalized?*/
		7 * sizeof(float),			/*stride*/
		(void*)0);	/*array buffer offset*/

	// Second attribute buffer : colors
	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(m_shader->GetAttrColors(),
		4,							// size of color attribute (4 components per color
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		7 * sizeof(float),			// stride (7 floats per vertex definition
		(void*)(3 * sizeof(float))	// array buffer offset
	);

	// Third attribute buffer : WVP
	_wvp *= m_world;
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(m_shader->GetAttrColors());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
}

void Mesh::Translate(glm::vec3 _pos)
{
	m_world = glm::translate(m_world, _pos);
}