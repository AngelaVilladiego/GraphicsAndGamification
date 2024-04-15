#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	m_shader = nullptr;
	m_texture = { };
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_world = glm::mat4(1.0f);
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
}

Mesh::~Mesh()
{
}

void Mesh::Create(Shader* _shader)
{
	m_shader = _shader;

	m_texture = Texture();
	m_texture.LoadTexture("../Assets/Textures/Wood.jpg");

	float a = 26.0f;
	float b = 42.0f;
	m_vertexData = { 
		/* Position */			/*	RGB Color	*/		/* Texture Coords */
		50.0f, 50.0f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,			//top-right		
		50.0f, -50.0f, 0.0f,	0.0f, 1.0f, 0.0f,		1.0f, 0.0f,			//bottom-right	
		-50.0f, -50.0f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 0.0f,			//bottom-left	
		-50.0f, 50.0f, 0.0f,	1.0f, 1.0f, 1.0f,		0.0f, 1.0f,			//top-left	

	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//vector<>.data() Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	m_indexData = {
		2, 0, 3, 2, 1, 0
	};

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(float), m_indexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_texture.Cleanup();
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
		8 * sizeof(float),			/*stride*/
		(void*)0);	/*array buffer offset*/

	// Second attribute buffer : colors
	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(m_shader->GetAttrColors(), 
		3,							// size of color attribute (3 components per color
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		8 * sizeof(float),			// stride (8 floats per vertex definition
		(void*)(3 * sizeof(float))	// array buffer offset
	);

	// 3rd attribute buffer: texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), // The attribute to configure
		2,							// size (2 points per coordinate)
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		8 * sizeof(float),			// stride (8 floats per vertex definition
		(void*)(6 * sizeof(float))	// array buffer offset
	);


	// 4th attribute buffer : WVP
	m_world = glm::rotate(m_world, 0.001f, { 0, 1, 0 }); // Rotate the camera a tiny bit around the y axis every frame
	_wvp *= m_world;
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetTexture());

	glDrawElements(GL_TRIANGLES, m_indexData.size(), GL_UNSIGNED_BYTE, (void*)0);	//Draw the triangle

	glDisableVertexAttribArray(m_shader->GetAttrColors());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}