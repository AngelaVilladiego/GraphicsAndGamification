#ifndef SHADER_H
#define SHADER_H

#include "StandardIncludes.h"

class Shader
{
public:
	// Constructors / Destructors
	Shader();
	virtual ~Shader() { }

	// Accessors
	GLuint GetProgramId() { return m_programID; }
	GLuint GetAttrVertices() { return m_attrVertices; }
	GLuint GetAttrColor() { return m_attrColor; }
	GLuint GetAttrWorld() { return m_attrWorld; }
	GLuint GetAttrView() { return m_attrView; }
	GLuint GetAttrProjection() { return m_attrProjection; }

	// Methods
	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();


private:
	// Methods
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);

	// Members
	GLuint m_programID; // ID of our shader program
	GLuint m_attrVertices; // Handle for the attribute vertex buffer
	GLuint m_attrColor;
	GLuint m_attrWorld;
	GLuint m_attrView;
	GLuint m_attrProjection;
	GLint m_result = GL_FALSE;
	int m_infoLogLength;
};

#endif // SHADER_H

#pragma once
