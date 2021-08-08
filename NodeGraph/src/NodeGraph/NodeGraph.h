#pragma once

#include "Core/Core.h"
#include "Core/Events/KeyEvents.h"
#include "Core/Events/MouseEvent.h"
#include "Nodes/Node.h"
#include "NodeLink/NodeLink.h"

class NodeGraph
{
	using NodeList = std::map<ImGuiID, Scope<class Node>>;
	using NodesSelected = std::vector<ImGuiID>;
	using NodeLinks = std::unordered_map<ImGuiID, Scope<NodeLink>>;
	using PropertyList = std::vector<Ref<struct IProperty>>;

public:
	NodeGraph();

	template<typename ... Args>
	void Instantiate(const std::string& name, Args... args)
	{
		auto newNode = NodeRegistry<Args...>::Instaniate(name, args...);

		assert(newNode != nullptr);

		last_added_node = newNode->GetID();
		m_Nodes.emplace(newNode->GetID(), Scope<Node>(newNode));
	}

	void Draw();


	//remove a node with the id
	void RemoveNode(ImGuiID id);

	void RemoveLinks(ImGuiID id);

	inline const ImGuiID& GetID() const { return m_ID; }

protected:
	//void RemoveVariable(Ref<class Property> var);

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

	void DrawSelectedPropertyWidget(struct IProperty* prop);

	void DrawNodes();

	void DrawNodeLinks();

	//Creates the category hierarchy, returns when an item is clicked
	void DrawCategory(const CategoryList& list, bool* selected = 0);

	const bool IsEditorHovered() const;

	const bool IsAnyItemHovered() const;

private:

	//Check if node attrs are the same type float, boo, etc
	bool CanPinsConnect(Pin* s_attr, Pin* e_attr);

	void DeleteSelectedNodes();
	void DeleteSelectedLinks();
	void OnDestroyedLink(const int link_id);

private:
	static struct IProperty* m_SelectedProperty;

	bool m_Item_Hovered = false;

	ImGuiID last_added_node = 0;

	NodeList m_Nodes;

	PropertyList m_Properties;

	NodeLinks m_NodeLinks;

	ImDrawListSplitter splitter;

	ImGuiID m_ID;

	static ImGuiID s_ID;
};
