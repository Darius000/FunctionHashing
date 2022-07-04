#pragma once

#include "Engine.h"
#include "BlackBoard/BlackBoard.h"
#include "Nodes/Node.h"
#include "UIElements/NodeElement.h"
#include "UIElements/EdgeElement.h"

using GraphElements = typename std::vector<Ref<class GraphElement>>;

class NodeGraph 
{
	
public:
	NodeGraph();

	void Instantiate(std::string_view name);

	void Draw();

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


	GraphElements m_Elements;

	BlackBoard m_BlackBoard;
};

