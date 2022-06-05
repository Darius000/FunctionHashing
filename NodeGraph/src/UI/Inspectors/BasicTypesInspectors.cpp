#include "BasicTypesInspectors.h"

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

