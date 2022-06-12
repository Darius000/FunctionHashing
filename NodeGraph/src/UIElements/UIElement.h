#pragma once

#include "Core//Core.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "UIElementStyle.h"
#include "imgui-node-editor/imgui_node_editor.h"
#include "Core/UUID/UUID.h"

namespace ed = ax::NodeEditor;

DECLARE_EVENT(OnHovered)
DECLARE_EVENT(OnUnHovered);
DECLARE_EVENT(OnClicked);


class UIElement
{
public:
	UIElement();

	virtual ~UIElement();

	virtual void DrawElement(ImDrawList* drawlist);

	virtual void OnDrawElement(ImDrawList* drawlist);

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

	const bool& IsHovered() const { return m_Hovered; }

	virtual const bool IsHoverable() const { return true; }

	virtual const bool IsClickable() const { return true; }

	const bool IsInteractive() const { return m_Interactive;  }

	UINT32 GetID() { return (UINT32)m_ID; }

public:
	//Properties

	std::string m_Name = "UIElement";

	std::string m_Title = "";

	std::string m_ToolTip = "";

	bool m_Interactive = true;

	bool m_Enabled = true;

	UIElementStyle m_Style;


public:

	//Begin Events

	FOnClickedEvent OnClickedEvent;

	FOnHoveredEvent OnHoveredEvent;

	FOnUnHoveredEvent OnUnHoveredEvent;

	//End Events


protected:

	//adds item to imgui
	void AddElementItem(const ImRect& bounds, ImGuiID id);

	bool HandleEvents();

	bool HandleEvents(const ImRect& bounds, ImGuiID id);

	void HandleHoveringEvent(const ImRect& bounds, ImGuiID id, bool& handled);

	void HandleClickEvent(const ImRect& bounds, ImGuiID id, bool& handled);

private:

	std::vector<Ref<UIElement>> m_Children;

	UIElement* m_ParentElement = nullptr;

	bool m_Hovered = false;

	bool m_PreviouslyHovered = false;

	Core::UUID m_ID;

protected:


	void DrawToolTip();
};