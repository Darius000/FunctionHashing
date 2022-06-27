#include "PCH.h"
#include "BasicTypesInspectors.h"
#include <imgui.h>
#include <imgui_internal.h>


namespace details
{
    const std::string format = "%.2f";
}

bool Inspector_Bool::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{
    auto data = var.get_value<bool>();

    if (read_only)
    {
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted(data ? "true" : "false");
    }
    else
    {
        if (ImGui::Checkbox("", &data))
        {
            var = data;
            return true;
        }
    }

    return false;
}

bool Inspector_String::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{
    auto data = var.get_value<std::string>();

    if (read_only)
    {
        ImGui::TextUnformatted(data.c_str());
    }
    else
    {
        static std::array<char,255> buf;
        buf.fill(0);
        std::memcpy(buf.data(), data.c_str(), data.size() < 255 ? data.size() : 255);
        if (ImGui::InputText("", buf.data(), buf.size(), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            var = std::string(buf.data());

            return true;
        }
    }

    return false;
}

bool Inspector_Int32::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{
    auto data = var.to_int32();

    if (read_only)
    {
        ImGui::TextUnformatted(std::to_string(data).c_str());
    }
    else
    {
        if (ImGui::DragInt("", &data))
        {
            var = data;

            return true;
        }
    }
    

    return false;
}

bool Inspector_Float::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{
    auto data = var.get_value<float>();


    if (read_only)
    {
        ImGui::Text(std::to_string(data).c_str());
    }
    else
    {
        if (ImGui::DragFloat("", &data, 1, -1.0f, -1.0f, details::format.c_str()))
        {
            var = data;

            return true;
        }
    }

    return false;
}

bool Inspector_Double::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{
    auto data = static_cast<float>(var.get_value<double>());

    if (read_only)
    {
        ImGui::Text(std::to_string(data).c_str());
    }
    else
    {
        if (ImGui::DragFloat("", &data, 1, -1, -1, details::format.c_str()))
        {
            var = data;

            return true;
        }
    }

    return true;
}

bool Inspector_UInt32::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{
    auto data = static_cast<int>(var.to_uint32());

    if (read_only)
    {
        ImGui::AlignTextToFramePadding();
        ImGui::Text(std::to_string(data).c_str());
    }
    else
    {
        if (ImGui::DragInt("", &data))
        {
            var = static_cast<uint32_t>(data);

            return true;
        }
    }

    return true;
}

bool Inspector_UInt8::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{
    auto data = static_cast<int>(var.to_uint8());

    if (read_only)
    {
        ImGui::Text(std::to_string(data).c_str());
    }
    else
    {
        if (ImGui::SliderInt("", &data, 0, 255))
        {
            var = static_cast<uint8_t>(data);

            return true;
        }
    }

    return true;
}

bool Inspector_UUID::Inspect(rttr::variant& var, bool read_only, const meta_getter& get_metadata)
{
    auto data = var.get_value<Core::UUID>();
    auto value = (int)(uint64_t)data;

    if (read_only)
    {
        ImGui::AlignTextToFramePadding();
        ImGui::Text(std::to_string((uint64_t)data).c_str());
    }
    else
    {
        if (ImGui::DragInt("", &value))
        {
            var = static_cast<Core::UUID>(value);

            return true;
        }
    }

    return true;
}