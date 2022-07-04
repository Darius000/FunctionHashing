#include "PCH.h"
#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>

namespace Utils
{
	static uint32_t ImageFormatToInternalImageFormat(BHive::ImageFormat format)
	{
		switch (format)
		{
		case BHive::ImageFormat::None:
			break;
		case BHive::ImageFormat::RGBA:
			return GL_RGBA8;
		case BHive::ImageFormat::RGBA32F:
			return GL_RGBA8;
		default:
			break;
		}

		return 0;
	}

	static uint32_t ImageFormatToOpenGLFormat(BHive::ImageFormat format)
	{
		switch (format)
		{
		case BHive::ImageFormat::None:
			break;
		case BHive::ImageFormat::RGBA:
			return GL_RGBA;
		case BHive::ImageFormat::RGBA32F:
			return GL_RGBA32F;
		default:
			break;
		}

		return 0;
	}

	static uint32_t BytesPerPixel(BHive::ImageFormat format)
	{
		switch (format)
		{
		case BHive::ImageFormat::None:
			break;
		case BHive::ImageFormat::RGBA:
			return 4;
		case BHive::ImageFormat::RGBA32F:
			return 16;
		default:
			break;
		}

		return 0;
	}
}

OpenGLTexture::OpenGLTexture(const std::string& filename)
{
	uint8_t* data = nullptr;

	stbi_set_flip_vertically_on_load(1);

	int width, height, channels;

	if (stbi_is_hdr(filename.c_str()))
	{
		data = (uint8_t*)stbi_load(filename.c_str(), &width, &height, &channels, 4);

		m_Format = BHive::ImageFormat::RGBA32F;
	}
	else
	{
		data = stbi_load(filename.c_str(), &width, &height, &channels, 4);

		m_Format = BHive::ImageFormat::RGBA;
	}

	m_Width = width;
	m_Height = height;
	m_Channels = channels;


	InValidate(data);

	STBI_FREE(data);
}

OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height, BHive::ImageFormat format, const void* data)
	:m_Width(width), m_Height(height), m_Format(format)
{

	InValidate(data);

	if (data)
		SetData(data);
}


void  OpenGLTexture::Bind(uint32_t slot) const
{
	glBindTextureUnit(slot, m_RendererID);
}

void OpenGLTexture::UnBind() const
{
	
}

void OpenGLTexture::SetData(const void* data)
{
	glTexImage2D(GL_TEXTURE_2D, 0, Utils::ImageFormatToInternalImageFormat(m_Format), m_Width, m_Height, 0,
		Utils::ImageFormatToOpenGLFormat(m_Format), GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture::Resize(uint32_t width, uint32_t height)
{
	if (m_Width == width && m_Height == height) return;

	m_Width = width;
	m_Height = height;

	glTexImage2D(GL_TEXTURE_2D, 0, Utils::ImageFormatToInternalImageFormat(m_Format), m_Width, m_Height, 0,
		Utils::ImageFormatToOpenGLFormat(m_Format), GL_UNSIGNED_BYTE, nullptr);
}

void OpenGLTexture::InValidate(const void* data)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

	glTextureStorage2D(m_RendererID, 1, Utils::ImageFormatToInternalImageFormat(m_Format), m_Width, m_Height);

	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, Utils::ImageFormatToOpenGLFormat(m_Format),
		GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(m_RendererID);
}



