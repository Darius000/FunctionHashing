#pragma once

#define ENUM_BIT_OPERATORS(EnumClass)\
namespace\
{\
	using EnumClass##Type = std::underlying_type<EnumClass>::type;\
	inline EnumClass operator |(EnumClass a, EnumClass b) \
		{ return static_cast<EnumClass>(static_cast<EnumClass##Type>(a) | static_cast<EnumClass##Type>(b)); }; \
	inline EnumClass##Type operator &(const EnumClass& a, const EnumClass& b) \
		{ return static_cast<EnumClass##Type>(a) & static_cast<EnumClass##Type>(b); }; \
	inline EnumClass& operator |=(EnumClass& a, EnumClass b) \
		{ return a = a | b; }; \
}