#include "PCH.h"
#include "GlmInspectors.h"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui_internal.h"

namespace details
{
    const std::string format = "%.2f";
}

bool Inspector_Vec2::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{
    auto data = var.get_value<glm::vec2>();

    if (read_only)
    {
        ImGui::Text("%d, %d, %d", data.x, data.y);
    }
    else
    {
        bool changed = false;

        ImGui::BeginHorizontal(&data);

        ImGui::PushMultiItemsWidths(2, 2 * 75.0f);

        changed |= ImGui::DragFloat("x", &data.x, 1, -1.0f, -1.0f, details::format.c_str());

        changed |= ImGui::DragFloat("y", &data.y, 1, -1.0f, -1.0f, details::format.c_str());

        ImGui::PopItemWidth();

        ImGui::EndHorizontal();

        if (changed)
        {
            var = data;

            return true;
        }
    }


    return false;
}

bool Inspector_Vec3::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{
    auto data = var.get_value<glm::vec3>();

    if (read_only)
    {
        ImGui::Text("%d, %d, %d", data.x, data.y, data.z);
    }
    else
    {
        bool changed = false;

        ImGui::BeginHorizontal(&data);

        ImGui::PushMultiItemsWidths(3, 3 * 75.0f);

        changed |= ImGui::DragFloat("x", &data.x, 1, -1.0f, -1.0f, details::format.c_str());

        changed |= ImGui::DragFloat("y", &data.y, 1, -1.0f, -1.0f, details::format.c_str());

        changed |= ImGui::DragFloat("z", &data.z, 1, -1.0f, -1.0f, details::format.c_str());

        ImGui::PopItemWidth();

        ImGui::EndHorizontal();

        if (changed)
        {
            var = data;

            return true;
        }
    }


    return false;
}

bool Inspector_Vec4::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{
    auto data = var.get_value<glm::vec4>();

    if (read_only)
    {
        ImGui::Text("%d, %d, %d, %d", data.x, data.y, data.z, data.w);
    }
    else
    {
        bool changed = false;

        ImGui::BeginHorizontal(&data);

        ImGui::PushMultiItemsWidths(4, 4 * 75.0f);

        changed |= ImGui::DragFloat("x", &data.x, 1, -1.0f, -1.0f, details::format.c_str());
      
        changed |= ImGui::DragFloat("y", &data.y, 1, -1.0f, -1.0f, details::format.c_str());

        changed |= ImGui::DragFloat("z", &data.z, 1, -1.0f, -1.0f, details::format.c_str());

        changed |= ImGui::DragFloat("w", &data.w, 1, -1.0f, -1.0f, details::format.c_str());

        ImGui::PopItemWidth();

        ImGui::EndHorizontal();

        if(changed)
        {
            var = data;

            return true;
        }
    }


    return false;
}

