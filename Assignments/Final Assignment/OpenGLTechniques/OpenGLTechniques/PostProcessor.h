#ifndef POSTROCESSOR_H
#define POSTPROCESSOR_H

#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class PostProcessor
{
public:
	PostProcessor();
	virtual ~PostProcessor();

	void Create(Shader* _postShader);
	void Cleanup();
	void Start();
	void End();

	void SetFrequency(float _frequency) { m_frequency = _frequency; }
	void SetAmplitude(float _amplitude) { m_amplitude = _amplitude; }
	void SetTime(float _time) { m_time = _time; }
	void SetWireframeMode(bool _wireframe) { m_wireframe = _wireframe; }

private:
	GLuint m_framebuffer;
	GLuint m_textureColorbuffer;
	GLuint m_renderBufferObject;
	GLuint m_vertexBuffer;
	Shader* m_postShader;

	float m_frequency;
	float m_amplitude;
	float m_time;

	bool m_wireframe;

	void CreateVertices();
	void CreateBuffers();
	void BindVertices();
};

#endif // POSTPROCESSOR_H