#pragma once

#include "Core/Core.h"
#include "DataTypes/TypeTraits.h"


struct FunctionWrapper
{
	template<typename ... Args>
	void* Invoke(Args&&... args) { throw "Not Supported!"; };

	template<typename T, typename ... Args>
	Scope<class Node> InvokeObj(T* obj, Args&&... args) { throw "Not Supported!"; };

	virtual ~FunctionWrapper() {};

protected:
	FunctionWrapper() {}
};

//for static and loose functions
template<typename ReturnType, typename ...Args>
struct FunctionWrapperT : public FunctionWrapper
{
	using TFunc = ReturnType(*)(Args... args);

	FunctionWrapperT(TFunc func) : m_func(func) {}

	template<typename ... Args>
	Scope<class Node> Invoke(Args&&... args) { return m_func(std::forward<Args>(args)...); }

private:
	TFunc m_func;
};

//for class methods
template<typename T, typename ReturnType, typename ...Args>
struct ClassMethodWrapperT : public FunctionWrapper
{
	using TFunc = ReturnType(T::*)(Args... args);

	ClassMethodWrapperT(TFunc func) : m_Func(func) {}

	template<typename ... Args>
	Scope<class Node> InvokeObj(T* obj, Args... args) { (obj->*m_Func)(std::forward<Args>(args)...); }

	TFunc m_Func;
};

template<typename ... Args>
Scope<class Node> Invoke(FunctionWrapper* obj, Args&&... args)
{
	return obj->InvokeObj(obj, args...);
};
