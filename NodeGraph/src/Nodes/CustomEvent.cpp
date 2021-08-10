#include "PCH.h"
#include "CustomEvent.h"

CustomEventNode::CustomEventNode()
{
	m_TitleColor = {1.0f, 0.0f, 0.0f, 0.3f};
	m_Color = {0.0f, 0.0f, 0.0f, 1.0f};

	AddExecutionPin(ImNodesAttributeType_Output);
}

void CustomEventNode::CustomDraw()
{
	Node::CustomDraw();

	
}

void CustomEventNode::OnExecute()
{

}

DEFINE_REGISTER_NODE(CustomEventNode)