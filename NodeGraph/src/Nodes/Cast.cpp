#include "PCH.h"
#include "Cast.h"

using IntToBool = CastNode<int, bool>;
using FloatToBool = CastNode<float, bool>;
using BoolToInt = CastNode<bool, int>;
using BoolToFloat = CastNode<bool, float>;

DEFINE_REGISTER_NODE(IntToBool)
DEFINE_REGISTER_NODE(FloatToBool)
DEFINE_REGISTER_NODE(BoolToInt)
DEFINE_REGISTER_NODE(BoolToFloat)