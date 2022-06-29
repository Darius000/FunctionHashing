#pragma once

enum class ShaderDataType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static uint32_t ShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::None:
		break;
	case ShaderDataType::Float:
		return 4 ;
	case ShaderDataType::Float2:
		return 4 * 2;
	case ShaderDataType::Float3:
		return 4 * 3;
	case ShaderDataType::Float4:
		return 4 * 4;
	case ShaderDataType::Mat3:
		return 4 * 3 * 3;
	case ShaderDataType::Mat4:
		return 4 * 4 * 4;
	case ShaderDataType::Int:
		return 4;
	case ShaderDataType::Int2:
		return 4 * 2;
	case ShaderDataType::Int3:
		return 4 * 3;
	case ShaderDataType::Int4:
		return 4 * 4;
	case ShaderDataType::Bool:
		return 1;
	default:
		break;
	}

	return 0;
}

struct BufferElement
{
	std::string m_Name;
	ShaderDataType m_Type;
	uint32_t m_Size;
	uint64_t m_Offset;
	bool m_Normalized;

	BufferElement() = default;

	BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
		:m_Name(name), m_Type(type), m_Size(ShaderDataTypeSize(type)), m_Offset(0), m_Normalized(normalized)
	{

	}

	uint32_t GetComponentCount() const
	{
		switch (m_Type)
		{
		case ShaderDataType::Float:
			return 1;
		case ShaderDataType::Float2:
			return 2;
		case ShaderDataType::Float3:
			return 3;
		case ShaderDataType::Float4:
			return 4;
		case ShaderDataType::Mat3:
			return 3;
		case ShaderDataType::Mat4:
			return 4;
		case ShaderDataType::Int:
			return 1;
		case ShaderDataType::Int2:
			return 2;
		case ShaderDataType::Int3:
			return 3;
		case ShaderDataType::Int4:
			return 4;
		case ShaderDataType::Bool:
			return 1;
		default:
			break;
		}


		return 0;
	}

};

class BufferLayout
{
public:
	using Elements = std::vector<BufferElement>;
	using ElementsIterator = Elements::iterator;
	using ElementsConstIterator = Elements::const_iterator;

	BufferLayout(){}

	BufferLayout(std::initializer_list<BufferElement> elements)
		:m_Elements(elements) 
	{
		CalculateOffsetAndStride();
	}

	uint32_t GetStride() const { return m_Stride; }
	const Elements& GetElements() const { return m_Elements; }

	ElementsIterator begin() { return m_Elements.begin(); }
	ElementsIterator end() { return m_Elements.end(); }
	ElementsConstIterator begin() const { return m_Elements.cbegin(); }
	ElementsConstIterator end() const { return m_Elements.cend(); }

private:

	void CalculateOffsetAndStride()
	{
		uint64_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.m_Offset = offset;
			offset += element.m_Size;
			m_Stride += element.m_Size;
		}
	}

	Elements m_Elements;
	uint32_t m_Stride = 0;
};