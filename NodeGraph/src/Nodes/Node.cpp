#include "Node.h"

Node::Node()
{
	m_NumInputs = 0;
	m_NumOutputs = 0;
}


RTTR_REGISTRATION
{
	registration::class_<Node>("Node")(policy::ctor::as_raw_ptr);
}
