#include "EdgeElement.h"
#include "imgui-node-editor/imgui_node_editor.h"
#include "Runtime/UI/Menu/Menu.h"

namespace ed = ax::NodeEditor;

EdgeElement::EdgeElement(const Ref<Edge>& edge)
	:m_Edge(edge)
{
	MenuItem copy{ "Copy", []() {} };

	MenuItem deleteItem{ "Delete", [&]() {
		ed::DeleteLink((uint64_t)GetID());
	} };

	m_Menu = MakeRef<Menu>("EdgeContextMenu");
	m_Menu->AddMenuItem(copy);
	m_Menu->AddMenuItem(deleteItem);
	m_Menu->m_CanOpenMenuCallBack += []()
	{
		static ed::LinkId contextID = 0;
		ed::Suspend();
		bool opened = ed::ShowLinkContextMenu(&contextID);
		ed::Resume();
		return opened;
	};
}

void EdgeElement::OnDrawElement()
{
	auto ids = m_Edge->GetIds();
	ed::Link((uint64_t)GetID(), (uint64_t)ids.first, (uint64_t)ids.second);


	ed::Suspend();

	//context menu
	m_Menu->Show();

	ed::Resume();
}
