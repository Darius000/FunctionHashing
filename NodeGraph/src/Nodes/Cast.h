#pragma once

#include "Node.h"

template<typename From, typename To>
class CastTo : public Node
{
public:
	CastTo()
	{
		m_Color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

		AddDataPin("In", PropertyType::Input, MakeRef<IPropertyT<From>>());
		AddDataPin("Out", PropertyType::Output, MakeRef<IPropertyT<To>>());
	}

	DEFINE_NODE_CLASS(CastTo, "Casting|", "Casting", true);

	static Node* CreateMethod()
	{
		return new CastTo<From, To>();
	}

};


template<>
inline std::string CastTo<int, bool>::GetFactoryName()
{
	return "Int to Bool";
}

template<>
inline std::string CastTo<float, bool>::GetFactoryName()
{
	return "Float to Bool";
}

template<>
inline std::string CastTo<bool, int>::GetFactoryName()
{
	return "Bool to Int";
}

template<>
inline std::string CastTo<bool, float>::GetFactoryName()
{
	return "Bool to Float";
}

template<>
inline std::string CastTo<int, float>::GetFactoryName()
{
	return "Int to Float";
}

template<>
inline std::string CastTo<float , int>::GetFactoryName()
{
	return "Float to Int";
}