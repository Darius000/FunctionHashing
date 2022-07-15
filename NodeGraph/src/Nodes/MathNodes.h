#pragma once
#include "Node.h"

template<typename T>
class Multiply : public Node
{
public:

	Multiply() : m_A(), m_B() 
	{
	
		m_Name = "X";
	}

	T m_A;

	T m_B;

	virtual T GetValue() { return m_A * m_B;  }

	virtual ENodeType GetNodeType() { return ENodeType::Compact; }

	REFLECTABLEV(Node)
};

#define DEFINE_MULTIPLYNODE(type)\
	REFLECT_INLINE(Multiply<type>)\
	{\
		rttr::registration::class_<Multiply<type>>(STRINGIFY_MACRO(Multiply type))(rttr::metadata(ClassMetaData::Category, "Math | "))\
			.constructor<>()(rttr::policy::ctor::as_raw_ptr)\
			.property("A", &Multiply<type>::m_A)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input))\
			.property("B", &Multiply<type>::m_B)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input))\
			.property_readonly("Out", &Multiply<type>::GetValue)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output));\
	}