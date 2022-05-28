#pragma once

#include "Core/Event.h"

class HoveredEvent : public Event
{
public:

	HoveredEvent()
	{

	}

	EVENT_CLASS_TYPE(MouseHovered)
	EVENT_CLASS_CATEGORY(Mouse)

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MousedHoveredEvent: ";
		return ss.str().c_str();
	}
};

class UnHoveredEvent : Event
{
public:

	UnHoveredEvent()
	{

	}

	EVENT_CLASS_TYPE(MouseUnHovered)
	EVENT_CLASS_CATEGORY(Mouse)

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MousedUnHoveredEvent: ";
		return ss.str().c_str();
	}
};