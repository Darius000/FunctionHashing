#include "GraphElement.h"
#include "Runtime/UI/Menu/Menu.h"



GraphElement::GraphElement()
{
	auto items = std::vector<MenuItem>{
		MenuItem{ "Copy", [&]() {} },
		MenuItem{ "Delete", [&]() { 
			if (IsDeletable())
			{
				Destroy();
			}
	
		}}

	};

	m_Menu = MakeRef<Menu>("EdgeContextMenu", items);

	m_Menu->m_CanOpenMenuCallBack += [&]()
	{
		return OnShowContextMenu();
	};
}

void GraphElement::EndLayout()
{
	ed::Suspend();

	//context menu
	m_Menu->Show();

	ed::Resume();
}

//void GraphElement::OnDrawElement()
//{
//	
//}
