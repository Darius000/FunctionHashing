#pragma once

#include "Core/Core.h"
#include "NodeEditorObject.h"

class NodeLink : public NodeEditorObject
{
public:
	NodeLink();
	NodeLink(int start_node, int start_attr, int end_node, int end_attr);

	void Draw();

	//first is node id, second is attr id
	std::pair<int, int> m_Start_Ids;
	std::pair<int, int> m_End_Ids;

	//Is it connected to a pin or node
	bool IsConnected(int id) const;
};
