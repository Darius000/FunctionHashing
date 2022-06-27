#pragma once

#include "Core/Core.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "UIElementStyle.h"
#include "BaseObject.h"
#include "ImGui/ImGuiOperators.h"

class LayoutSlot;

class UIElement : public BaseObject
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

	REFLECTABLEV(BaseObject)
};