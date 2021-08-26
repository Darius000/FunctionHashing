#pragma once

#include "Core/Core.h"
#include "NodeLink/Link.h"
#include "Nodes/Node.h"


class NodeGraph 
{
	using NodeList = typename std::map<ImGuiID, Scope<class Node>>;
	using NodesSelected = typename std::vector<ImGuiID>;
	using NodeLinks = typename std::unordered_map<ImGuiID, Scope<struct Link>>;
	using PropertyList = std::vector<Ref<struct IProperty>>;

public:
	NodeGraph();

	template<typename...Args>
	void Instantiate(const std::string& name, Args... args);

	void Draw();

private:
	//Draws the window that displays the node menu
	void DrawNodeList();

	void DrawVariableList();

	//draw the menu to create a new property
	void DrawAddNewProperty();

	//context menu when editor is right-clicked
	void DrawNodeListContextMenu();

	//the list of properties in a new window
	void DrawVariableListProp(Ref<struct IProperty> prop);

	void DrawSelectedPropertyWidget(class NodeEditorObject* prop);

	void DrawNodes();

	void DrawNodeLinks();

	//Creates the category hierarchy, returns when an item is clicked

	void DrawCategory(const std::string& id, const struct CategoryList& list);

	template<typename Pred>
	void DrawCategory(const std::string& id, const struct CategoryList& list, Pred pred);

	Pin* FindPind(ImGuiID id);

	
protected:
	bool m_OpenNodePopup;

	class NodeEditorObject* m_SelectedObject = nullptr;

	NodeList m_Nodes;

	PropertyList m_Properties;

	NodeLinks m_NodeLinks;

	friend class GraphSerializer;
};

template<typename... Args>
void NodeGraph::Instantiate(const std::string& name, Args... args)
{
	auto newNode = NodeRegistry::Instaniate(name, args...);

	assert(newNode != nullptr);

	auto id = newNode->GetID();

	m_Nodes.emplace(id, Scope<class Node>(newNode));

	ed::CenterNodeOnScreen(id);
}
