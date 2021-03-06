#pragma once

#include "GraphElement.h"
#include "imgui-node-editor/imgui_node_editor.h"
#include <rttr/type.h>
#include <Engine.h>

namespace ed = ax::NodeEditor;


class PinElement : public GraphElement
{
public:
	PinElement(std::string_view name, ed::PinKind kind, const rttr::property& property, const rttr::instance& obj, bool canMultiConnect = false);

	ed::PinKind GetKind() const { return m_PinKind; }

	rttr::type GetType() const { return m_PinType; }

	virtual void OnConnected();

	virtual void OnDisConnected();

	bool OnShowContextMenu() override;

	void OnDestroyed() override;

	bool IsDeletable() override { return false; }

	bool CanMultiConnect() const { return m_CanMulitConnect; }

	void BeginLayout(uint64_t id) override;

	void EndLayout() override;

protected:
	ed::PinKind m_PinKind;

	rttr::type m_PinType = rttr::type::get<rttr::detail::invalid_type>();

	bool m_CanMulitConnect = false;

	int32_t m_Connections = 0;

	rttr::property m_Property;

	rttr::instance m_Object;

	class CircleElement* m_PinShape = nullptr;
};

