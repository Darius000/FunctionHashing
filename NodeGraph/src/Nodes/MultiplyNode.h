#pragma once

#include "FunctionNode.h"
#include "INodeCreation.h"

template<typename T>
class MultiplyNode : public FunctionNode , public INodeCreation
{
public:
	MultiplyNode();

	void OnExecute() override;

	virtual std::string GetTypeName() const override { return "Multiply";}

	static Node* CreateMethod()
	{
		return new MultiplyNode();
	}

	static std::string GetFactoryName();
};

template<>
std::string MultiplyNode<int>::GetFactoryName() { return "MultiplyInt"; }

template<>
std::string MultiplyNode<float>::GetFactoryName() { return "MultiplyFloat"; }
