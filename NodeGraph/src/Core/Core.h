#pragma once

#include "ImGuiOperators.h"
#include "ImguiExtras.h"
#include "Log/Log.h"

#include <memory>

template<typename T>
void Print(const T* msg)
{
	std::cout << msg << "\n";
}

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
constexpr T* Cast(U* t)
{
	return dynamic_cast<T*>(t);
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

#include "Events/EventDelegate.h"
#include "Event.h"