#pragma once

#include "FunctionNode.h"
#include "INodeCreation.h"

template<typename T>
class MultiplyNode : public FunctionNode , public INodeCreation
{
public:
	MultiplyNode();

	void OnExecute() override;

	DEFINE_NODE_CLASS(MultiplyNode, "Math|", "Multiply")
};

template<>
std::string MultiplyNode<int>::GetFactoryName() { return "Multiply(Int)"; }

template<>
std::string MultiplyNode<float>::GetFactoryName() { return "Multiply(Float)"; }
