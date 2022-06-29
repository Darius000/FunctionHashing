#pragma once

#include "Inspector.h"


rttr::variant get_metadata_empty(const rttr::variant& other);

struct InspectorRegistry
{
	InspectorRegistry()
	{
		auto inspector_types = rttr::type::get<Inspector>().get_derived_classes();

		for (auto& inspector_type : inspector_types)
		{
			auto inspected_var = inspector_type.get_metadata("inspected_type");
			if (inspected_var)
			{
				auto inspected_type = inspected_var.get_value<rttr::type>();
				auto inspector_var = inspector_type.create();
				if (inspector_var)
				{
					type_map[inspected_type] = inspector_var.get_value<std::shared_ptr<Inspector>>();
				}
			}
		}
	}

	static std::shared_ptr<Inspector> GetInspector(rttr::type type)
	{
		static InspectorRegistry registry;

		if (registry.type_map.find(type) != registry.type_map.end())
		{
			return registry.type_map[type];
		}

		return nullptr;
	}

	static bool InspectVar(rttr::variant& var, bool read_only = false, const Inspector::meta_getter& get_metadata = get_metadata_empty);

	static bool InspectProperty(const rttr::property& property, rttr::instance& obj);

	static bool InspectArray(rttr::variant& var, bool read_only = false, const Inspector::meta_getter& get_metadata = get_metadata_empty);

	static bool InspectAssociativeContainter(rttr::variant& var, bool read_only = false);

	std::unordered_map<rttr::type, std::shared_ptr<Inspector>> type_map;
};

