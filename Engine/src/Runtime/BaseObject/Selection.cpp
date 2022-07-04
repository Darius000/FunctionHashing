#include "PCH.h"
#include "Selection.h"
#include "BaseObject.h"

void Selection::Select(const Ref<class BaseObject>& obj)
{
	s_SelectedObject = obj;
	if (s_SelectedObject)
	{
		s_SelectedObject->OnDestroyedEvent.AddBinding([](BaseObject* objPtr) {
			if (s_SelectedObject.get() == objPtr)
			{
				s_SelectedObject = nullptr;
			}
			});
	}
}

Ref<class BaseObject> Selection::s_SelectedObject = nullptr;