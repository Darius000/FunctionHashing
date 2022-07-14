#pragma once

#include "Reflection/Reflection.h"
#include "Node.h"



template<typename Type>
class Literal : public Node
{
public:
	Literal() :m_Value(Type()) {
	
		m_Name = "Literal";
	}

	Literal(const Type& obj) : m_Value(obj) {
		m_Name = "Literal";
	}

	Type m_Value;

	REFLECTABLEV(Node)
};

#define DEFINE_LITERAL(type, name)\
	REFLECT_INLINE(Literal<##type>)\
		{\
			rttr::registration::class_<Literal<##type>>(STRINGIFY_MACRO(name))\
				(rttr::metadata(ClassMetaData::Category, "Literal | "), \
				rttr::metadata(ClassMetaData::Description, STRINGIFY_MACRO(Literal name value)))\
				.constructor<>()(rttr::policy::ctor::as_raw_ptr)\
				.property("Value", &Literal<##type>::m_Value)(rttr::metadata(EPropertyMetaData::PinType, EPinType::InputOutput));\
		}
