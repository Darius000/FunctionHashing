#pragma once


#include "Runtime/UI/Elements/UIElement.h"
#include "Edge/Edge.h"

class EdgeElement : public UIElement
{
public:

	EdgeElement(const Ref<Edge>& edge);

	void OnDrawElement() override;

	Ref<Edge> GetEdge() { return m_Edge; }

	bool HandleEvents() override;

private:

	Ref<Edge> m_Edge;

	Ref<class Menu> m_Menu;
};