#pragma once

#include "Core/Core.h"
#include "NodeEditorObject.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "UIElementStyle.h"
#include "ImGuiExtensions.h"
#include "imgui-node-editor/imgui_node_editor.h"

namespace ed = ax::NodeEditor;

class UIElement : public NodeEditorObject
{
public:
	UIElement();

	virtual ~UIElement();

	virtual void OnBeginDraw() {};

	virtual void OnEndDraw() {};

	void DrawElement();

	virtual void OnDrawElement() {};

	void AddChild(UIElement* element);

	void RemoveElement(UIElement* element);

	void RemoveElement(const std::string& name);

	std::vector<Ref<UIElement>>& GetChildren() { return m_Children; }

	size_t GetChildCount() const { return m_Children.size(); }

	void Clear();

	ImVec2 GetPosition();

	ImVec2 GetLocalPosition();

	ImVec2 GetSize();

	ImRect GetBounds();

	virtual void SetPosition(const ImVec2& pos);

	UIElement* GetParent() { return m_ParentElement; }

public:
	//Properties
	bool m_Interactive = true;

	bool m_Enabled = true;

	UIElementStyle m_Style;

protected:

	//adds item to imgui
	void AddElementItem(const ImRect& bounds, ImGuiID id);

	virtual bool HandleEvents();

private:

	std::vector<Ref<UIElement>> m_Children;

	UIElement* m_ParentElement = nullptr;
};