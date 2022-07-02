#pragma once

#include "Core/Core.h"

class Selection
{
public:

	static void Select(const Ref<class BaseObject>& obj);

	static Ref<class BaseObject> Get()
	{
		return s_SelectedObject;
	}
	
private:

	static Ref<class BaseObject> s_SelectedObject;
};