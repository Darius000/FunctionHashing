#pragma once


#include "GraphElement.h"
#include "Edge/Edge.h"

class EdgeElement : public GraphElement
{
public:

	EdgeElement(const Ref<Edge>& edge);

	void BeginLayout(uint64_t id) override;

	bool OnShowContextMenu() override;

	void OnDestroyed() override;

	Ref<Edge> GetEdge() { return m_Edge; }

private:

	Ref<Edge> m_Edge;

	
};