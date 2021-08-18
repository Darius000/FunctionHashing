#pragma once

#include "Core/Core.h"
#include "DataTypes/Property.h"
#include "Nodes/INodeCreation.h"
#include "Core/Category/Category.h"
#include <any>

class NodeRegistry
{
	using NodePtrT = class Node*;

public:
	//Register a node type with the name and a static create function
	
	template<typename R, typename...Args>
	static bool Registrate(const std::string& name, const NodeCreationMethod<R, Args...>& CN)
	{
		auto it = Registry().find(name);

		if (it == Registry().end())
		{
			Registry()[name] = CN.m_CreateFunc;

			if (CN.m_Category.size() > 0 && CN.m_PlaceInCategories)
				NodeCatgeories::AddCategory(CN.m_Category, CN.m_Description);

			LOG("Registered Node Class: %s", name.c_str());

			return true;
		}
		return false;
	}

	
	template<typename...Args>
	static NodePtrT Instaniate(const std::string& name, Args ... args)
	{
		using CreaterTraitT = NodePtrT(*)(Args...);

		const auto it = Registry().find(name);

		if (it == Registry().end())
		{
			return nullptr;
		}
		try
		{
			auto creater = std::any_cast<CreaterTraitT>(it->second);
			return creater(std::forward<Args>(args)...);
		}
		catch (const std::bad_any_cast& e)
		{
			std::cout << e.what() << "\n";
		}
	
		return nullptr;
	}


	static std::unordered_map<std::string, std::any>& Registry()
	{
		static std::unordered_map<std::string, std::any> impl;
		return impl;
	}

};
