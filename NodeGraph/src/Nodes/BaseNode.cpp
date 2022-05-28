#include "PCH.h"
#include "BaseNode.h"

BaseNode::BaseNode(){}

BaseNode::~BaseNode() {}

void BaseNode::Execute() 
{
	if (!m_BeginExecution)
	{
		OnBeginExecute();

		m_BeginExecution = true;
	}
	
	OnExecute();

	OnEndExecute();

	m_BeginExecution = false;
}

void BaseNode::Serialize(YAML::Emitter& out)
{
	NodeEditorObject::Serialize(out);

	out << YAML::Key << "FactoryName";
	out << YAML::Value << GetFactoryName();

	out << YAML::Key << "Position" << YAML::Value << m_Position;

}

void BaseNode::DeSerialize(YAML::detail::iterator_value& value)
{
	NodeEditorObject::DeSerialize(value);

	m_Position = value["Position"].as<Vec2>();
}
