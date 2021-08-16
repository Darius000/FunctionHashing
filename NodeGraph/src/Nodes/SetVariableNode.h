#pragma once

#include "Node.h"
#include "VariableNodeInterface/VariableNodeInterface.h"

#define TYPENAME "Set"

template<typename T>
class SetVariableNode : public VariableNodeInterface<T>
{
public:
	SetVariableNode(Ref<IProperty> prop)
		:VariableNodeInterface(prop)
	{
		
		AddExecutionPin("", ed::PinKind::Input);
		AddExecutionPin("", ed::PinKind::Output);
		auto pinIn = AddDataPin("In", ed::PinKind::Input, prop);
		auto pinOut = AddDataPin("Out", ed::PinKind::Output, prop);

		prop->OnDestroyed.AddBinding([this, pinIn, pinOut](NodeEditorObject* obj) {
				pinIn->m_Property = nullptr;
				pinOut->m_Property = nullptr;
		});
	}

	virtual void OnExecute() override 
	{
	
	};

	DEFINE_NODE_CLASS(SetVariableNode,"", "", false)

	static Node* CreateMethod(Ref<IProperty> prop) { return new SetVariableNode(prop); }


};

#undef TYPENAME

template<>
std::string SetVariableNode<int>::GetFactoryName()
{
	return "Setint";
}


template<>
std::string SetVariableNode<float>::GetFactoryName()
{
	return "Setfloat";
}


template<>
std::string SetVariableNode<bool>::GetFactoryName()
{
	return "Setbool";
}