#include "Mesh.h"
#include "Shader.h"
#include "OBJ_loader.h"
#include "Vec3ToString.h"

vector<Mesh> Mesh::Lights;

Mesh::Mesh()
{
	m_shader = nullptr;
	m_textureDiffuse = { };
	m_textureSpecular = { };
	m_textureNormal = { };
	m_vertexBuffer = 0;
	m_world = glm::mat4();
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_scale = { 1, 1, 1 };
	m_color = { 0, 0, 0 };
	m_cameraPosition = { 0, 0, 0 };
	m_enableNormalMap = false;

	m_lightPosition = { 0, 0, 0 };
	m_specularStrength = 1;
	m_specularColor = { 1.0f, 1.0f, 1.0f };
	m_diffuseColor = { 0.0f, 0.0f, 0.0f };
	m_ambientColor = { 0.5f, 0.5f, 0.5f };

	m_instanceCount = 1;
	m_enableInstancing = false;
	m_elementSize = 0;

	m_instanceBuffer = 0;
	m_vertexData.clear();
	m_instanceData.clear();
}

Mesh::~Mesh()
{
}

string Mesh::RemoveFolder(string _map)
{
	const size_t last_slash_idx = _map.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		_map.erase(0, last_slash_idx + 1);
	}

	return _map;
}

void Mesh::CalculateTangents(vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent)
{
	// calculate tangent/bitangent vectors of both triangles
	objl::Vector3 edge1 = _vertices[1].Position - _vertices[0].Position;
	objl::Vector3 edge2 = _vertices[2].Position - _vertices[0].Position;

	objl::Vector2 deltaUV1 = _vertices[1].TextureCoordinate - _vertices[0].TextureCoordinate;
	objl::Vector2 deltaUV2 = _vertices[2].TextureCoordinate - _vertices[0].TextureCoordinate;

	float f = 1.0f / (deltaUV1.X * deltaUV2.Y - deltaUV2.X * deltaUV1.Y);

	_tangent.X = f * (deltaUV2.Y * edge1.X - deltaUV1.Y * edge2.X);
	_tangent.Y = f * (deltaUV2.Y * edge1.Y - deltaUV1.Y * edge2.Y);
	_tangent.Z = f * (deltaUV2.Y * edge1.Z - deltaUV1.Y * edge2.Z);

	_bitangent.X = f * (-deltaUV2.X * edge1.X + deltaUV1.X * edge2.X);
	_bitangent.Y = f * (-deltaUV2.X * edge1.Y + deltaUV1.X * edge2.Y);
	_bitangent.Z = f * (-deltaUV2.X * edge1.Z + deltaUV1.X * edge2.Z);
}

GLuint Mesh::GetShaderProgram()
{
	return m_shader->GetProgramId();
}

void Mesh::Create(Shader* _shader, string _file, int _instanceCount)
{
	m_shader = _shader;

	m_instanceCount = _instanceCount;
	if (m_instanceCount > 1)
	{
		m_enableInstancing = true;
	}

	objl::Loader Loader; // Initialize Loader
	M_ASSERT(Loader.LoadFile(_file) == true, "Failed to load mesh,"); // Load .obj File

	m_vertexData.clear();

	for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = Loader.LoadedMeshes[i];

		vector<objl::Vector3> tangents;
		vector<objl::Vector3> bitangents;
		vector<objl::Vertex> triangle;
		objl::Vector3 tangent;
		objl::Vector3 bitangent;

		for (unsigned int j = 0; j < curMesh.Vertices.size(); j += 3)
		{
			triangle.clear();
			triangle.push_back(curMesh.Vertices[j]);
			triangle.push_back(curMesh.Vertices[j + 1]);
			triangle.push_back(curMesh.Vertices[j + 2]);
			CalculateTangents(triangle, tangent, bitangent);
			tangents.push_back(tangent);
			bitangents.push_back(bitangent);
		}

		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			m_vertexData.push_back(curMesh.Vertices[j].Position.X);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Z);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.X);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Z);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);

			if (Loader.LoadedMaterials[0].map_bump != "")
			{
				int index = j / 3;
				m_vertexData.push_back(tangents[index].X);
				m_vertexData.push_back(tangents[index].Y);
				m_vertexData.push_back(tangents[index].Z);
				m_vertexData.push_back(bitangents[index].X);
				m_vertexData.push_back(bitangents[index].Y);
				m_vertexData.push_back(bitangents[index].Z);
			}
		}
	}

	m_textureDiffuse = Texture();
	m_textureDiffuse.LoadTexture("../Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_Kd));

	m_textureSpecular = Texture();
	if (Loader.LoadedMaterials[0].map_Ks != "")
	{
		m_textureSpecular.LoadTexture("../Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_Ks));
	}

	m_textureNormal = Texture();
	if (Loader.LoadedMaterials[0].map_bump != "")
	{
		m_textureNormal.LoadTexture("../Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_bump));
		m_enableNormalMap = true;
	}


	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (m_enableInstancing)
	{
		glGenBuffers(1, &m_instanceBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);

		float minX = -0.3f;
		float maxX = 0.3f;
		float minY = -0.1f;
		float maxY = 0.1f;
		float minZ = -0.23f;
		float maxZ = 0.55f;

		float randomX, randomY, randomZ;
		float distanceSquared;

		glm::vec3 exclusionCenter(0.0f, 0.0f, 0.22f);
		float exclusionRadius = 0.1f;

		srand(glfwGetTime());
		for (unsigned int i = 0; i < m_instanceCount; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);

			do {
				randomX = minX + (float)(rand() / (float)(RAND_MAX / (maxX - minX)));
				randomY = minY + (float)(rand() / (float)(RAND_MAX / (maxY - minY)));
				randomZ = minZ + (float)(rand() / (float)(RAND_MAX / (maxZ - minZ)));

				distanceSquared = pow(randomX - exclusionCenter.x, 2) + pow(randomY - exclusionCenter.y, 2) + pow(randomZ - exclusionCenter.z, 2);
			} while (distanceSquared <= pow(exclusionRadius, 2));


			glm::vec3 randomPos = { randomX, randomY, randomZ };

			

			model = glm::translate(model, randomPos);

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					m_instanceData.push_back(model[x][y]);
				}
			}
		}

		glBufferData(GL_ARRAY_BUFFER, m_instanceCount * sizeof(glm::mat4), m_instanceData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

string Mesh::Concat(string _s1, int _index, string _s2)
{
	string index = to_string(_index);
	return (_s1 + index + _s2);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_instanceBuffer);
	m_textureDiffuse.Cleanup();
	m_textureSpecular.Cleanup();
	m_textureNormal.Cleanup();
}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	int stride = 8;


	if (m_enableNormalMap == true)
	{
		stride += 6;
	}

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3,			/*size*/
		GL_FLOAT,	/*type*/
		GL_FALSE,	/*normalized?*/
		stride * sizeof(float),			/*stride*/
		(void*)0);	/*array buffer offset*/

	// 2nd attribute buffer : normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(),
		3,							// size of color attribute (3 components per color
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		stride * sizeof(float),			// stride (8 floats per vertex definition
		(void*)(3 * sizeof(float))	// array buffer offset
	);

	// 3rd attribute buffer: texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), // The attribute to configure
		2,							// size (2 points per coordinate)
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		stride * sizeof(float),			// stride (8 floats per vertex definition
		(void*)(6 * sizeof(float))	// array buffer offset
	);

	m_elementSize = 8;

	if (m_enableNormalMap == true)
	{
		//tangents
		glEnableVertexAttribArray(m_shader->GetAttrTangents());
		glVertexAttribPointer(m_shader->GetAttrTangents(), // The attribute to configure
			3,							// size (2 points per coordinate)
			GL_FLOAT,					// type
			GL_FALSE,					// normalized?
			stride * sizeof(float),			// stride (8 floats per vertex definition
			(void*)(8 * sizeof(float))	// array buffer offset
		);
		//bitangents
		glEnableVertexAttribArray(m_shader->GetAttrBitangents());
		glVertexAttribPointer(m_shader->GetAttrBitangents(), // The attribute to configure
			3,							// size (2 points per coordinate)
			GL_FLOAT,					// type
			GL_FALSE,					// normalized?
			stride * sizeof(float),			// stride (8 floats per vertex definition
			(void*)(11 * sizeof(float))	// array buffer offset
		);

		m_elementSize += 6;
	}

	//bind instancing data
	if (m_enableInstancing)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);

		// set att pointers for instance matrix (4 * vec4)
		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix());
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix(),
			4,				//size, (4 components)
			GL_FLOAT,
			GL_FALSE,
			sizeof(glm::mat4),
			(void*)0
		);

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 1);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 1,
			4,				//size, (4 components)
			GL_FLOAT,
			GL_FALSE,
			sizeof(glm::mat4),
			(void*)(sizeof(glm::vec4))
		);

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 2);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 2,
			4,				//size, (4 components)
			GL_FLOAT,
			GL_FALSE,
			sizeof(glm::mat4),
			(void*)(2 * sizeof(glm::vec4))
		);

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 3);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 3,
			4,				//size, (4 components)
			GL_FLOAT,
			GL_FALSE,
			sizeof(glm::mat4),
			(void*)(3 * sizeof(glm::vec4))
		);

		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix(), 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 1, 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 2, 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 3, 1);
	}
}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	m_world = glm::rotate(m_world, m_rotation.x, glm::vec3(1, 0, 0));
	m_world = glm::rotate(m_world, m_rotation.y, glm::vec3(0, 1, 0));
	m_world = glm::rotate(m_world, m_rotation.z, glm::vec3(0, 0, 1));
	m_world = glm::scale(m_world, m_scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);
	m_shader->SetInt("EnableNormalMap", m_enableNormalMap);
	m_shader->SetInt("EnableInstancing", m_enableInstancing);

	for (unsigned int i = 0; i < Lights.size(); i++)
	{
		// Configure light
		m_shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), m_ambientColor); //set the ambient lighting
		m_shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), Lights[i].GetColor()); //set the diffuse color to white
		m_shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), m_specularColor);
		m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
	}

	// configure material
	m_shader->SetFloat("material.specularStrength", m_specularStrength);
	m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_textureDiffuse.GetTexture());
	m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_textureSpecular.GetTexture());
	m_shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, m_textureNormal.GetTexture());
}

void Mesh::Render(glm::mat4 _pv)
{
	glUseProgram(m_shader->GetProgramId()); // Use our shader

	CalculateTransform();
	SetShaderVariables(_pv);
	BindAttributes();

	if (m_enableInstancing)
	{
		glDrawArraysInstanced(GL_TRIANGLES, 0, m_vertexData.size() / m_elementSize, m_instanceCount);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / m_elementSize);
	}

	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());

	if (m_enableNormalMap)
	{
		glDisableVertexAttribArray(m_shader->GetAttrTangents());
		glDisableVertexAttribArray(m_shader->GetAttrBitangents());
	}

	if (m_enableInstancing)
	{
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix());
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 1);
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 2);
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 3);
	}
}