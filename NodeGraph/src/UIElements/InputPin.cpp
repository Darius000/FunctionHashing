#include "InputPin.h"
#include "Runtime/UI/Elements/HorizontalBox.h"
#include "Runtime/UI/Inspectors/InspectorRegistry.h"
#include "Runtime/UI/Elements/CircleElement.h"
#include "Runtime/UI/Elements/LabelElement.h"
#include "Runtime/UI/Elements/PropertyFieldElement.h"

inline ImColor GetPinColor(rttr::type type)
{
	if (type == rttr::type::get<int>()) return ImColor(0.1f, 0.5f, 0.1f);
	if (type == rttr::type::get<bool>()) return ImColor(1.0f, 0.0f, 0.0f);
	if (type == rttr::type::get<float>()) return ImColor(0.6f, 1.0f, 0.6f);
	if (type == rttr::type::get<std::string>()) return ImColor(1.0f, 0.5f, 0.5f);
	if (type == rttr::type::get<glm::vec2>()) return ImColor(0.1f, 0.1f, 1.0f);
	if (type == rttr::type::get<glm::vec3>()) return ImColor(1.0f, 1.0f, 0.0f);
	if (type == rttr::type::get<glm::vec4>()) return ImColor(1.0f, 0.5f, 0.0f);

	return ImColor();
}




InputPin::InputPin(std::string_view name, const rttr::property& property, const rttr::instance& obj, bool canMultiConnect)	
	:PinElement(name, ed::PinKind::Input, property, obj, canMultiConnect)
{
	auto pinStyle = CircleStyle();
	pinStyle.m_Radius = 6.0f;
	pinStyle.m_Resolution = 30;
	pinStyle.m_Thickness = 2.0f;

	m_PinShape = new CircleElement("");
	auto& style = m_PinShape->GetStyle();
	style.m_Color = GetPinColor(property.get_type());


	m_PinShape->GetCircleStyle() = pinStyle;

	auto h_element = new HorizontalBox();

	h_element->AddChild(m_PinShape, SlotConfiguration(-1.0f));

	h_element->AddChild(new LabelElement("Label", name.data()), SlotConfiguration(- 1.0f));

	m_PropertyField = new PropertyFieldElement(property, obj);
	auto property_slot = Cast<HorizontalBoxSlot>(h_element->AddChild(m_PropertyField));

	AddChild(h_element);
}

void InputPin::OnConnected()
{
	PinElement::OnConnected();

	m_PropertyField->m_Enabled = false;
}

void InputPin::OnDisConnected()
{
	PinElement::OnDisConnected();

	m_PropertyField->m_Enabled = true;
}



OutputPin::OutputPin(std::string_view name, const rttr::property& property, const rttr::instance& obj, bool canMultiConnect)
	:PinElement(name, ed::PinKind::Output, property, obj, canMultiConnect)
{
	auto pinStyle = CircleStyle();
	pinStyle.m_Radius = 6.0f;
	pinStyle.m_Resolution = 30;
	pinStyle.m_Thickness = 2.0f;

	m_PinShape = new CircleElement("");
	auto& style = m_PinShape->GetStyle();
	style.m_Color = GetPinColor(property.get_type());


	m_PinShape->GetCircleStyle() = pinStyle;

	auto h_element = new HorizontalBox();

	h_element->AddChild(new LabelElement("Label", name.data()));

	h_element->AddChild(m_PinShape);

	AddChild(h_element);
}
