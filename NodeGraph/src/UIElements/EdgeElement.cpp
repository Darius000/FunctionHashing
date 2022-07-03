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
}

void EdgeElement::OnDrawElement()
{
	auto ids = m_Edge->GetIds();
	ed::Link((uint64_t)GetID(), (uint64_t)ids.first, (uint64_t)ids.second);

	
}

bool EdgeElement::HandleEvents()
{
	bool handled = UIElement::HandleEvents();

	if (!handled)
	{
		static ed::LinkId contextID = 0;
		ed::Suspend();
		if (ed::ShowLinkContextMenu(&contextID))
		{
			m_Menu->OpenMenu();

		}
		ed::Resume();

		ed::Suspend();

		//context menu
		handled = m_Menu->ShowAsContext();

		ed::Resume();
	}


	return handled;
}
