#pragma once

#include "Node.h"
#include "INodeCreation.h"

#define TYPENAME "Multiply"

template<typename T>
class MultiplyNode : public Node
{
public:
	MultiplyNode()
	{
		AddExecutionPin("", ed::PinKind::Input);
		AddExecutionPin("", ed::PinKind::Output);
		AddDataPin("A", ed::PinKind::Input,  MakeRef<IPropertyT<T>>());
		AddDataPin("B", ed::PinKind::Input,  MakeRef<IPropertyT<T>>());
		AddDataPin("Out", ed::PinKind::Output,  MakeRef<IPropertyT<T>>());
	}

	void OnExecute() override
	{
		/*auto a = GetPin("A");
		auto b = GetPin("B");
		auto c = GetPin("Out");

		typename IPropertyT<T>* aprop = Cast<IPropertyT<T>>(a->m_Property.get());
		typename IPropertyT<T>* bprop = Cast<IPropertyT<T>>(b->m_Property.get());
		typename IPropertyT<T>* cprop = Cast<IPropertyT<T>>(c->m_Property.get());
		if (aprop && bprop && cprop)
		{
			T aref = aprop->GetConstRef();
			T bref = bprop->GetConstRef();
			cprop->Set(aref * bref);
			std::cout << cprop->GetConstRef() << "\n";
		}*/
	}

	DEFINE_NODE_CLASS(MultiplyNode, "Math|", "Multiply", true)

	static Node* CreateMethod() { return new MultiplyNode(); }
};

#undef TYPENAME

template<>
std::string MultiplyNode<int>::GetFactoryName() { return "Multiply(Int)"; }

template<>
std::string MultiplyNode<float>::GetFactoryName() { return "Multiply(Float)"; }
