#pragma once

#include "Functions/Functions.h"
#include "Functions/FunctionRegistry.h"
#include "Node.h"
#include <Engine.h>

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
	
	virtual const ENodeType GetNodeType() { return ENodeType::Blueprint; }

	virtual std::vector<const char*> GetParameterNames() { return {}; };
	
	
	FuncType* functionwrapper = nullptr;
};