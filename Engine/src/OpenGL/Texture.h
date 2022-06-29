#pragma once



#include <glad/glad.h>

struct FPixelData
{
	void* m_Data = nullptr;

	GLenum m_InternalFormat;

	GLenum m_DataFormat;
};

class Texture
{
public:
	Texture(const std::string& file);

	void Bind(uint32_t slot) const;

	int GetWidth() const {return m_Width; }
	int GetHeight() const { return m_Height; }
	int GetChannels() const { return m_Channels; }
	
	uint32_t GetRenderID() { return m_RendererID; }

	bool IsValid() { return m_Data.m_Data != nullptr; }

	static bool IsValidExtension(const char* extension);

private:

	uint32_t m_Width = 0;

	uint32_t m_Height = 0;

	uint32_t m_Channels = 0;

	FPixelData m_Data;

	bool b_HasAlphaChannel = false;

	uint32_t m_RendererID = -1;
};
