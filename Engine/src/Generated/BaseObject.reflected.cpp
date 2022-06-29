#include "PCH.h"
#include "Reflection/Reflection.h"
#include "Runtime/BaseObject/BaseObject.h"


REFLECT_INLINE(BaseObject)
{
	rttr::registration::class_<BaseObject>("BaseObject")
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("Name", &BaseObject::GetName, &BaseObject::SetName, rttr::registration::public_access)
		.property("Pending Destroy", &BaseObject::m_PendingDestroy, rttr::registration::private_access)
		.property_readonly("ID", &BaseObject::GetID);
}