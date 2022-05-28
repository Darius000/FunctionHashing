#pragma once

#include <Engine.h>


class DataTypeRegistry
{
public:
	using PropertyCreateMethod = struct IProperty*(*)();

	inline static bool Registrate(const std::string& name, PropertyCreateMethod CN)
	{
		auto it = Registry().find(name);

		if (it == Registry().end())
		{
			Registry()[name] = CN;

			RegisteredTypes().push_back(name);

			//std::cout <<  << name << "\n";
			LOG("Registered Data Type: %s", name.c_str());

			return true;
		}

		return false;
	}

	inline static struct IProperty* Instaniate(const std::string& name)
	{
		auto it = Registry().find(name);
		return it == Registry().end() ? nullptr : it->second();
	}

	inline static std::vector<std::string>& RegisteredTypes()
	{
		static std::vector<std::string> impl;
		return impl;
	}

	inline static std::unordered_map<std::string, PropertyCreateMethod>& Registry()
	{
		static std::unordered_map<std::string, PropertyCreateMethod> impl;
		return impl;
	}

};