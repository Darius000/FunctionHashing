#pragma once

#include "UIElement.h"
#include "imgui-node-editor/imgui_node_editor.h"
#include <rttr/type.h>
#include <Engine.h>

namespace ed = ax::NodeEditor;

class PinElement : public UIElement
{
public:
	PinElement(std::string_view name, ed::PinKind kind, rttr::property& property, rttr::instance& obj, bool canMultiConnect = false);

	ed::PinKind GetKind() const { return m_PinKind; }

	rttr::type GetType() const { return m_PinType; }

	bool CanMultiConnect() const { return m_CanMulitConnect; }

	virtual void OnBeginDraw() override;

	virtual void OnEndDraw() override;

private:
	ed::PinKind m_PinKind;

	rttr::type m_PinType = rttr::type::get<rttr::detail::invalid_type>();

	bool m_CanMulitConnect = false;

	int32_t m_Connections = 0;

	rttr::property m_Property;

	rttr::instance m_Object;
};

