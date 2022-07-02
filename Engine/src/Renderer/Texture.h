#pragma once



#include "RenderObject.h"
#include "Image.h"


class Texture : public RenderObject
{
public:
	virtual ~Texture() = default;

	virtual void Bind(uint32_t slot) const = 0;
	virtual void UnBind() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual int GetChannels() const = 0;
	virtual void SetData(const void* data) = 0;
	virtual void Resize(uint32_t width, uint32_t height) = 0;
	
	static bool IsValidExtension(const char* extension);

	static Ref<Texture> Create(const std::string& filename);
	static Ref<Texture> Create(uint32_t width, uint32_t height, BHive::ImageFormat format, const void* data);

private:


	uint32_t m_Width = 0;

	uint32_t m_Height = 0;

	uint32_t m_Channels = 0;

};
