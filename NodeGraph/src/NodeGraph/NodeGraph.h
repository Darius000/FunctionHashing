#pragma once

#include "Engine.h"
#include "BlackBoard/BlackBoard.h"
#include "Nodes/Node.h"
#include "UIElements/NodeElement.h"
#include "UIElements/EdgeElement.h"

using NodeList = typename std::vector<Scope<class NodeElement>>;
using Edges = typename std::vector<Scope<class EdgeElement>>;


class NodeGraph 
{
	
public:
	NodeGraph();

	void Instantiate(std::string_view name);

	void Draw();

	class BaseObject* GetSelectedObject();

	class BlackBoard* GetBlackBoard() { return &m_BlackBoard; }

private:

	class BaseObject* FindNodeByID(uint64_t id) const;

	class PinElement* FindPin(uint64_t pinid) const;

	virtual bool CanConnectPins(class PinElement* start, class PinElement* end, std::string& error);

	//context menu when editor is right-clicked
	void DrawNodeListContextMenu();

	void DrawElements();

protected:
	bool m_OpenNodePopup;

	class BaseObject* m_SelectedObject = nullptr;

	NodeList m_Nodes;

	Edges m_Edges;

	BlackBoard m_BlackBoard;
};

