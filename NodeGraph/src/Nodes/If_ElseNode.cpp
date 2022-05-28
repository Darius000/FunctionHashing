#include "PCH.h"
#include "If_ElseNode.h"

If_ElseNode::If_ElseNode()
{
	
	m_TitleColor = ImGuiExtras::DarkRed;
	m_Color = {.2f, .2f, .2f, .5f};

}

void If_ElseNode::OnExecute()
{
	
}


DEFINE_REGISTER_NODE(If_ElseNode)
