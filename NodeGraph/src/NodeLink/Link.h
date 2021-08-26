#pragma once

#include "Core/Core.h"
#include "NodeEditorObject.h"
#include "NodeEditor/imgui_node_editor.h"

namespace ed = ax::NodeEditor;

struct Link : public NodeEditorObject
{
public:
	Link() {};
	Link(ed::PinId startpin, ed::PinId endpin);

	ed::PinId m_StartPin;
	ed::PinId m_EndPin;

	virtual void Serialize(YAML::Emitter& out) override;

	virtual void DeSerialize(YAML::detail::iterator_value& value) override;
};
