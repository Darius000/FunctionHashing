#pragma once

#include <rttr/registration.h>
#include <rttr/type.h>
#include <rttr/rttr_enable.h>
#include <rttr/registration_friend.h>

#define CAT_IMPL_(a, b) a##b
#define CAT(a, b) CAT_IMPL_(a, b)

#ifdef __COUNTER__
#define ANONYMOUS_VARIABLE(str) CAT(str, CAT(__COUNTER__, CAT(__LINE__, __COUNTER__)))
#else
#define ANONYMOUS_VARIABLE(str) CAT(str, __LINE__)
#endif


namespace refl_detail
{
	template<typename T>
	inline int get_reg(void(*f)())
	{
		static const int s = [&f]()
		{
			f();
			return 0;
		}();

		return s;
	}
}

#define REFLECT_INLINE(class_)\
	template<typename T>\
	extern void rttr_auto_register_reflection_function_t();\
	template<>\
	void rttr_auto_register_reflection_function_t<class_>();\
	static const int ANONYMOUS_VARIABLE(auto_register__) = \
		refl_detail::get_reg<class_>(&rttr_auto_register_reflection_function_t<class_>);\
	template<>\
	inline void rttr_auto_register_reflection_function_t<class_>()

#define REFLECT_EXTERN(cls)                                                                                  \
	template <typename T>                                                                                    \
	extern void rttr_auto_register_reflection_function_t();                                                  \
	template <>                                                                                              \
	void rttr_auto_register_reflection_function_t<cls>();                                                    \
	static const int ANONYMOUS_VARIABLE(auto_register__) = []() {                                            \
		rttr_auto_register_reflection_function_t<cls>();                                                     \
		return 0;                                                                                            \
	}();


#define REFLECT(class_)\
	template<>\
		void rttr_auto_register_reflection_function_t<class_>()

#define RTTR_REGISTRATION_FRIEND_NON_INTRUSIVE()\
	template <typename T>\
	friend void rttr_auto_register_reflection_function_t();\
	RTTR_REGISTRATION_FRIEND

#define EXPAND(x) x
#define REFLECTABLE_VIRTUAL_IMPL(...)\
	RTTR_REGISTRATION_FRIEND_NON_INTRUSIVE()\
	RTTR_ENABLE(__VA_ARGS__)\
public:

#define REFLECTABLE() RTTR_REGISTRATION_FRIEND_NON_INTRUSIVE()
#define REFLECTABLEV(...) EXPAND(REFLECTABLE_VIRTUAL_IMPL(__VA_ARGS__))

#define COMMA ,

#include "MetaDataSpecifiers.h"