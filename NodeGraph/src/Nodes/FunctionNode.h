#pragma once

#include "Functions/Functions.h"
#include "Functions/FunctionRegistry.h"
#include "Node.h"
#include <Engine.h>

#define  TYPENAME "function"

float multiplyFloat(float x, float y) { return x * y; }
int multiplyInt(int x, int y) { return x * y; }

template<typename Func, const char* Name>
class FunctionNode : public Node
{
public:
	using FuncType = FunctionWrapper<Func>;

	FunctionNode(FuncType* function)
	{
		if (GetNodeType() != ENodeType::Simple)
		{
		
		}

		size_t size = FuncType::ArgCount;
		size_t i = 0;
		for (i; i < size; i++)
		{
			using ArgType = FuncType::NthArg<0>;
			
			auto name = i < GetParameterNames().size() ? GetParameterNames()[i] : std::to_string(i);
			
		}
		
		auto name = GetParameterNames().size() > i ? GetParameterNames()[i] : "Return";


		functionwrapper = function;
	}
	
	DEFINE_NODE_CLASS(FunctionNode, "Functions|", "", true);

	virtual const ENodeType GetNodeType() { return ENodeType::Blueprint; }

	virtual std::vector<const char*> GetParameterNames() { return {}; };
	
	static Node* CreateMethod()
	{
		const auto it = FunctionRegistry::Registry<Func>().find(Name);

		return new FunctionNode(it->second);
	}
	
	FuncType* functionwrapper = nullptr;
};

#undef TYPENAME


#define DEFINE_REGISTER_FUNCTION(func, nodetype, ...)\
namespace Register##func\
{\
	constexpr const char name[] = #func;\
	bool registered = FunctionRegistry::Registrate(#func, new FunctionWrapper<decltype(&func)>(&func)); \
};\
template<>\
std::string FunctionNode<decltype(&func), Register##func::name>::GetStaticFactoryName() { return #func; };\
\
template<>\
std::string FunctionNode<decltype(&func), Register##func::name>::GetTypeName()  const override { return #func; };\
\
template<>\
const ENodeType FunctionNode<decltype(&func), Register##func::name>::GetNodeType() override { return ENodeType::##nodetype; };\
\
template<>\
std::vector<const char*> FunctionNode<decltype(&func), Register##func::name>::GetParameterNames() override { return __VA_ARGS__; };\
\
using func##Node = FunctionNode<decltype(&func), Register##func::name>;\
\
DEFINE_REGISTER_NODE(func##Node);

