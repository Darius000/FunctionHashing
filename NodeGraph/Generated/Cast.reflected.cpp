#include "Reflection/Reflection.h"
#include "Nodes/Cast.h"

using IntToBool = CastTo<int, bool>;
using FloatToBool = CastTo<float, bool>;
using BoolToInt = CastTo<bool, int>;
using BoolToFloat = CastTo<bool, float>;
using IntToFloat = CastTo<int, float>;
using FloatToInt = CastTo<float, int>;

REFLECT_INLINE(IntToBool)
{
	rttr::registration::class_<IntToBool>("Cast<int,bool>")(rttr::metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &IntToBool::m_Input)(rttr::metadata("Kind", "Input"))
		.property_readonly("Out", &IntToBool::m_Output)(rttr::metadata("Kind", "Output"));
}

REFLECT_INLINE(FloatToBool)
{

	rttr::registration::class_<FloatToBool>("Cast<float,bool>")(rttr::metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &FloatToBool::m_Input)(rttr::metadata("Kind", "Input"))
		.property_readonly("Out", &FloatToBool::m_Output)(rttr::metadata("Kind", "Output"));
}

REFLECT_INLINE(BoolToInt)
{

	rttr::registration::class_<BoolToInt>("Cast<bool,int>")(rttr::metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &BoolToInt::m_Input)(rttr::metadata("Kind", "Input"))
		.property_readonly("Out", &BoolToInt::m_Output)(rttr::metadata("Kind", "Output"));
}

REFLECT_INLINE(BoolToFloat)
{

	rttr::registration::class_<BoolToFloat>("Cast<bool,float>")(rttr::metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &BoolToFloat::m_Input)(rttr::metadata("Kind", "Input"))
		.property_readonly("Out", &BoolToFloat::m_Output)(rttr::metadata("Kind", "Output"));
}

REFLECT_INLINE(IntToFloat)
{

	rttr::registration::class_<IntToFloat>("Cast<int,float>")(rttr::metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &IntToFloat::m_Input)(rttr::metadata("Kind", "Input"))
		.property_readonly("Out", &IntToFloat::m_Output)(rttr::metadata("Kind", "Output"));
}

REFLECT_INLINE(FloatToInt)
{

	rttr::registration::class_<FloatToInt>("Cast<float,int>")(rttr::metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &FloatToInt::m_Input)(rttr::metadata("Kind", "Input"))
		.property_readonly("Out", &FloatToInt::m_Output)(rttr::metadata("Kind", "Output"));
}