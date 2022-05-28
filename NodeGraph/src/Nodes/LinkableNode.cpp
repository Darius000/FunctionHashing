#include "PCH.h"
#include "LinkableNode.h"
#include "Core/Helpers/Vectors/VectorHelper.h"

LinkableNode::LinkableNode ()
{

}

LinkableNode::LinkableNode(const LinkableNode& other)
{
	m_Children = other.m_Children;
	m_LinkData = other.m_LinkData;
}

void LinkableNode::AddChild(BaseNode* child)
{
	m_Children.push_back(child);

	child->OnDestroyed.AddBinding(BIND_EVENT(this, LinkableNode::OnChildNodeDestroyed));

	OnAddChild(child);
}

void LinkableNode::RemoveChild(BaseNode* child)
{
	Helpers::Vector::Remove(m_Children, child);

	OnRemoveChild(child);
}


void LinkableNode::OnChildNodeDestroyed(NodeEditorObject* node)
{
	RemoveChild(Cast<BaseNode>(node));
}

void LinkableNode::Serialize(YAML::Emitter& out)
{
	BaseNode::Serialize(out);

	out << YAML::Key << "FactoryName";
	out << YAML::Value << GetFactoryName();

	out << YAML::Key << "LinkData" << YAML::Value << GetLinkData();
}

void LinkableNode::DeSerialize(YAML::detail::iterator_value& value)
{
	BaseNode::DeSerialize(value);

	auto links = value["LinkData"].as<LinkData>();
	for (auto link : links)
	{
		m_LinkData.push_back(link);
	}
}