#include "NodeListPanel.h"
#include "Category/Category.h"
#include <rttr/type>

NodeListPanel::NodeListPanel(ImGuiWindowFlags flags, ImGuiID id, bool runtimecreated)
	:ImGuiPanel("Create New Node", flags)
{
	auto nodeType = rttr::type::get_by_name("Node");

	for (auto derived_type : nodeType.get_derived_classes())
	{
		
		std::string cat, descr;
		auto md_category = derived_type.get_metadata("Category");
		auto md_description = derived_type.get_metadata("Description");

		cat = (md_category.is_valid() ? md_category.get_value<std::string>()  : "") + derived_type.get_name();
		descr = md_description.is_valid() ? md_description.get_value<std::string>() : "";

		NodeCatgeories::AddCategory(cat, descr);
	}
}

NodeListPanel::~NodeListPanel()
{
}

void NodeListPanel::OnRenderMenuBar()
{
}

void NodeListPanel::OnRenderWindow()
{
	auto& list = NodeCatgeories::GetCategoryList();
	DrawCategory("Node List", list);
}

void NodeListPanel::DrawCategory(std::string_view id, const struct CategoryList& item)
{
	float width = ImGui::GetWindowContentRegionWidth();
	for (auto& leaf : item.m_Leafs)
	{
		auto name = leaf.m_Name + "##" + id.data();
		if (ImGui::TreeNodeEx(name.data(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf))
		{
			ImGui::TreePop();
		}

		if (ImGui::IsItemClicked((int)EMouseButton::Left))
		{
			OnMenuItemSelected.Invoke(leaf.m_Name.data());
		}

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text(leaf.m_Description.c_str());
			ImGui::EndTooltip();
		}

	}

	for (auto& cat : item.m_SubCategories)
	{
		if (ImGui::TreeNodeEx(cat.first.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			DrawCategory(id, *cat.second);
			ImGui::TreePop();

		}
	}
}
