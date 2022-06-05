#include "If_ElseNode.h"
#include <rttr/registration>

If_ElseNode::If_ElseNode()
{
	m_Name = "If Else";
}

void If_ElseNode::OnExecute()
{
	
}


using namespace rttr;

RTTR_REGISTRATION
{
	registration::class_<If_ElseNode>("IfElse")(metadata("Category", "Branching | "), metadata("Description", "Condition determines next node path"))
	.constructor<>()(policy::ctor::as_raw_ptr)
	.property("Condition", &If_ElseNode::m_InCondition);

}