#include "PCH.h"
#include "NodeEditorObject.h"

NodeEditorObject::NodeEditorObject()
{	
	auto id = GetNextAvialableID();
	m_Name = "Object" + std::to_string(id);
	m_ID = id;
	m_PendingDestroy = false;
}

NodeEditorObject::NodeEditorObject(const NodeEditorObject& obj)
{
	auto id = GetNextAvialableID();
	m_Name = obj.m_Name;
	m_ID = id;
	m_PendingDestroy = false;
}

NodeEditorObject::~NodeEditorObject()
{
	
}


void NodeEditorObject::Destroy()
{
	m_PendingDestroy = true;
	s_DeletedIDs.push_back(m_ID);
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

ImGuiID NodeEditorObject::GetID() const
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
	auto name = value["Name"].as<std::string>();
	auto id =	value["Identifier"].as<ImGuiID>();
	auto tooltip = value["ToolTip"].as<std::string>();

	m_Name = name;
	m_ID = id;
	m_ToolTip = tooltip;
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

ImGuiID NodeEditorObject::GetNextAvialableID()
{	
	ImGuiID id = 0;

	if (s_DeletedIDs.size() > 0)
	{
		id = s_DeletedIDs[0];
		s_DeletedIDs.erase(s_DeletedIDs.begin());
		return id;
	}

	return id = ++s_ID;
}

ImGuiID NodeEditorObject::s_ID = 0;

std::vector<ImGuiID> NodeEditorObject::s_DeletedIDs;

