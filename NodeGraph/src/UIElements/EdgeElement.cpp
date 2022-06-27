#include "EdgeElement.h"
#include "imgui-node-editor/imgui_node_editor.h"

namespace ed = ax::NodeEditor;

EdgeElement::EdgeElement(const Ref<Edge>& edge)
	:m_Edge(edge)
{
}

void EdgeElement::OnDrawElement()
{
	auto ids = m_Edge->GetIds();
	ed::Link((uint64_t)GetID(), (uint64_t)ids.first, (uint64_t)ids.second);
}
