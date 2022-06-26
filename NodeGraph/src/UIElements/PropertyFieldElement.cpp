#include "PropertyFieldElement.h"
#include "UI/Inspectors/InspectorRegistry.h"

PropertyFieldElement::PropertyFieldElement(const rttr::property& _property, const rttr::instance& _object)
	:m_Property(_property), m_Object(_object)
{
}

void PropertyFieldElement::OnDrawElement()
{
	if (m_Property.get_type())
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
