#pragma once

#include "Core/Core.h"

class GraphSerializer
{
public:
	GraphSerializer(const Ref<class NodeGraph>& graph);

	void Serialize(const std::string& filepath);

	void DeSerialize(const std::string& filepath);

private:
	Ref<class NodeGraph> m_Graph;
};
