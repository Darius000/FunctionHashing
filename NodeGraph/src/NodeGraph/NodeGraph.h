#pragma once

#include "Core/Core.h"
#include "NodeLink/NodeLink.h"
#include "Nodes/Node.h"

class NodeGraph
{
	using NodeList = typename std::map<ImGuiID, Scope<class Node>>;
	using NodesSelected = typename std::vector<ImGuiID>;
	using NodeLinks = typename std::unordered_map<ImGuiID, Scope<class NodeLink>>;
	using PropertyList = std::vector<Ref<struct IProperty>>;

public:
	NodeGraph();

	template<typename...Args>
	void Instantiate(const std::string& name, Args... args)
	{
		auto newNode = NodeRegistry::Instaniate(name, args...);
		newNode->OnSelected.AddBinding([this](NodeEditorObject* obj)
		{
			if(m_SelectedObject != obj)
				m_SelectedObject = obj;
		});

		assert(newNode != nullptr);

		last_added_node = newNode->GetID();
		m_Nodes.emplace(newNode->GetID(), Scope<class Node>(newNode));
	}

	void Draw();


	//remove a node with the id
	void RemoveNode(typename ImGuiID id);

	void RemoveLinks(typename ImGuiID id);

	typename inline const ImGuiID& GetID() const { return m_ID; }

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

	void DrawSelectedPropertyWidget(class NodeEditorObject* prop);

	void DrawNodes();

	void DrawNodeLinks();

	//Creates the category hierarchy, returns when an item is clicked
	void DrawCategory(const struct CategoryList& list, bool* selected = 0);

	const bool IsEditorHovered() const;

	const bool IsAnyItemHovered() const;

private:

	//Check if node attrs are the same type float, boo, etc
	bool CanPinsConnect(struct Pin* s_attr, struct Pin* e_attr);

	void DeleteSelectedNodes();
	void DeleteSelectedLinks();
	void OnDestroyedLink(const int link_id);

private:
	static class NodeEditorObject* m_SelectedObject;

	bool m_Item_Hovered = false;

	typename ImGuiID last_added_node = 0;

	NodeList m_Nodes;

	PropertyList m_Properties;

	NodeLinks m_NodeLinks;

	struct ImDrawListSplitter splitter;

	typename ImGuiID m_ID;

	static ImGuiID s_ID;
};
