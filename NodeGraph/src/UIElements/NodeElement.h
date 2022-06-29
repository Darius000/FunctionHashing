#pragma once


#include "Runtime/UI/Elements/Layouts.h"
#include "Runtime/UI/Menu/Menu.h"
#include "PinElement.h"

class VerticalBox;

class NodeElement : public LayoutElement
{
public:
	NodeElement(class BaseNode* node);

	void BeginLayout(uint64_t id) override;

	void EndLayout() override;

	void SetPosition(const ImVec2& pos);

	class BaseNode* GetNode() { return m_Node;  }

	VerticalBox* GetInputs() { return m_InputContainer; }

	VerticalBox* GetOutputs() { return m_OutputContainer; }

protected:

	void AddPinElement(std::string_view name, ed::PinKind kind, const rttr::property& property, const rttr::instance& obj, bool canMultiConnect);


private:
	bool HandleEvents() override;

	void DrawToolTip(const std::string& text, ImDrawList* drawlist);

	void DrawSeperator(const ImVec2& position, const ImVec2& size, ImDrawList* drawlist);

	void DrawTitle(const std::string& title, const ImVec2& position, const ImVec2& size, ImDrawList* drawlist);

	void DrawHeader(const ImVec2& position, const ImVec2& size, const ImVec4& color, float rounding, ImDrawCornerFlags flags, ImDrawList* drawlist);

protected:

	VerticalBox* m_InputContainer = nullptr;

	VerticalBox* m_OutputContainer = nullptr;


	class BaseNode* m_Node = nullptr;

	Ref<class Menu> m_Menu;

};