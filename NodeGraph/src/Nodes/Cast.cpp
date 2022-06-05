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
	.constructor<>()(rttr::policy::ctor::as_raw_ptr);

	auto tb = registration::class_<FloatToBool>("Cast<float,bool>")(metadata("Category", "Casts | "))
	.constructor<>()(rttr::policy::ctor::as_raw_ptr);

	auto bi = registration::class_<BoolToInt>("Cast<bool,int>")(metadata("Category", "Casts | "))
	.constructor<>()(rttr::policy::ctor::as_raw_ptr);

	auto bf = registration::class_<BoolToFloat>("Cast<bool,float>")(metadata("Category", "Casts | "))
	.constructor<>()(rttr::policy::ctor::as_raw_ptr);

	auto IF = registration::class_<IntToFloat>("Cast<int,float>")(metadata("Category", "Casts | "))
	.constructor<>()(rttr::policy::ctor::as_raw_ptr);

	auto FI = registration::class_<FloatToInt>("Cast<float,int>")(metadata("Category", "Casts | "))
	.constructor<>()(rttr::policy::ctor::as_raw_ptr);
}