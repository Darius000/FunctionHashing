#pragma once

#include "Node.h"
#include "Reflection/Reflection.h"

template<typename From, typename To>
class CastTo : public Node
{
public:
	CastTo() 
	{
		m_Name = std::string("Cast ") + rttr::type::get<From>().get_name().to_string() + " to " + rttr::type::get<To>().get_name().to_string();
	}

	virtual const ENodeType GetNodeType() override { return ENodeType::Simple; }

	From m_Input = From();

	To m_Output = To();

	REFLECTABLEV(Node)
};

#define DEFINE_CAST_NODE(From , To, name)\
	REFLECT_INLINE(CastTo<From COMMA To>)\
		{\
			rttr::registration::class_<CastTo<From, To>>(STRINGIFY_MACRO(name))(rttr::metadata(ClassMetaData::Category, "Casts | "))\
				.constructor<>()(rttr::policy::ctor::as_raw_ptr)\
				.property("In", &CastTo<From, To>::m_Input)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Input))\
				.property_readonly("Out", &CastTo<From,To>::m_Output)(rttr::metadata(EPropertyMetaData::PinType, EPinType::Output));\
		}