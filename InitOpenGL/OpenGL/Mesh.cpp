#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	m_shader = nullptr;
	m_texture = { };
	m_texture2 = { };
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	//m_world = glm::mat4(1.0f);
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

	m_texture2 = Texture();
	m_texture2.LoadTexture("../Assets/Textures/Emoji.jpg");

	m_vertexData = { 
		/* Position */				/* Normals */		/* Texture Coords*/
		-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,			0.0f, 0.0f, -1.0f,	1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,			0.0f, 0.0f, -1.0f,	1.0f, 1.0f,
		0.5f, 0.5f, -0.5f,			0.0f, 0.0f, -1.0f,	1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,			0.0f, 0.0f, -1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,			0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,			0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,			0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,			0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,			0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,			0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,			-1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,			-1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,			-1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,			-1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,			1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,			1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,			1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,			1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.5f, 0.5f, 0.5f,			1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,			0.0f, -1.0f, 0.0f,	1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,			0.0f, -1.0f, 0.0f,	1.0f, 0.0f,
		0.5f, -0.5f, 0.5f,			0.0f, -1.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,			0.0f, -1.0f, 0.0f,	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,			0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,			0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,			0.0f, 1.0f, 0.0f,	0.0f, 1.0f

	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//vector<>.data() Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	/*
	m_indexData = {
		2, 0, 3, 2, 1, 0
	};

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(float), m_indexData.data(), GL_STATIC_DRAW);
	*/
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_texture.Cleanup();
	m_texture2.Cleanup();
}

void Mesh::Render(glm::mat4 _wvp)
{
	glUseProgram(m_shader->GetProgramId()); // Use our shader

	m_shader->SetVec3("AmbientLight", { 0.1f, 0.1, 0.1f }); //set the ambient lighting
	m_shader->SetVec3("DiffuseColor", { 1.0f, 0.0f, 0.0f }); //set the diffuse color to red

	// First attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3,			/*size*/
		GL_FLOAT,	/*type*/ 
		GL_FALSE,	/*normalized?*/
		8 * sizeof(float),			/*stride*/
		(void*)0);	/*array buffer offset*/

	// Second attribute buffer : normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(), 
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
	m_rotation.y += 0.005f;
	glm::mat4 translate = glm::translate(_wvp, m_position);
	glm::mat4 transform = glm::rotate(translate, m_rotation.y, glm::vec3(0, 1, 0)); //rotate around the y axis
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &transform[0][0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	//explicitly set our texture to use the first texture unit (16 texture units total)
	glActiveTexture(GL_TEXTURE0); //Texture Unit 0
	glBindTexture(GL_TEXTURE_2D, m_texture.GetTexture());
	glUniform1i(m_shader->GetSampler1(), 0);

	//Set our second texture to use the second texture unit
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture2.GetTexture());
	glUniform1i(m_shader->GetSampler2(), 1);

	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size());

	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrColors());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}