#include "PCH.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& file)
{
	int width, height, channels;
	m_Data.m_Data = stbi_load(file.c_str(), &width, &height, &channels, 0);

	if (!m_Data.m_Data) return;

	m_Width = width;
	m_Height = height;
	m_Channels = channels;
	
	if (m_Channels == 4)
	{
		m_Data.m_InternalFormat = GL_RGBA8;
		m_Data.m_DataFormat = GL_RGBA;
		b_HasAlphaChannel = true;
	}
	else if (m_Channels == 3)
	{
		m_Data.m_InternalFormat = GL_RGB8;
		m_Data.m_DataFormat = GL_RGB;
		b_HasAlphaChannel = false;
	}
	else if (m_Channels == 1)
	{
		m_Data.m_InternalFormat = GL_R8;
		m_Data.m_DataFormat = GL_RED;
		b_HasAlphaChannel = false;
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

	glTextureStorage2D(m_RendererID, 1, m_Data.m_InternalFormat, m_Width, m_Height);

	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_Data.m_DataFormat, 
		GL_UNSIGNED_BYTE, m_Data.m_Data);
	glGenerateMipmap(m_RendererID);
}

bool Texture::IsValidExtension(const char* extension)
{
	// // O: insert return statement here
	std::vector<std::string> extensions = { ".png", ".jpeg", ".jpg", ".targa", ".tiff", ".tif" };

	bool found = std::find(extensions.begin(), extensions.end(), extension) != extensions.end();
	return found;
}
