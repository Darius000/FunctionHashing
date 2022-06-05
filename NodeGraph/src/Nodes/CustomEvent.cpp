#include "PCH.h"
#include "CustomEvent.h"

CustomEventNode::CustomEventNode()
{
	m_Name = "Custom Event";
}

RTTR_REGISTRATION
{
	registration::class_<CustomEventNode>("CustomEvent")(metadata("Category", "Events | "), metadata("Description", "Begin a new Event"))
	.constructor<>()(policy::ctor::as_raw_ptr);

}