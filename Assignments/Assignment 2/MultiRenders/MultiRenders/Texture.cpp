#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{
	m_width = 0;
	m_height = 0;
	m_channels = 0;
	m_texture = 0;
}

void Texture::Cleanup()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::LoadTexture(string _fileName)
{
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// Set the texture wrapping/filtering options (on the currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load and generate the texture
	stbi_set_flip_vertically_on_load(true); //flip the image so that 0.0 y on input is bottom side like expected by OpenGL
	GLubyte* data = stbi_load(_fileName.c_str(), &m_width, &m_height, &m_channels, 0);
	M_ASSERT(data != nullptr, _fileName.c_str());

	if (EndsWith(_fileName, ".png"))
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free image data from RAM
	stbi_image_free(data);
}

bool Texture::EndsWith(const std::string& _str, const std::string& _suffix)
{
	if (_str.length() < _suffix.length()) {
		return false;
	}
	return _str.compare(_str.length() - _suffix.length(), _suffix.length(), _suffix) == 0;
}