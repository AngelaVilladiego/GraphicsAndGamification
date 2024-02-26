#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

Mesh::Mesh()
{
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_world = glm::mat4(1.0f);
	m_view = glm::mat4(1.0f);
	m_projection = glm::mat4(1.0f);
	m_vertexData = { };
}

Mesh::~Mesh()
{
}

void Mesh::Create(Shader* _shader, Camera _camera)
{
	m_shader = _shader;

	m_view = _camera.GetView();
	m_projection = _camera.GetProjection();

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//vector<>.data() Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	// send view and projection matrices to the shader
	glUseProgram(m_shader->GetProgramId());
	GLint viewMatrixId = glGetUniformLocation(m_shader->GetProgramId(), "view");
	GLint projectionMatrixId = glGetUniformLocation(m_shader->GetProgramId(), "projection");
	
	glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, &m_view[0][0]);
	glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, &m_projection[0][0]);

	// this can go after where you initialize your cube or triangle vertex information
	m_worldMatrixId = glGetUniformLocation(m_shader->GetProgramId(), "world"); //modelMatrixId can be a global GLint
	glUniformMatrix4fv(m_worldMatrixId, 1, GL_FALSE, &m_world[0][0]); //modelMatrix can be a global glm::mat4
	glUseProgram(0);
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
	//_wvp *= m_world;
	//glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);
	glUniformMatrix4fv(m_worldMatrixId, 1, GL_FALSE, &m_world[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(m_shader->GetAttrColors());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glUseProgram(0);
}

