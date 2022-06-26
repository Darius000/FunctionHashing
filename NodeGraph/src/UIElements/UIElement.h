#pragma once

#include "Core/Core.h"
#include "NodeEditorObject.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "UIElementStyle.h"
#include "ImGuiExtensions.h"
#include "ImGui/ImGuiOperators.h"
#include "imgui-node-editor/imgui_node_editor.h"

namespace ed = ax::NodeEditor;

class LayoutSlot;

class UIElement : public NodeEditorObject
{
public:
	UIElement();

	UIElement(std::string_view name);

	virtual ~UIElement();

	virtual void DrawElement();

	virtual void OnDrawElement();

	ImVec2 GetPosition();

	ImVec2 GetLocalPosition();

	ImVec2 GetSize();

	virtual ImRect GetBounds();

	virtual void SetPosition(const ImVec2& pos);

	class LayoutElement* GetParent();

	UIElementStyle& GetStyle() { return m_Style; }

	ImVec2 GetCursorPos();

public:
	//Properties
	bool m_Interactive = true;

	bool m_Enabled = true;

	UIElementStyle m_Style;

protected:

	//adds item to imgui
	void AddElementItem();

	virtual bool HandleEvents();

protected:

	Ref<LayoutSlot> m_ParentSlot;

	friend class LayoutElement;
};