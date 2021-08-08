#pragma once


#include "FunctionNode.h"
#include "INodeCreation.h"

class CustomEventNode : public FunctionNode, public INodeCreation
{
public:
	CustomEventNode();

	virtual std::string GetTypeName() const override;

	static Node* CreateMethod()
	{
		return new CustomEventNode();
	}

	static std::string GetFactoryName() { return "Event"; }

	virtual void CustomDraw() override;

	virtual void OnExecute() override;
};