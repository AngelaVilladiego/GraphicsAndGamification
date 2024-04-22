#include "PostProcessor.h"
#include "WindowController.h"
#include "Shader.h"

PostProcessor::PostProcessor()
{
	m_framebuffer = 0;
	m_textureColorbuffer = 0;
	m_renderBufferObject = 0;
	m_postShader = 0;
	m_vertexBuffer = 0;

	m_frequency = 4.0f;
	m_amplitude = 0.1f;
	m_time = 0.0f;

	m_wireframe = false;
}

PostProcessor::~PostProcessor()
{

}

void PostProcessor::Cleanup()
{
	glDeleteFramebuffers(1, &m_framebuffer);
	glDeleteTextures(1, &m_textureColorbuffer);
	glDeleteRenderbuffers(1, &m_renderBufferObject);
}

void PostProcessor::Create(Shader* _postShader)
{
	m_postShader = _postShader;
	CreateBuffers();
	CreateVertices();
}

void PostProcessor::CreateBuffers()
{
	//framebuffer config
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	// create a color attachment texture
	glGenTextures(1, &m_textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureColorbuffer);
	Resolution r = WindowController::GetInstance().GetResolution();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, r.m_width, r.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorbuffer, 0);

	// create a renderbuffer object for depth and stencil attachment (we wont be sampling these)
	glGenRenderbuffers(1, &m_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, r.m_width, r.m_height); // use a single renderbuffer object for both depth and stencil buffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferObject); // now actually attach it

	// now we created framebuffer and added all attachment, check if its complete
	M_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::CreateVertices()
{
	float vertexData[] = { //vertex attributes for a quad that fills the entire screen in normalized device coordinates
		// positions	//tex coords
		-1.0f, 1.0f,	0.0f, 1.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,
		1.0f, -1.0f,	1.0f, 0.0f,

		-1.0f, 1.0f,	0.0f, 1.0f,
		1.0f, -1.0f,	1.0f, 0.0f,
		1.0f, 1.0f,		1.0f, 1.0f
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PostProcessor::BindVertices()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(m_postShader->GetAttrVertices());
	glVertexAttribPointer(m_postShader->GetAttrVertices(), // The attribute we want to configure
		2,			/*size*/
		GL_FLOAT,	/*type*/
		GL_FALSE,	/*normalized?*/
		4 * sizeof(float),			/*stride*/
		(void*)0);	/*array buffer offset*/

	// 1st attribute buffer : texCoords
	glEnableVertexAttribArray(m_postShader->GetAttrTexCoords());
	glVertexAttribPointer(m_postShader->GetAttrTexCoords(), // The attribute we want to configure
		2,			/*size*/
		GL_FLOAT,	/*type*/
		GL_FALSE,	/*normalized?*/
		4 * sizeof(float),			/*stride*/
		(void*)(2 * sizeof(float)));	/*array buffer offset*/
}

void PostProcessor::Start()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void PostProcessor::End()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // disable depth test so screenspace quad isnt discarded

	glUseProgram(m_postShader->GetProgramId());
	m_postShader->SetTextureSampler("ScreenTexture", GL_TEXTURE0, 0, m_textureColorbuffer);
	m_postShader->SetFloat("Frequency", m_frequency);
	m_postShader->SetFloat("Amplitude", m_amplitude);
	m_postShader->SetFloat("Time", m_time);
	m_postShader->SetInt("TintBlue", m_tintBlue);

	if (m_wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	BindVertices();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(m_postShader->GetAttrVertices());
	glDisableVertexAttribArray(m_postShader->GetAttrTexCoords());
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
}