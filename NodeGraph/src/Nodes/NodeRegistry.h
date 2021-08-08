#pragma once

#include "Core/Core.h"
#include "DataTypes/DataTypeEnum.h"
#include "DataTypes/Property.h"
#include "INodeCreation.h"
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

template<typename T>
struct VariableNodeCreation
{
	using Type = T;

	using Create_Variable_FN = Scope<class Node>(*)(IProperty*);

	VariableNodeCreation(){}
	VariableNodeCreation(Create_Variable_FN get, 
		Create_Variable_FN set)
	{
		Functions[EVariableNodeType::Get] = get;
		Functions[EVariableNodeType::Set] = set;
	}

	std::unordered_map<TEnum<EVariableNodeType>, Create_Variable_FN> Functions;
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
				AddCategory(CN.m_Category, CN.m_Description);

			std::cout << "Registered Node Class: " << name << "\n";
			return true;
		}
		
		return false;
	}

	inline static void AddCategory(const std::string& name, const std::string& description)
	{
		CategoryList* currentCatgory  = &NodeTypes();
		std::vector<std::string> categories;
		SplitString(name, "|", categories);

		size_t numCategories = categories.size();
		for (size_t i = 0; i < numCategories; i++)
		{
			auto& catname = categories[i];
			if (i != numCategories - 1)
			{
				//check if category already exists if not create a new one
				bool exists = currentCatgory->m_SubCategories.find(catname) != currentCatgory->m_SubCategories.end();
				if (exists)
				{
					currentCatgory = &*currentCatgory->m_SubCategories[catname];
				}
				else
				{
					CategoryList* newlist = new CategoryList();
					currentCatgory->m_SubCategories[catname] = Scope<CategoryList>(newlist);
					currentCatgory = newlist;
				}	
			}
			else
			{
				currentCatgory->m_Leafs.push_back(catname);
			}
		}
	}

	static Node* Instaniate(const std::string& name, Args ... args)
	{
		auto it = Registry().find(name);
		return it == Registry().end() ? nullptr : it->second.m_CreateFunc(args...);
	}

	static CategoryList& NodeTypes()
	{
		static CategoryList impl;
		return impl;
	}

	static std::unordered_map<std::string, NodeCreationMethod<Args...>>& Registry()
	{
		static std::unordered_map<std::string, NodeCreationMethod<Args...>> impl;
		return impl;
	}

};
