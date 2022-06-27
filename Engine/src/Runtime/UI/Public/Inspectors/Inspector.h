#pragma once

#include <Core/Reflection/Reflection.h>

namespace ImGui
{

};

struct Inspector
{
	using meta_getter = std::function<rttr::variant(const rttr::variant&)>;

	virtual ~Inspector() = default;

	virtual bool Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata) = 0;
	
	RTTR_REGISTRATION_FRIEND
	RTTR_ENABLE()
};

struct Property_Layout
{
	Property_Layout(const rttr::property& prop, bool columns = true);

	Property_Layout(std::string_view name, bool columns = true);

	Property_Layout(std::string_view name, std::string_view tooltip, bool columns = true);

	~Property_Layout();

	std::string m_Name;
};

REFLECT_INLINE(Inspector)
{
	auto r = rttr::registration::class_<Inspector>("Inspector");
}

#define INSPECTOR_REFLECT(inspector_type, inspected_type)\
		REFLECT_INLINE(inspector_type)\
		{\
			auto r = rttr::registration::class_<inspector_type>(#inspector_type)\
			(rttr::metadata("inspected_type", rttr::type::get<inspected_type>()))\
			.constructor<>()(rttr::policy::ctor::as_std_shared_ptr);\
		}	

#define DELARE_INSPECTOR(inspector_type, inspected_type)\
	struct inspector_type : public Inspector\
	{\
		RTTR_ENABLE(Inspector)\
		bool Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata) override;\
	};\
	INSPECTOR_REFLECT(inspector_type, inspected_type)