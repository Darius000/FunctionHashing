#include "PCH.h"
#include "MultiplyNode.h"

template<typename T>
MultiplyNode<T>::MultiplyNode()
{

	AddDataPin<T>("A", ImNodesAttributeType_Input, MakeRef<IPropertyT<T>>());
	AddDataPin<T>("B", ImNodesAttributeType_Input, MakeRef<IPropertyT<T>>());
	AddDataPin<T>("Out", ImNodesAttributeType_Output, MakeRef<IPropertyT<T>>());
	AddExecutionPin(ImNodesAttributeType_Input);
	AddExecutionPin(ImNodesAttributeType_Output);
}

template<typename T>
void MultiplyNode<T>::OnExecute()
{
	
}

using MultiplyNodeInt = MultiplyNode<int>;
using MultiplyNodeFloat = MultiplyNode<float>;


REGISTER_NODE(MultiplyNodeInt, "Math |MultiplyInt", "Multiply node for int")
REGISTER_NODE(MultiplyNodeFloat, "Math |MultiplyFloat", "Multiply node for floats")
