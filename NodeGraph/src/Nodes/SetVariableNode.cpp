#include "PCH.h"
#include "SetVariableNode.h"

using SetVariableNodeInt = SetVariableNode<int>;
using SetVariableNodeFloat = SetVariableNode<float>;
using SetVariableNodeBool = SetVariableNode<bool>;

REGISTER_NODE(SetVariableNodeInt, "", "", Ref<IProperty>);
REGISTER_NODE(SetVariableNodeFloat,"", "", Ref<IProperty>)
REGISTER_NODE(SetVariableNodeBool, "", "", Ref<IProperty>)