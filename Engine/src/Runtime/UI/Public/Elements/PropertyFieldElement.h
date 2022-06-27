#pragma once

#include "UIElement.h"

class PropertyFieldElement : public UIElement
{
public:

	PropertyFieldElement(const rttr::property& _property, const rttr::instance& _object);

	void OnDrawElement() override;

private:

	rttr::property m_Property;

	rttr::instance m_Object;
};
