#include "BaseNode.h"

BaseNode::BaseNode(){}

BaseNode::~BaseNode() {}

void BaseNode::Execute() 
{
	if (!m_BeginExecution)
	{
		OnBeginExecute();

		m_BeginExecution = true;
	}
	
	OnExecute();

	OnEndExecute();

	m_BeginExecution = false;
}

void BaseNode::OnExecute()
{
	LOG_TRACE("Executing");
}
