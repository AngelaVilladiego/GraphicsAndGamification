#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"
#include "OBJ_Loader.h"

class Shader;

class Mesh
{
public:
	// Constructors / Destructors
	Mesh();
	virtual ~Mesh();

	//Accessors
	void SetPosition(glm::vec3 _position) { m_position = _position; }
	void SetRotation(glm::vec3 _rotation) { m_rotation = _rotation; }
	glm::vec3 GetPosition() { return m_position; }
	void SetScale(glm::vec3 _scale) { m_scale = _scale; }
	void SetColor(glm::vec3 _color) { m_color = _color; }
	glm::vec3 GetColor() { return m_color; }
	void SetCameraPosition(glm::vec3 _cameraPosition) { m_cameraPosition = _cameraPosition; }
	void SetSpecularStrength(float _specularStrength) { m_specularStrength = _specularStrength; }
	void SetSpecularColor(glm::vec3 _specularColor) { m_specularColor = _specularColor; }
	GLuint GetShaderProgram();

	// Methods
	void Create(Shader* _shader, string _file);
	void Cleanup();
	void Render(glm::mat4 _pv);
	void CalculateTransform();

	// Members
	static vector<Mesh> Lights;

private:
	// Methods
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();
	string Concat(string _s1, int _index, string _s2);
	string RemoveFolder(string _map);

	// Members
	Shader* m_shader;
	Texture m_textureDiffuse;
	Texture m_textureSpecular;
	Texture m_textureNormal;
	GLuint m_vertexBuffer; // GPU buffer
	std::vector<GLfloat> m_vertexData; // Store vertex data in RAM
	bool m_enableNormalMap;

	// Transform
	glm::mat4 m_world;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::vec3 m_color;
	glm::vec3 m_cameraPosition;

	// LIGHT
	glm::vec3 m_lightPosition;
	float m_specularStrength;
	glm::vec3 m_specularColor;
	glm::vec3 m_diffuseColor;

};

#endif // MESH_H

