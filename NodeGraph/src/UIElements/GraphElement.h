#pragma once

#include "Runtime/UI/Elements/Layouts.h"
#include "imgui-node-editor/imgui_node_editor.h"

namespace ed = ax::NodeEditor;


class GraphElement : public LayoutElement
{
public:
	GraphElement();

	virtual ~GraphElement() = default;

	//virtual void OnDrawElement() override;

	virtual void EndLayout() override;

	virtual bool OnShowContextMenu() { return false; };

	virtual bool IsDeletable() { return true;  }

	Ref<class Menu> m_Menu;
};