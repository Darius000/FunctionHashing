#pragma once


#include "Layouts.h"
#include "UI/GenericMenu.h"
#include "PinElement.h"


class NodeElement : public LayoutElement
{
public:
	NodeElement(class BaseNode* node);

	void BeginLayout(uint32_t id);

	void EndLayout();

	void SetPosition(const ImVec2& pos);

	class BaseNode* GetNode() { return m_Node;  }

	VerticalElement* GetInputs() { return m_InputContainer; }

	VerticalElement* GetOutputs() { return m_OutputContainer; }

protected:

	void AddPinElement(std::string_view name, ed::PinKind kind, rttr::property& property, rttr::instance& obj, bool canMultiConnect);


private:
	bool HandleEvents() override;

	void DrawToolTip(const std::string& text, ImDrawList* drawlist);

	void DrawSeperator(const ImVec2& position, const ImVec2& size, ImDrawList* drawlist);

	void DrawTitle(const std::string& title, const ImVec2& position, const ImVec2& size, ImDrawList* drawlist);

	void DrawHeader(const ImVec2& position, const ImVec2& size, const ImVec4& color, float rounding, ImDrawCornerFlags flags, ImDrawList* drawlist);

protected:

	VerticalElement* m_InputContainer = nullptr;

	VerticalElement* m_OutputContainer = nullptr;


	class BaseNode* m_Node = nullptr;

	Ref<class UI::GenericMenu> m_Menu;

};