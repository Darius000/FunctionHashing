#pragma once

#include "Core/Event.h"
#include "MouseCodes.h"

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float x, float y)
		:m_MouseX(x), m_MouseY(y)
		{
			m_DeltaX = m_MouseX - m_OldMouseX;
			m_DeltaY = m_MouseY - m_OldMouseY;

			m_OldMouseX = m_MouseX;
			m_OldMouseY = m_MouseY;
		}

	inline float GetX() const { return m_MouseX; }
	inline float GetY() const { return m_MouseY; }
	inline float GetDeltaX() const { return m_DeltaX; }
	inline float GetDeltaY() const { return m_DeltaY; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MousedMovedEvent: " << m_MouseX << ", " << m_MouseY;
		return ss.str().c_str();
	}

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(Mouse)

private:
	float m_MouseX, m_MouseY;
	float m_DeltaX, m_DeltaY;

	static float m_OldMouseX;
	static float m_OldMouseY;
};


class  MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float xOffset, float yOffset)
		:m_XOffset(xOffset), m_YOffset(yOffset) {}

	inline float GetXOffset() const { return m_XOffset; }
	inline float GetYOffset() const { return m_YOffset; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MousedScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
		return ss.str().c_str();
	}

	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY(Mouse)

private:
	float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event
{
public:
	inline EMouseButton GetMouseButton() const { return m_Button; }

	EVENT_CLASS_CATEGORY(Mouse)

protected:
	MouseButtonEvent(EMouseButton button)
		:m_Button(button) {}

	EMouseButton m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(EMouseButton button)
		:MouseButtonEvent(button) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << (int32_t)m_Button;
		return ss.str().c_str();
	}

	EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(EMouseButton button)
		:MouseButtonEvent(button) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << (int32_t)m_Button;
		return ss.str().c_str();
	}

	EVENT_CLASS_TYPE(MouseButtonReleased)
};