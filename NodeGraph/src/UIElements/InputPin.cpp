#include "InputPin.h"
#include "UI/Inspectors/InspectorRegistry.h"
#include "CircleElement.h"
#include "LabelElement.h"
#include "Layouts.h"
#include "PropertyFieldElement.h"

inline ImColor GetPinColor(rttr::type type)
{
	if (type == rttr::type::get<int>()) return ImColor(0.1f, 0.5f, 0.1f);
	if (type == rttr::type::get<bool>()) return ImColor(1.0f, 0.0f, 0.0f);
	if (type == rttr::type::get<float>()) return ImColor(0.6f, 1.0f, 0.6f);
	if (type == rttr::type::get<std::string>()) return ImColor(1.0f, 0.5f, 0.5f);

	return ImColor();
}




InputPin::InputPin(std::string_view name, rttr::property& property, rttr::instance& obj, bool canMultiConnect)	
	:PinElement(name, ed::PinKind::Input, property, obj, canMultiConnect)
{
	auto pinStyle = CircleStyle();
	pinStyle.m_Radius = 6.0f;
	pinStyle.m_Resolution = 30;
	pinStyle.m_Thickness = 2.0f;

	auto circle_element = new CircleElement("");
	auto& style = circle_element->GetStyle();
	style.m_Color = GetPinColor(property.get_type());


	circle_element->GetCircleStyle() = pinStyle;

	auto h_element = new HorizontalElement();

	h_element->AddChild(circle_element);

	h_element->AddChild(new LabelElement("Label", name.data()));

	h_element->AddChild(new PropertyFieldElement(property, obj));

	AddChild(h_element);
}



OutputPin::OutputPin(std::string_view name, rttr::property& property, rttr::instance& obj, bool canMultiConnect)
	:PinElement(name, ed::PinKind::Output, property, obj, canMultiConnect)
{
	auto pinStyle = CircleStyle();
	pinStyle.m_Radius = 6.0f;
	pinStyle.m_Resolution = 30;
	pinStyle.m_Thickness = 2.0f;

	auto circle_element = new CircleElement("");
	auto& style = circle_element->GetStyle();
	style.m_Color = GetPinColor(property.get_type());


	circle_element->GetCircleStyle() = pinStyle;

	auto h_element = new HorizontalElement();

	h_element->AddChild(new LabelElement("Label", name.data()));

	h_element->AddChild(circle_element);

	AddChild(h_element);
}
