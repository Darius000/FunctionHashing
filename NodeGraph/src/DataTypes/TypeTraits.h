#pragma once

#include "PCH.h"
#include "Core\Core.h"
#include <baseaudioprocessingobject.h>

template<typename T>
struct RemovePointer
{
	using type = T;
};

template<typename T>
struct RemovePointer<T*>
{
	using type = T;
};

template<typename T>
struct RemoveConst
{
	using type = T;
};

template<typename T>
struct RemoveConst<const T>
{
	using type = T;
};

template<typename Base, typename Derived>
struct Type 
{ 
	using type = Derived;
	static Scope<Base> Create()
	{
		return MakeScope<Derived>();
	}
};

template <typename T>
struct id { using type = T; };



//template test to deduce enum underlying type is integral
template<typename T, typename v = void>
struct Test : std::false_type{};

template<typename T>
struct  Test<T, decltype((void)+T{})> : std::true_type{};


//template to determine if enum is scoped or not
template<typename T>
using is_enum_class = std::integral_constant<bool, !Test<T>::value && std::is_enum<T>::value>;

template<typename T>
using is_pointer_or_ref = std::integral_constant<bool, std::is_pointer<T>::value ||
	(std::is_lvalue_reference<T>::value &&
	!std::is_const<typename std::remove_reference<T>::type>::value)>;

template<typename... Conds>
struct and_ : std::true_type {};

template<typename Cond, typename ... Conds>
struct and_<Cond, Conds...> :
	std::conditional<Cond::value, and_<Conds...>, ::std::false_type>::type {};

template<typename ...Ts>
using are_pointer_or_ref = and_<is_pointer_or_ref<Ts>...>;