#pragma once

#include "DataTypes/DataTypeEnum.h"
#include "Nodes/Node.h"

enum class EVariableNodeType : uint8_t
{
	Get,
	Set,
	Max
};


template<>
std::vector<std::string> EnumStrings<EVariableNodeType>::Data = {
		"Get", "Set"
};


template<typename T>
class VariableNodeInterface : public Node
{
public:
	VariableNodeInterface(Ref<struct IProperty> prop)
		:m_Property(prop)
	{

		if (prop)
		{
			m_PropertyName = prop->GetName();

			prop->OnDestroyed.AddBinding([this](NodeEditorObject* obj) {

				m_Property = nullptr;
				m_PropertyName = "UnReferenced Property!";
			});
		}
		else
		{
			m_Property = nullptr;
			m_PropertyName = "UnReferenced Property!";
		}
		


	}

	virtual void Serialize(YAML::Emitter& out);

	const ENodeType GetNodeType() override { return ENodeType::Simple; }

	Ref<struct IProperty> m_Property;
	std::string m_PropertyName;
};


template<typename T>
void VariableNodeInterface<T>::Serialize(YAML::Emitter& out)
{
	Node::Serialize(out);

	if (m_Property)
	{
		out << YAML::Key << "PropertyID";
		out << YAML::Value << m_Property->GetID();
	}
	
}
