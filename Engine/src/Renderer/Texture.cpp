#include "PCH.h"
#include "Texture.h"
#include "OpenGL/OpenGLTexture.h"
#include "RendererAPI.h"
#include<string>
#include <vector>

bool Texture::IsValidExtension(const char* extension)
{
	// // O: insert return statement here
	std::vector<std::string> extensions = { ".png", ".jpeg", ".jpg", ".targa", ".tiff", ".tif" };

	bool found = std::find(extensions.begin(), extensions.end(), extension) != extensions.end();
	return found;
}

Ref<Texture> Texture::Create(const std::string& filename)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::Opengl:
		return MakeRef<OpenGLTexture>(filename);
	default:
		break;
	}

	return nullptr;
}

Ref<Texture> Texture::Create(uint32_t width, uint32_t height, BHive::ImageFormat format, const void* data)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::Opengl:
		return MakeRef<OpenGLTexture>(width, height, format, data);
	default:
		break;
	}

	return nullptr;
}
