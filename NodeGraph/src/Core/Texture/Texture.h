#pragma once



#include <glad/glad.h>

struct FPixelData
{
	void* m_Data;

	GLenum m_InternalFormat;

	GLenum m_DataFormat;
};

class Texture
{
public:
	Texture(const std::string& file);

	int GetWidth() const {return m_Width; }
	int GetHeight() const { return m_Height; }
	int GetChannels() const { return m_Channels; }
	
	uintptr_t GetRenderID() { return m_RendererID; }

private:

	int m_Width;

	int m_Height;

	int m_Channels;

	FPixelData m_Data;

	bool b_HasAlphaChannel;

	unsigned int m_RendererID;
};