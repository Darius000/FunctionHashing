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


void LinkableNode::OnChildNodeDestroyed(BaseObject* node)
{
	RemoveChild(Cast<BaseNode>(node));
}
