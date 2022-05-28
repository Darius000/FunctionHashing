#include "Property.h"

template<>
void IPropertyT<int>::DrawDetails()
{
	ImGui::DragInt("##Value", &m_Prop);
}

template<>
void IPropertyT<float>::DrawDetails()
{
	ImGui::DragFloat("##Value", &m_Prop, 1.0f, 0.0f, 0.0f, "%.3f");
}

template<>
void IPropertyT<bool>::DrawDetails()
{
	ImGui::Checkbox("##Value", &m_Prop);
}

template<>
ImVec4 IPropertyT<int>::GetColor()
{
	return { .3f, .6f, .3f, 1.0f };
}

template<>
ImVec4 IPropertyT<float>::GetColor()
{
	return { .6f, 1.0f, .6f, 1.0f };
}

template<>
ImVec4 IPropertyT<bool>::GetColor()
{
	return { 1.0f, .3f, .3f, 1.0f };
}

template<>
const std::string IPropertyT<int>::GetStaticTypeName()
{
	return "int";
}

template<>
const std::string IPropertyT<float>::GetStaticTypeName()
{
	return "float";
}


template<>
const std::string IPropertyT<bool>::GetStaticTypeName()
{
	return "bool";
}


REGISTER_TYPE(int);
REGISTER_TYPE(float)
REGISTER_TYPE(bool)
