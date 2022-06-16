#include "PinElement.h"
#include "Nodes/BaseNode.h"
#include "UI/Inspectors/InspectorRegistry.h"

ImColor GetPinColor(rttr::type type)
{
	if (type == rttr::type::get<int>()) return ImColor(0.1f, 0.5f, 0.1f);
	if (type == rttr::type::get<bool>()) return ImColor(1.0f, 0.0f, 0.0f);
	if (type == rttr::type::get<float>()) return ImColor(0.6f, 1.0f, 0.6f);
	if (type == rttr::type::get<std::string>()) return ImColor(1.0f, 0.5f, 0.5f);
	if (type == rttr::type::get<class BaseNode*>()) return ImColor(.6f, .6f, .6f);

	return ImColor();
}


PinElement::PinElement(std::string_view name, ed::PinKind kind, rttr::property& property, rttr::instance& obj, bool canMultiConnect)
	:m_PinKind(kind), m_PinType(property.get_type()), m_CanMulitConnect(canMultiConnect), m_Connections(0), m_Property(property), m_Object(obj)
{
	m_Name = name;
}

void PinElement::OnBeginDraw()
{
	ImGui::SetCursorPos(ImGui::GetCursorPos() + (m_PinKind == ed::PinKind::Output ? ImVec2(400.0f, 0.0f) : ImVec2(0.0f, 0.0f)));
	ed::BeginPin((uint64_t)GetID(), GetKind());

}

void PinElement::OnEndDraw()
{
	ImDrawList* drawlist = ImGui::GetWindowDrawList();
	auto style = ed::GetStyle();
	auto radius = style.PinRadius;
	auto cursorpos = ImGui::GetCursorScreenPos();

	ImRect rect = ImRect(cursorpos, cursorpos + ImVec2{radius, radius});

	auto rect_w = rect.Max.x - rect.Min.x;
	auto rect_center_x = (rect.Min.x + rect.Max.x) * .5f;
	auto rect_center_y = (rect.Min.y + rect.Max.y) * .5f;
	auto rect_center = ImVec2(rect_center_x, rect_center_y);

	auto rect_offset = -static_cast<int>(rect_w * .25f * .25f);

	rect_center.x += (rect_offset * .5f) * 2.0f;

	if (m_PinKind == ed::PinKind::Input)
	{
		if (drawlist)
		{
			drawlist->AddCircle(rect_center, 0.5f * rect_w / 2.f, GetPinColor(m_Property.get_type()), 20, 2.0f);
		}

		ImGui::Dummy({ radius, radius });

		ImGui::SameLine();

		ImGui::TextUnformatted(GetName().c_str(), nullptr, TextAlignment_::Center, TextJustification_::Right);

		ImGui::SameLine();


		if (m_Property.get_type() != rttr::type::get<class BaseNode*>())
		{
			ImGui::PushItemWidth(200.0f);
			auto prop_var = m_Property.get_value(m_Object);
			if (InspectorRegistry::InspectVar(prop_var))
			{
				m_Property.set_value(m_Object, prop_var);
			}
			ImGui::PopItemWidth();
		}
	}
	else
	{
		ImGui::TextUnformatted(GetName().c_str(), nullptr, TextAlignment_::Center, TextJustification_::Left);

		ImGui::SameLine();

		ImGui::Dummy({ radius, radius });

		
		if (drawlist)
		{
			drawlist->AddCircle(rect_center, 0.5f * rect_w / 2.f, GetPinColor(m_Property.get_type()), 20, 2.0f);
		}

	}

	

	ed::EndPin();

}
