#ifndef PROPERTYFIELDELEMENT_H
#define PROPERTYFIELDELEMENT_H

#include "UIElement.h"

class PropertyFieldElement : public UIElement
{
public:

	PropertyFieldElement(rttr::property& _property, rttr::instance& _object);

	void OnDrawElement() override;

private:

	rttr::property m_Property;

	rttr::instance m_Object;
};

#endif // !PROPERTYFIELDELEMENT_H
