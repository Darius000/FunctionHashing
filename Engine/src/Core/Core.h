#pragma once


#include "Log/Log.h"
#include <memory>

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Scope<T> MakeScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T, typename ... Args>
constexpr Ref<T> MakeRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T, typename U>
constexpr T* Cast(U* t) noexcept
{
	return dynamic_cast<T*>(t);
}

template<typename T, typename U>
constexpr Ref<T> Cast(const Ref<U>& t) noexcept
{
	return std::dynamic_pointer_cast<T>(t);
}


template<typename T>
bool operator==(const std::pair<T, T>& p, const T& v)
{
	return p.first == v || p.second == v;
}

template <class U, class T>
struct is_convertible
{
	is_convertible(const U& a, const T& b)
	{

	}
	enum { value = std::is_convertible<U, T>::value };
};



#define  BIT(x) (1 << x)

#define CLASS(...)
#define PROPERTY(...)
#define FUNCTION(...)
#define ENUM()
#define VALUE(...)
#define STRUCT(...)

#include "Specifiers/MetaDataSpecifiers.h"
#include "Reflection/Reflection.h"
#include "Events/EventDelegate.h"
#include "Event.h"