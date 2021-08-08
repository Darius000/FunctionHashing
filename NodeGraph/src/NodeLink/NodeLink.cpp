#include "PCH.h"
#include "NodeLink.h"
#include "ImNodes/imnodes.h"

NodeLink::NodeLink()
	:m_Start_Ids(-1, -1), m_End_Ids(-1, -1)
{

}

NodeLink::NodeLink(int start_node, int start_attr, int end_node, int end_attr)
	:NodeEditorObject(), m_Start_Ids(start_node, start_attr), m_End_Ids(end_node, end_attr)
{

}

void NodeLink::Draw()
{
	ImNodes::Link(GetID(), m_Start_Ids.second, m_End_Ids.second);
}

bool NodeLink::IsConnected(int id) const
{
	return m_Start_Ids == id || m_End_Ids == id;
}
