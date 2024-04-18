#include "Mesh.h"
#include "Shader.h"
#include "OBJ_loader.h"

vector<Mesh> Mesh::Lights;

Mesh::Mesh()
{
	m_shader = nullptr;
	m_textureDiffuse = { };
	m_textureSpecular = { };
	m_textureNormal = { };
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_world = glm::mat4();
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_scale = { 1, 1, 1 };
	m_color = { 0, 0, 0 };
	m_cameraPosition = { 0, 0, 0 };
	m_enableNormalMap = false;
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

GLuint Mesh::GetShaderProgram()
{
	return m_shader->GetProgramId();
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

void Mesh::Create(Shader* _shader, string _file)
{
	m_shader = _shader;

	std::cout << "creating mesh for shader:" << _shader->GetProgramId() << endl;

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
	std::cout << "diffuse texture added: " << RemoveFolder(Loader.LoadedMaterials[0].map_Kd) << endl;


	m_textureSpecular = Texture();
	if (Loader.LoadedMaterials[0].map_Ks != "")
	{
		m_textureSpecular.LoadTexture("../Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_Ks));
		std::cout << "specular texture added: " << RemoveFolder(Loader.LoadedMaterials[0].map_Ks) << endl;
	}

	m_textureNormal = Texture();
	if (Loader.LoadedMaterials[0].map_bump != "")
	{
		m_textureNormal.LoadTexture("../Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_bump));
		m_enableNormalMap = true;

		std::cout << "map bump added: " << RemoveFolder(Loader.LoadedMaterials[0].map_bump) << endl;
	}


	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//vector<>.data() Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}

string Mesh::Concat(string _s1, int _index, string _s2)
{
	string index = to_string(_index);
	return (_s1 + index + _s2);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_textureDiffuse.Cleanup();
	m_textureSpecular.Cleanup();
	m_textureNormal.Cleanup();
}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3,			/*size*/
		GL_FLOAT,	/*type*/
		GL_FALSE,	/*normalized?*/
		14 * sizeof(float),			/*stride*/
		(void*)0);	/*array buffer offset*/

	// 2nd attribute buffer : normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(),
		3,							// size of color attribute (3 components per color
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		14 * sizeof(float),			// stride (8 floats per vertex definition
		(void*)(3 * sizeof(float))	// array buffer offset
	);

	// 3rd attribute buffer: texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), // The attribute to configure
		2,							// size (2 points per coordinate)
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		14 * sizeof(float),			// stride (8 floats per vertex definition
		(void*)(6 * sizeof(float))	// array buffer offset
	);	

	//tangents
	glEnableVertexAttribArray(m_shader->GetAttrTangents());
	glVertexAttribPointer(m_shader->GetAttrTangents(), // The attribute to configure
		3,							// size (2 points per coordinate)
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		14 * sizeof(float),			// stride (8 floats per vertex definition
		(void*)(9 * sizeof(float))	// array buffer offset
	);

	//bitangents
	glEnableVertexAttribArray(m_shader->GetAttrBitangents());
	glVertexAttribPointer(m_shader->GetAttrBitangents(), // The attribute to configure
		3,							// size (2 points per coordinate)
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		14 * sizeof(float),			// stride (8 floats per vertex definition
		(void*)(12 * sizeof(float))	// array buffer offset
	);
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

	for (unsigned int i = 0; i < Lights.size(); i++)
	{
		// Configure light
		m_shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), { 0.1f, 0.1f, 0.1f }); //set the ambient lighting
		m_shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), Lights[i].GetColor()); //set the diffuse color to white
		m_shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), m_specularColor);
		m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
	}

	//m_shader->SetVec3("light[1].ambientColor", { 0.1f, 0.1f, 0.1f }); //set the ambient lighting
	//m_shader->SetVec3("light[1].diffuseColor", m_diffuseColor); //set the diffuse color to white
	//m_shader->SetVec3("light[1].specularColor", m_specularColor);
	//m_shader->SetVec3("light[1].position", m_lightPosition);



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

	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size());

	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());

}