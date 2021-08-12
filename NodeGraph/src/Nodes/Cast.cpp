#include "PCH.h"
#include "Cast.h"

using IntToBool = CastTo<int, bool>;
using FloatToBool = CastTo<float, bool>;
using BoolToInt = CastTo<bool, int>;
using BoolToFloat = CastTo<bool, float>;
using IntToFloat = CastTo<int, float>;
using FloatToInt = CastTo<float, int>;

DEFINE_REGISTER_NODE(IntToBool)
DEFINE_REGISTER_NODE(FloatToBool)
DEFINE_REGISTER_NODE(BoolToInt)
DEFINE_REGISTER_NODE(BoolToFloat)
DEFINE_REGISTER_NODE(IntToFloat)
DEFINE_REGISTER_NODE(FloatToInt)