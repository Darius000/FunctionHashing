#include "Core/Reflection/Reflection.h"
#include "Nodes/If_ElseNode.h"

REFLECT_INLINE(If_ElseNode)
{
	rttr::registration::class_<If_ElseNode>("If_ElseNode")(rttr::metadata(ClassMetaData::Category, "Branching | "), rttr::metadata(ClassMetaData::Description, "Condition determines next node path"))
		.constructor<>(rttr::registration::public_access)(rttr::policy::ctor::as_raw_ptr)
		.property("m_InCondition", &If_ElseNode::m_InCondition, rttr::registration::public_access)(rttr::metadata("Kind", "Input"));
}