#include "PCH.h"
#include "SetVariableNode.h"

using SetVariableNodeInt = SetVariableNode<int>;
using SetVariableNodeFloat = SetVariableNode<float>;
using SetVariableNodeBool = SetVariableNode<bool>;

DEFINE_REGISTER_NODE(SetVariableNodeInt);
DEFINE_REGISTER_NODE(SetVariableNodeFloat)
DEFINE_REGISTER_NODE(SetVariableNodeBool)
