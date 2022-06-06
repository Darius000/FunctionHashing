#include "PCH.h"
#include "Cast.h"

using IntToBool = CastTo<int, bool>;
using FloatToBool = CastTo<float, bool>;
using BoolToInt = CastTo<bool, int>;
using BoolToFloat = CastTo<bool, float>;
using IntToFloat = CastTo<int, float>;
using FloatToInt = CastTo<float, int>;

RTTR_REGISTRATION
{
	auto ib = registration::class_<IntToBool>("Cast<int,bool>")(metadata("Category", "Casts | "))
	.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &IntToBool::m_Input)
		.property_readonly("Out", &IntToBool::m_Output);

	auto tb = registration::class_<FloatToBool>("Cast<float,bool>")(metadata("Category", "Casts | "))
	.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &FloatToBool::m_Input)
		.property_readonly("Out", &FloatToBool::m_Output);

	auto bi = registration::class_<BoolToInt>("Cast<bool,int>")(metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &BoolToInt::m_Input)
		.property_readonly("Out", &BoolToInt::m_Output);

	auto bf = registration::class_<BoolToFloat>("Cast<bool,float>")(metadata("Category", "Casts | "))
	.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &BoolToFloat::m_Input)
		.property_readonly("Out", &BoolToFloat::m_Output);

	auto IF = registration::class_<IntToFloat>("Cast<int,float>")(metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &IntToFloat::m_Input)
		.property_readonly("Out", &IntToFloat::m_Output);

	auto FI = registration::class_<FloatToInt>("Cast<float,int>")(metadata("Category", "Casts | "))
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("In", &FloatToInt::m_Input)
		.property_readonly("Out", &FloatToInt::m_Output);
	}