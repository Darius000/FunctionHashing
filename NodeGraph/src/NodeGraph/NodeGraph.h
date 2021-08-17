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
	void Instantiate(const std::string& name, Args... args)
	{
		auto newNode = NodeRegistry::Instaniate(name, args...);
		newNode->OnSelected.AddBinding([this](NodeEditorObject* obj)
		{
			if(m_SelectedObject != obj)
				m_SelectedObject = obj;
		});

		assert(newNode != nullptr);

		m_Nodes.emplace(newNode->GetID(), Scope<class Node>(newNode));
	}

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

	void DrawNode(class Node* node);

	void DrawPin(ImGuiID id, EPinType pintype = EPinType::DataPin,
		float size = 6.0f, const ImVec4& color = ImGuiExtras::White, 
		const ImVec4& innercolor = ImGuiExtras::Black);

	void DrawPinTriangle(ImGuiID id, float size = 6.0f, const ImVec4& color = ImGuiExtras::White,
		const ImVec4& innercolor = ImGuiExtras::Black, const ImVec2& offset = ImVec2());

	void DrawInputs(class Node* node);

	void DrawOutputs(class Node* node);

	void DrawCommentResizeButton(class Comment* commentNode);

	void DrawNodeLinks();

	//Creates the category hierarchy, returns when an item is clicked

	void DrawCategory(const std::string& id, const struct CategoryList& list);

	template<typename Pred>
	void DrawCategory(const std::string& id, const struct CategoryList& list, Pred pred);

	Pin* FindPind(ImGuiID id);

	
private:

	bool m_OpenNodePopup;

	static class NodeEditorObject* m_SelectedObject;

	NodeList m_Nodes;

	PropertyList m_Properties;

	NodeLinks m_NodeLinks;

	float m_LinkThickness;

	float m_PinPadding;

	Ref<class Texture> m_HeaderTexture;

};
