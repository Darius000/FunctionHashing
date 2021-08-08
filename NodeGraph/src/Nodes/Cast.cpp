#include "PCH.h"
#include "Cast.h"

using IntToBool = CastNode<int, bool>;
using FloatToBool = CastNode<float, bool>;
using BoolToInt = CastNode<bool, int>;
using BoolToFloat = CastNode<bool, float>;

REGISTER_NODE(IntToBool, "Operators|Int to Bool", "Convert int to bool")
REGISTER_NODE(FloatToBool, "Operators|Float to Bool", "Convert float to bool")
REGISTER_NODE(BoolToInt, "Operators |Bool to Int", "Convert bool to int")
REGISTER_NODE(BoolToFloat, "Operators |Bool to Float", "Convert bool to float")