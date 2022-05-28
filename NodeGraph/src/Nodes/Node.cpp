#include "PCH.h"
#include "Node.h"


Node::Node()
{
	m_Color = { .2f, .2f, .2f, .9f };
	m_TitleColor = {0.0f, .2f, 1.0f, .5f};
	m_Rounding = 5.0f;
	m_NumInputs = 0;
	m_NumOutputs = 0;
}

