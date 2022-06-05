#include "NodeInspector.h"
#include "NodeEditorObject.h"
#include "UI/Inspectors/InspectorRegistry.h"

bool Inspector_Object::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{

    auto data = var.get_value<NodeEditorObject*>();

    rttr::instance obj = var;

    if (!data) return false;

    bool changed = false;

    {
        Property_Layout prop_name("Name");
        rttr::variant var_name = rttr::variant(data->GetName());

        changed = InspectorRegistry::InspectVar(var_name);

        if (changed)
        {
            data->SetName(var_name.to_string());
        }
    }

    ImGui::Separator();

    auto type = obj.get_derived_type();

    for (auto& property : type.get_properties())
    {
        changed |= InspectorRegistry::InspectProperty(property, obj);
    }

    return changed;
}
