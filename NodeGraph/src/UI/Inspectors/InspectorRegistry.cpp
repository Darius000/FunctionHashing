#include "InspectorRegistry.h"

rttr::variant get_metadata_empty(const rttr::variant& other)
{
    return rttr::variant();
}

bool InspectorRegistry::InspectVar(rttr::variant& var, bool read_only, const Inspector::meta_getter& get_metadata)
{
    rttr::instance obj = var;

    auto derivedtype = obj.get_derived_type();
    auto type = obj.get_type();

    auto properties = derivedtype.get_properties();

    bool changed = false;

    auto inspector = GetInspector(derivedtype);

    if (!inspector)
    {
        inspector = GetInspector(type);
    }

    if (inspector)
    {
        changed |= inspector->Inspect(var, read_only, get_metadata);
    }

    if (!inspector)
    {
        if (properties.empty())
        {

        }
        else
        {
            for (auto& property : properties)
            {
                changed |= InspectProperty(property, obj);
            }
        }
    }

    return changed;
}

bool InspectorRegistry::InspectProperty(const rttr::property& property, rttr::instance& obj)
{
    bool prop_changed = false;
    auto prop_var = property.get_value(obj);
    bool is_readonly = property.is_readonly();
    bool is_array = prop_var.is_sequential_container();
    bool is_associative_container = prop_var.is_associative_container();
    
    bool is_enum = property.is_enumeration();

    rttr::instance prop_object = prop_var;

    bool has_inspector = !!InspectorRegistry::GetInspector(prop_object.get_derived_type());

    bool details = !has_inspector && !is_enum;

    Property_Layout layout(property);
    bool open = true;

    if (details)
    {
        ImGui::AlignTextToFramePadding();
        open = ImGui::TreeNode("details");
    }

    if (open)
    {
        auto get_meta = [&property](const rttr::variant& name)->rttr::variant {
            return property.get_metadata(name);
        };

        if (is_array)
        {
            InspectorRegistry::InspectArray(prop_var, is_readonly, get_meta);
        }
        else if (is_associative_container)
        {
            InspectorRegistry::InspectAssociativeContainter(prop_var, is_readonly);
        }
        else if (is_enum)
        {

        }
        else
        {
            prop_changed |= InspectorRegistry::InspectVar(prop_var, is_readonly, get_meta);
        }

        if (details && open)
        {
            ImGui::TreePop();
        }
    }

    if (prop_changed && !is_readonly)
    {
        property.set_value(obj, prop_var);
    }

    return prop_changed;
}

bool InspectorRegistry::InspectArray(rttr::variant& var, bool read_only, const Inspector::meta_getter& get_metadata)
{
    auto view = var.create_sequential_view();
    auto size = view.get_size();
    bool changed = false;
    auto int_size = static_cast<int>(size);

    for (std::size_t i = 0; i < size; i++)
    {
        auto value = view.get_value(i).extract_wrapped_value();
        std::string element = "Element ";
        element += std::to_string(i);

        Property_Layout layout(element.data());

        changed |= InspectVar(value, read_only, get_metadata);

        if (changed)
        {
            view.set_value(i, value);
        }
    }

    if (view.is_dynamic())
    {
        Property_Layout layout("Size");

        if (!read_only)
        {
            if (ImGui::Button("-"))
            {
                int_size = std::clamp(--int_size, 0, int_size);
                size = static_cast<std::size_t>(int_size);
                changed |= view.set_size(size);
            }

            ImGui::SameLine();
            
            if(ImGui::Button("+"))
            {
                int_size = std::clamp(++int_size, 0, int_size);
                size = static_cast<std::size_t>(int_size);
                changed |= view.set_size(size);
            }
        }
        else
        {
            ImGui::AlignTextToFramePadding();
            ImGui::TextUnformatted(std::to_string(int_size).c_str());
        }
    }

    return changed;
}

bool InspectorRegistry::InspectAssociativeContainter(rttr::variant& var, bool read_only)
{
    
    bool changed = false;

    auto associative_view = var.create_associative_view();

    for (auto item : associative_view)
    {
        auto first = item.first.extract_wrapped_value();
        auto second = item.second.extract_wrapped_value();

        
        Property_Layout layout("Element");
        changed |= InspectVar(first, read_only);

        Property_Layout layoutv("Value");
        changed |= InspectVar(second, read_only);

        if (changed)
        {
            associative_view.insert(first, second);
        }
    }

    return changed;
}
