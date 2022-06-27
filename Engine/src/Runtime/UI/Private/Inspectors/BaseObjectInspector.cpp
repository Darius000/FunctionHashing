#include "PCH.h"
#include "BaseObjectInspector.h"
#include "BaseObject.h"
#include "InspectorRegistry.h"
#include "imgui.h"

bool Inspector_BaseObject::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{

    auto data = var.get_value<BaseObject*>();

    rttr::instance obj = var;

    if (!data) return false;

    bool changed = false;

    auto type = obj.get_derived_type();

    for (auto& property : type.get_properties())
    {
        changed |= InspectorRegistry::InspectProperty(property, obj);
    }

    return changed;
}
