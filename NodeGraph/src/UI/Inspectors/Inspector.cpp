#include "Inspector.h"

void ToolTip(const rttr::property& prop)
{
	auto& g = *ImGui::GetCurrentContext();
	if (!g.DragDropActive && ImGui::IsItemHovered())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		auto tooltip = prop.get_metadata("ToolTip");
		if (tooltip)
		{
			ImGui::BeginTooltip();
			ImGui::TextUnformatted(tooltip.to_string().c_str());
			ImGui::EndTooltip();
		}
	}
}

Property_Layout::Property_Layout(const rttr::property& prop, bool columns)
{
	std::string pretty_name = prop.get_name().to_string();
	auto meta_pretty_name = prop.get_metadata("pretty_name");

	if (meta_pretty_name)
	{
		pretty_name = meta_pretty_name.get_value<std::string>();
	}

	if (columns)
	{
		if (ImGui::GetColumnsCount() > 1)
		{
			ImGui::EndColumns();
		}

		ImGui::BeginColumns("Properties", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
	}

	ImGui::AlignTextToFramePadding();
	ImGui::TextUnformatted(pretty_name.data());

	ToolTip(prop);

	ImGui::NextColumn();

	ImGui::PushID(pretty_name.data());
	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
}

Property_Layout::Property_Layout(std::string_view name, bool columns)
{
	if (columns)
	{
		if (ImGui::GetColumnsCount() > 1)
		{
			ImGui::EndColumns();
		}

		ImGui::BeginColumns("Properties", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
	}

	ImGui::AlignTextToFramePadding();
	ImGui::TextUnformatted(name.data());

	ImGui::NextColumn();

	ImGui::PushID(name.data());
	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
}

Property_Layout::Property_Layout(std::string_view name, std::string_view tooltip, bool columns)
{
}

Property_Layout::~Property_Layout()
{
	ImGui::PopItemWidth();
	ImGui::PopID();

	if (ImGui::GetColumnsCount() > 1)
	{
		ImGui::EndColumns();
	}
}
