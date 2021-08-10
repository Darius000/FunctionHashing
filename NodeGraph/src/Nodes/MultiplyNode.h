#pragma once

#include "Node.h"
#include "INodeCreation.h"

template<typename T>
class MultiplyNode : public Node
{
public:
	MultiplyNode();

	void OnExecute() override;

	DEFINE_NODE_CLASS(MultiplyNode, "Math|", "Multiply", true)

	static Node* CreateMethod() { return new MultiplyNode(); }
};

template<>
std::string MultiplyNode<int>::GetFactoryName() { return "Multiply(Int)"; }

template<>
std::string MultiplyNode<float>::GetFactoryName() { return "Multiply(Float)"; }
