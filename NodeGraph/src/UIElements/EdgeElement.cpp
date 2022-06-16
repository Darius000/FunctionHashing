#include "EdgeElement.h"

EdgeElement::EdgeElement(const Ref<Edge>& edge)
	:m_Edge(edge)
{
}

void EdgeElement::OnDrawElement()
{
	auto ids = m_Edge->GetIds();
	ed::Link((uint64_t)GetID(), (uint64_t)ids.first, (uint64_t)ids.second);
}
