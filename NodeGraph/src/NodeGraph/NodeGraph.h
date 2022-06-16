#pragma once

#include "Core/Core.h"
#include "NodeLink/Link.h"
#include "Nodes/Node.h"
#include "UIElements/NodeElement.h"

class NodeGraph 
{
	using NodeList = typename std::vector<Scope<class NodeElement>>;
	using NodesSelected = typename std::vector<ImGuiID>;
	using Edges = typename std::vector<Scope<class EdgeElement>>;
	using PropertyList = std::vector<Ref<struct IProperty>>;

public:
	NodeGraph();

	void Instantiate(std::string_view name);

	void Draw();

	class NodeEditorObject* GetSelectedObject() { return m_SelectedObject; }


private:

	class NodeEditorObject* FindNodeByID(uint64_t id) const;

	class PinElement* FindPin(uint64_t pinid) const;

	void DrawVariableList();

	virtual bool CanConnectPins(class PinElement* start, class PinElement* end, std::string& error);

	//draw the menu to create a new property
	void DrawAddNewProperty();

	//context menu when editor is right-clicked
	void DrawNodeListContextMenu();

	//the list of properties in a new window
	void DrawVariableListProp(Ref<struct IProperty> prop);

	void DrawSelectedPropertyWidget(class NodeEditorObject* prop);

	void DrawElements();

	//Creates the category hierarchy, returns when an item is clicked

	//Ref<IProperty> FindProperty(ImGuiID id);


protected:
	bool m_OpenNodePopup;

	class NodeEditorObject* m_SelectedObject = nullptr;

	NodeList m_Nodes;

	PropertyList m_Properties;

	Edges m_Edges;

	friend class GraphSerializer;
};

