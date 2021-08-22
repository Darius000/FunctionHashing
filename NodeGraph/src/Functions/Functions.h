#pragma once

#include "Core/Core.h"


struct Function
{
	virtual ~Function() = default;
};

template<typename ReturnType, typename... Args>
struct FunctionWrapperBase : public Function
{
	using R = ReturnType;
	using ArgTypes =  std::tuple<Args...>;
	static constexpr size_t ArgCount = sizeof...(Args);
	template<size_t N>
	using NthArg = std::tuple_element_t<N, ArgTypes>;
};

template<typename F> struct FunctionWrapper{

};


//free floating or static function
template<typename ReturnType, typename... Args>
struct FunctionWrapper<ReturnType(*)(Args...)> : public
	FunctionWrapperBase<ReturnType, Args...>
{	
	using Pointer = ReturnType(*)(Args...);

	explicit FunctionWrapper(Pointer func)
	{
		m_Func = func;
	}

	FunctionWrapper(const FunctionWrapper& other)
	{
		m_Func = other.m_Func;
	}

	FunctionWrapper& operator=(const FunctionWrapper& rhs)
	{
		m_Func = rhs.m_Func;
	}
	
	R operator()(Args... args){return std::invoke(m_Func, args...); }

	Pointer m_Func;
};

//non method const version
template<typename T, typename ReturnType, typename... Args>
struct FunctionWrapper<ReturnType(T::*)(Args...)> : public
	FunctionWrapperBase<ReturnType, Args...>
{
	using Pointer = ReturnType(T::*)(Args...);

	explicit FunctionWrapper(Pointer func)
	{
		m_Func = func;
	}

	FunctionWrapper(const FunctionWrapper& other)
	{
		m_Func = other.m_Func;
	}

	FunctionWrapper& operator=(const FunctionWrapper& rhs)
	{
		m_Func = rhs.m_Func;
	}

	typename FunctionWrapperBase::R operator()(T& obj, Args... args) { return std::invoke(m_Func, obj, args...); }
	typename FunctionWrapperBase::R operator()(T* obj, Args... args) { return std::invoke(m_Func, obj, args...); }

	Pointer m_Func;
};

//const method version
template<typename T, typename ReturnType, typename... Args>
struct FunctionWrapper<ReturnType(T::*)(Args...) const> : public
	FunctionWrapperBase<ReturnType, Args...>
{
	using Pointer = ReturnType(T::*)(Args...) const;

	explicit FunctionWrapper(Pointer func)
	{
		m_Func = func;
	}

	FunctionWrapper(const FunctionWrapper& other)
	{
		m_Func = other.m_Func;
	}

	FunctionWrapper& operator=(const FunctionWrapper& rhs)
	{
		m_Func = rhs.m_Func;
	}

	
	typename FunctionWrapperBase::R operator()(const T& obj, Args... args) { return std::invoke(m_Func, obj, args...); }
	typename FunctionWrapperBase::R operator()(const T* obj, Args... args) { return std::invoke(m_Func, obj, args...); }

	Pointer m_Func;
};


#define DEFINE_FUNCTION_WRAPPER(name, x)\
	namespace name\
	{\
		using Type = FunctionWrapper<decltype(&x)>;\
		static FunctionWrapper<decltype(&x)> ptr(&x);\
	}
	
