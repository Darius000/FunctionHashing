#pragma once

#include "Core/Core.h"
#include "NodeEditorObject.h"
#include "imgui-node-editor/imgui_node_editor.h"

namespace ed = ax::NodeEditor;

struct Link
{
public:
	Link() {};
	Link(ed::PinId startpin, ed::PinId endpin);

	ed::PinId m_StartPin;
	ed::PinId m_EndPin;
};
