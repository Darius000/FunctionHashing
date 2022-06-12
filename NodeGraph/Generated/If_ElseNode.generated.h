REFLECT_INLINE(TOO::E_Alignment)
{
	registration::enumeration<TOO::E_Alignment>("TOO::E_Alignment")
	(
		value("AlignLeft" , TOO::E_Alignment::AlignLeft),
		value("AlignRight" , TOO::E_Alignment::AlignRight),
		value("AlignHCenter" , TOO::E_Alignment::AlignHCenter),
		value("AlignJustify" , TOO::E_Alignment::AlignJustify)
	);
}

REFLECT_INLINE(If_ElseNode)
{
	registration::class_<If_ElseNode>("If_ElseNode")(metadata(ClassMetaData::Category , "Branching | "),metadata(ClassMetaData::Description , "Condition determines next node path"))
	.constructor<>(registration::public_access)(policy::ctor::as_raw_ptr)
	.property("m_InCondition" , &If_ElseNode::m_InCondition, registration::public_access)
;
}

