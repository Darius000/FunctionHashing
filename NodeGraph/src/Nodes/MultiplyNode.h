#pragma once

#include "Node.h"
#include "INodeCreation.h"

template<typename T>
class MultiplyNode : public Node
{
public:
	MultiplyNode()
	{
		AddDataPin("A", PropertyType::Input, MakeRef<IPropertyT<T>>());
		AddDataPin("B", PropertyType::Input, MakeRef<IPropertyT<T>>());
		AddDataPin("Out", PropertyType::Output, MakeRef<IPropertyT<T>>());
		AddExecutionPin(ImNodesAttributeType_Input);
		AddExecutionPin(ImNodesAttributeType_Output);
	}

	void OnExecute() override
	{
		auto a = GetParameter("A");
		auto b = GetParameter("B");
		auto c = GetParameter("Out");

		typename IPropertyT<T>* aprop = Cast<IPropertyT<T>>(a->m_Property.get());
		typename IPropertyT<T>* bprop = Cast<IPropertyT<T>>(b->m_Property.get());
		typename IPropertyT<T>* cprop = Cast<IPropertyT<T>>(c->m_Property.get());
		if (aprop && bprop && cprop)
		{
			T aref = aprop->GetConstRef();
			T bref = bprop->GetConstRef();
			cprop->Set(aref * bref);
			std::cout << cprop->GetConstRef() << "\n";
		}
	}

	DEFINE_NODE_CLASS(MultiplyNode, "Math|", "Multiply", true)

	static Node* CreateMethod() { return new MultiplyNode(); }
};

template<>
std::string MultiplyNode<int>::GetFactoryName() { return "Multiply(Int)"; }

template<>
std::string MultiplyNode<float>::GetFactoryName() { return "Multiply(Float)"; }
