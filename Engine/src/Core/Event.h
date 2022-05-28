#pragma once

#include "Core.h"
#include "Types/EnumMacros.h"

enum class EEventType
{
	None = 0,
	WindowClose, WindowResize,
	KeyPressed, KeyReleased, 
	MouseButtonPressed, MouseMoved, MouseScrolled, MouseButtonReleased,
	MouseHovered, MouseUnHovered
};

enum  class EEventCategory: int
{
	None = 0,
	Application = BIT(0),
	Input = BIT(1),
	KeyBoard = BIT(2),
	Mouse = BIT(3),
	MouseButton = BIT(4)
};

ENUM_BIT_OPERATORS(EEventCategory)

#define EVENT_CLASS_TYPE(type) static EEventType GetStaticType() { return EEventType::##type;}\
	virtual EEventType GetEventType() const override { return GetStaticType(); }\
	virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual EEventCategory GetCategoryFlags() const override { return EEventCategory::category; }

class Event
{
	friend class EventDispatcher;

public:
	virtual EEventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual EEventCategory GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	inline bool IsInCategory(EEventCategory category)
	{
		return GetCategoryFlags() & category;
	}

	bool m_Handled = false;
};

class EventDispatcher
{
	template<typename T>
	using EventCallback = bool(*)(T&);

public:
	EventDispatcher(Event& event)
		:m_Event(event)
	{
		
	}

	template<typename U, typename T>
	bool Dispatch(T* object, bool (T::* func)(U&))
	{
		if (m_Event.GetEventType() == U::GetStaticType())
		{
			m_Event.m_Handled = (object->*func)(*(U*)&m_Event);
			return true;
		}

		return false;
	}

private:
	Event& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}

#define BIND_EVENT(obj, x) [obj](auto&&... args)->decltype(auto){return obj->x(std::forward<decltype(args)>(args)...); }