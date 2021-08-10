#include "PCH.h"
#include "GetVariableNode.h"

using GetVariableNodeInt = GetVariableNode<int>;
using GetVariableNodeFloat = GetVariableNode<float>;
using GetVariableNodeBool = GetVariableNode<bool>;

DEFINE_REGISTER_NODE(GetVariableNodeInt);
DEFINE_REGISTER_NODE(GetVariableNodeFloat)
DEFINE_REGISTER_NODE(GetVariableNodeBool)