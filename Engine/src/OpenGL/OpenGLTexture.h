#pragma once



#include "Renderer/Texture.h"

class OpenGLTexture : public Texture
{
public:
	OpenGLTexture(const std::string& file);
	OpenGLTexture(uint32_t width, uint32_t height, BHive::ImageFormat format ,const void* data);

	void Bind(uint32_t slot) const override;
	void UnBind() const override;

	void SetData(const void* data) override;
	void Resize(uint32_t width, uint32_t height) override;

	int GetWidth() const override {return m_Width; }
	int GetHeight() const override { return m_Height; }
	int GetChannels() const override { return m_Channels; }

private:
	void InValidate(const void* data);

	uint32_t m_Width = 0;

	uint32_t m_Height = 0;

	uint32_t m_Channels = 0;

	BHive::ImageFormat m_Format = BHive::ImageFormat::None;
};
