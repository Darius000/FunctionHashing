#include "PinElement.h"
#include "Nodes/BaseNode.h"


PinElement::PinElement(std::string_view name, ed::PinKind kind, rttr::property& property, rttr::instance& obj, bool canMultiConnect)
	:m_PinKind(kind), m_PinType(property.get_type()), m_CanMulitConnect(canMultiConnect), m_Connections(0), m_Property(property), m_Object(obj)
{
	m_Name = name;
}

void PinElement::BeginLayout(uint32_t id)
{
	if (m_PinKind == ed::PinKind::Input)
	{
		ed::PushStyleVar(ed::StyleVar_PivotAlignment, { 0.0f, 0.5f });
		ed::PushStyleVar(ed::StyleVar_PivotSize, { 0,0 });
	}
	else
	{
		ed::PushStyleVar(ed::StyleVar_PivotAlignment, { .5f, 0.5f });
		ed::PushStyleVar(ed::StyleVar_PivotSize, { 0, 0 });
	}

	ed::BeginPin(id, m_PinKind);
}

void PinElement::EndLayout()
{
	ed::EndPin();

	ed::PopStyleVar(2);
}

