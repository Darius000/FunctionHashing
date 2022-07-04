#include "EdgeElement.h"

#include "Runtime/UI/Menu/Menu.h"

namespace ed = ax::NodeEditor;

EdgeElement::EdgeElement(const Ref<Edge>& edge)
	:m_Edge(edge)
{

}

void EdgeElement::BeginLayout(uint64_t id)
{
	auto ids = m_Edge->GetIds();
	ed::Link((uint64_t)GetID(), (uint64_t)ids.first, (uint64_t)ids.second);
}

bool EdgeElement::OnShowContextMenu()
{
	static ed::LinkId contextID = 0;
	ed::Suspend();
	bool opened = ed::ShowLinkContextMenu(&contextID);
	ed::Resume();
	return opened;
}

void EdgeElement::OnDestroyed()
{
	ed::DeleteLink((uint64_t)GetID());
}
