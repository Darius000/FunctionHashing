#include "PCH.h"
#include "GetVariableNode.h"

using GetVariableNodeInt = GetVariableNode<int>;
using GetVariableNodeFloat = GetVariableNode<float>;
using GetVariableNodeBool = GetVariableNode<bool>;

REGISTER_NODE(GetVariableNodeInt, "", "", Ref<IProperty>);
REGISTER_NODE(GetVariableNodeFloat, "", "", Ref<IProperty>)
REGISTER_NODE(GetVariableNodeBool, "", "", Ref<IProperty>)