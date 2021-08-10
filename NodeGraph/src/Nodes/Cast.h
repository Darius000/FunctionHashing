#pragma once

#include "Node.h"

template<typename From, typename To>
class CastNode : public Node
{
public:
	CastNode()
	{
		m_Color = ImVec4(0.3f, 1.0f, 0.3f, 1.0f);

		AddDataPin<From>("In", ImNodesAttributeType_Input, MakeRef<IPropertyT<From>>());
		AddDataPin<To>("Out", ImNodesAttributeType_Output, MakeRef<IPropertyT<To>>());
	}

	DEFINE_NODE_CLASS(CastNode, "Operators|", "Casting", true);

	static Node* CreateMethod()
	{
		return new CastNode<From, To>();
	}

};


template<>
inline std::string CastNode<int, bool>::GetFactoryName()
{
	return "Int to Bool";
}

template<>
inline std::string CastNode<float, bool>::GetFactoryName()
{
	return "Float to Bool";
}

template<>
inline std::string CastNode<bool, int>::GetFactoryName()
{
	return "Bool to Int";
}

template<>
inline std::string CastNode<bool, float>::GetFactoryName()
{
	return "Bool to Float";
}