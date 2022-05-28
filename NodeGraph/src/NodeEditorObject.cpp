#include "PCH.h"
#include "NodeEditorObject.h"

NodeEditorObject::NodeEditorObject()
{	
	m_Name = "Object";
	m_PendingDestroy = false;
}

NodeEditorObject::NodeEditorObject(const NodeEditorObject& obj)
{
	m_Name = obj.m_Name;
	m_PendingDestroy = false;
}

NodeEditorObject::~NodeEditorObject()
{
	
}


void NodeEditorObject::Destroy()
{
	m_PendingDestroy = true;
	OnDestroyed.Broadcast(this);
}

void NodeEditorObject::SetName(const std::string& str)
{
	m_Name = str;
}

void NodeEditorObject::SetToolTip(const std::string& tooltip)
{
	m_ToolTip = tooltip;
}

Core::UUID NodeEditorObject::GetID() const
{
	return m_ID;
}


void NodeEditorObject::Serialize(YAML::Emitter& out)
{
	
	out << YAML::Key << "Identifier";
	out << YAML::Value << m_ID;
	
	out << YAML::Key << "Name";
	out << YAML::Value << m_Name;

	out << YAML::Key << "ToolTip";
	out << YAML::Value << m_ToolTip;

}

void NodeEditorObject::DeSerialize(YAML::detail::iterator_value& value)
{
	m_Name = value["Name"].as<std::string>();
	m_ID =	value["Identifier"].as<Core::UUID>();
	m_ToolTip = value["ToolTip"].as<std::string>();
}


NodeEditorObject& NodeEditorObject::operator=(const NodeEditorObject& obj)
{
	m_Name = obj.m_Name;
	return *this;
}

const bool NodeEditorObject::operator==(const NodeEditorObject& obj)
{
	return m_Name == obj.m_Name && m_ID == obj.m_ID;
}
