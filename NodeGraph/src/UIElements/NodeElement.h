#pragma once


#include "UIElement.h"
#include "UI/GenericMenu.h"
#include "PinElement.h"


class NodeElement : public UIElement
{
public:
	NodeElement(class BaseNode* node);

	void OnBeginDraw() override;

	void OnEndDraw() override;

	void SetPosition(const ImVec2& pos);

	class BaseNode* GetNode() { return m_Node;  }

private:
	bool HandleEvents() override;

	void DrawToolTip(const std::string& text, ImDrawList* drawlist);

	void DrawSeperator(const ImVec2& position, const ImVec2& size, ImDrawList* drawlist);

	void DrawTitle(const std::string& title, const ImVec2& position, const ImVec2& size, ImDrawList* drawlist);

	void DrawHeader(const ImVec2& position, const ImVec2& size, const ImVec4& color, float rounding, ImDrawCornerFlags flags, ImDrawList* drawlist);

protected:

	class BaseNode* m_Node = nullptr;

	Ref<class UI::GenericMenu> m_Menu;

};