#pragma once

#include "Functions.h"
#include <any>

class FunctionRegistry
{
public:
	//Register a node type with the name and a static create function

	template<typename R>
	static bool Registrate(const std::string& name, FunctionWrapper<R>* CN)
	{
		auto it = Registry<R>().find(name);

		if (it == Registry<R>().end())
		{
			Registry<R>()[name] = CN;

			LOG("Registered Function : %s", name.c_str());

			return true;
		}
		return false;
	}

	template<typename R>
	static std::unordered_map<std::string, FunctionWrapper<R>*>& Registry()
	{
		static std::unordered_map<std::string, FunctionWrapper<R>*> impl;
		return impl;
	}

};


