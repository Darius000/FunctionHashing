#pragma once

#include "Core/Core.h"
#include "DataTypes/DataTypeEnum.h"
#include "DataTypes/Property.h"
#include "Nodes/INodeCreation.h"
#include "Category/Category.h"

enum class EVariableNodeType : uint8_t
{
	Get,
	Set,
	Max
};


template<>
std::vector<std::string> EnumStrings<EVariableNodeType>::Data = {
		"Get", "Set"
};

template<typename ...Args>
class NodeRegistry
{
public:
	//Register a node type with the name and a static create function
	
	static bool Registrate(const std::string& name, NodeCreationMethod<Args...> CN)
	{
		auto it = Registry().find(name);

		if (it == Registry().end())
		{
			Registry()[name] = CN;

			if(CN.m_Category.size() > 0)
				NodeCatgeories::AddCategory(CN.m_Category, CN.m_Description);

			std::cout << "Registered Node Class: " << name << "\n";
			return true;
		}
		
		return false;
	}

	

	static Node* Instaniate(const std::string& name, Args ... args)
	{
		auto it = Registry().find(name);
		return it == Registry().end() ? nullptr : it->second.m_CreateFunc(args...);
	}


	static std::unordered_map<std::string, NodeCreationMethod<Args...>>& Registry()
	{
		static std::unordered_map<std::string, NodeCreationMethod<Args...>> impl;
		return impl;
	}

};
