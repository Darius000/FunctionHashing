#pragma once

#include "Core/Event.h"
#include "KeyCodes.h"

class KeyEvent : public Event
{
public:
	inline EKeyCode GetKeyCode() const { return m_KeyCode; }

	EVENT_CLASS_CATEGORY(KeyBoard)

protected:
	KeyEvent(EKeyCode keycode)
	:m_KeyCode(keycode) {}

	EKeyCode m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(EKeyCode keycode, int repeatCount)
		:KeyEvent(keycode), m_RepeatCount(repeatCount){}

	inline int GetRepeatCount() const { return m_RepeatCount; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << (int32_t)m_KeyCode << "(" << m_RepeatCount << " repeats)";
		return ss.str().c_str();
	}

	EVENT_CLASS_TYPE(KeyPressed)

private:
	int m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:	
	KeyReleasedEvent(EKeyCode keycode)
		:KeyEvent(keycode){}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << (int32_t)m_KeyCode;
		return ss.str().c_str();
	}

	EVENT_CLASS_TYPE(KeyReleased)

};