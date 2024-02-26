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
	m_color = { };
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

	
	// send world, view, and projection matrices to the shader
	glUseProgram(m_shader->GetProgramId());
	
	glUniformMatrix4fv(m_shader->GetAttrView() , 1, GL_FALSE, &m_view[0][0]);
	glUniformMatrix4fv(m_shader->GetAttrProjection() , 1, GL_FALSE, &m_projection[0][0]);
	glUniformMatrix4fv(m_shader->GetAttrWorld(), 1, GL_FALSE, &m_world[0][0]); //modelMatrix can be a global glm::mat4
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Render()
{
	glUseProgram(m_shader->GetProgramId()); // Use our shader

	// vertices attribute buffer
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3,			/*size*/
		GL_FLOAT,	/*type*/
		GL_FALSE,	/*normalized?*/
		0,			/*stride*/
		(void*)0);	/*array buffer offset*/

	// color attribute buffer
	glUniform4fv(m_shader->GetAttrColor(), 1, &m_color[0]);

	// world attribute buffer
	glUniformMatrix4fv(m_shader->GetAttrWorld(), 1, GL_FALSE, &m_world[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
}

