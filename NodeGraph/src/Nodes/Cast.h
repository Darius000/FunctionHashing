#pragma once

#include "Node.h"

#define TYPENAME "Cast"

template<typename From, typename To>
class CastTo : public Node
{
public:
	CastTo()
	{

		AddDataPin("In", ed::PinKind::Input, MakeRef<IPropertyT<From>>());
		AddDataPin("Out", ed::PinKind::Output, MakeRef<IPropertyT<To>>());
	}

	DEFINE_NODE_CLASS(CastTo, "Casting|", "Casting", true);

	virtual const ENodeType GetNodeType() override { return ENodeType::Simple; }

	static Node* CreateMethod()
	{
		return new CastTo<From, To>();
	}

};

#undef TYPENAME


template<>
inline std::string CastTo<int, bool>::GetStaticFactoryName()
{
	return "Int to Bool";
}

template<>
inline std::string CastTo<float, bool>::GetStaticFactoryName()
{
	return "Float to Bool";
}

template<>
inline std::string CastTo<bool, int>::GetStaticFactoryName()
{
	return "Bool to Int";
}

template<>
inline std::string CastTo<bool, float>::GetStaticFactoryName()
{
	return "Bool to Float";
}

template<>
inline std::string CastTo<int, float>::GetStaticFactoryName()
{
	return "Int to Float";
}

template<>
inline std::string CastTo<float , int>::GetStaticFactoryName()
{
	return "Float to Int";
}