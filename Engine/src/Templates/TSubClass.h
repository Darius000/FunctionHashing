#ifndef TSUBCLASS_H
#define TSUBCLASS_H

#include "Reflection/Reflection.h"
#include <concepts>

template<typename TClass>
class TSubClass
{
public:

	TSubClass() {};

	TSubClass(const TSubClass& other)
	{
		m_Class = other.Get();
	}

	template<typename U, typename = std::enable_if<std::derived_from<TClass, U>>>
	TSubClass(const TSubClass<U>& other)
	{
		m_Class = other.Get();
	}

	const rttr::type& Get() const { return m_Class; }

	template<typename... Args>
	TClass* Instaniate(Args... args)
	{
		if (!m_Class) return nullptr;

		return m_Class.create(std::forward<Args>(args)...).get_value<TClass*>();
	}

	TSubClass& operator=(const TSubClass& rhs)
	{
		m_Class = rhs.Get();

		return *this;
	}

	template<typename U, typename = std::enable_if<std::derived_from<U, TClass>>>
	TSubClass& operator=(const TSubClass<U>& rhs)
	{
		m_Class = rhs.Get();

		return *this;
	}
private:

	rttr::type m_Class = rttr::type::get<TClass>();
};

#endif
