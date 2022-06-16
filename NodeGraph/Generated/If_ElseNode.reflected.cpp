#include "Core/Reflection/Reflection.h"
#include "Nodes/If_ElseNode.h"

REFLECT_INLINE(If_ElseNode)
{
	registration::class_<If_ElseNode>("If_ElseNode")(metadata(ClassMetaData::Category, "Branching | "), metadata(ClassMetaData::Description, "Condition determines next node path"))
		.constructor<>(registration::public_access)(policy::ctor::as_raw_ptr)
		.property("m_InCondition", &If_ElseNode::m_InCondition, registration::public_access)(metadata("Kind", "Input"));
}