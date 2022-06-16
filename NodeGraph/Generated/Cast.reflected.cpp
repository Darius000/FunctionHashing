#include "Core/Reflection/Reflection.h"
#include "Nodes/Cast.h"

using IntToBool = CastTo<int, bool>;
using FloatToBool = CastTo<float, bool>;
using BoolToInt = CastTo<bool, int>;
using BoolToFloat = CastTo<bool, float>;
using IntToFloat = CastTo<int, float>;
using FloatToInt = CastTo<float, int>;

REFLECT_INLINE(IntToBool)
{
	registration::class_<IntToBool>("Cast<int,bool>")(metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &IntToBool::m_Input)(metadata("Kind", "Input"))
		.property_readonly("Out", &IntToBool::m_Output)(metadata("Kind", "Output"));
}

REFLECT_INLINE(FloatToBool)
{

	registration::class_<FloatToBool>("Cast<float,bool>")(metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &FloatToBool::m_Input)(metadata("Kind", "Input"))
		.property_readonly("Out", &FloatToBool::m_Output)(metadata("Kind", "Output"));
}

REFLECT_INLINE(BoolToInt)
{

	registration::class_<BoolToInt>("Cast<bool,int>")(metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &BoolToInt::m_Input)(metadata("Kind", "Input"))
		.property_readonly("Out", &BoolToInt::m_Output)(metadata("Kind", "Output"));
}

REFLECT_INLINE(BoolToFloat)
{

	registration::class_<BoolToFloat>("Cast<bool,float>")(metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &BoolToFloat::m_Input)(metadata("Kind", "Input"))
		.property_readonly("Out", &BoolToFloat::m_Output)(metadata("Kind", "Output"));
}

REFLECT_INLINE(IntToFloat)
{

	registration::class_<IntToFloat>("Cast<int,float>")(metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &IntToFloat::m_Input)(metadata("Kind", "Input"))
		.property_readonly("Out", &IntToFloat::m_Output)(metadata("Kind", "Output"));
}

REFLECT_INLINE(FloatToInt)
{

	registration::class_<FloatToInt>("Cast<float,int>")(metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &FloatToInt::m_Input)(metadata("Kind", "Input"))
		.property_readonly("Out", &FloatToInt::m_Output)(metadata("Kind", "Output"));
}