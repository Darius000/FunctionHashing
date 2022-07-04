#include "LinkableNode.h"
#include "Utilities/VectorUtilities.h"

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

	child->OnDestroyedEvent.AddBinding(BIND_EVENT(this, LinkableNode::OnChildNodeDestroyed));

	OnAddChild(child);
}

void LinkableNode::RemoveChild(BaseNode* child)
{
	VectorUtilities::Remove(m_Children, child);

	OnRemoveChild(child);
}


void LinkableNode::OnChildNodeDestroyed(BaseObject* node)
{
	RemoveChild(Cast<BaseNode>(node));
}
