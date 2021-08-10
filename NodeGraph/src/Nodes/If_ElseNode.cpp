#include "PCH.h"
#include "If_ElseNode.h"

If_ElseNode::If_ElseNode()
{
	AddDataPin<bool>("Condition", ImNodesAttributeType_Input, MakeRef<IPropertyT<bool>>());
	AddExecutionPin(ImNodesAttributeType_Input);
	AddExecutionPin(ImNodesAttributeType_Output);
	
	m_TitleColor = {1, 0, 0, 1};
	m_Color = {.2f, .2f, .2f, .5f};

}

void If_ElseNode::OnExecute()
{
	
}


DEFINE_REGISTER_NODE(If_ElseNode)
