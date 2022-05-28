#pragma once

#include "Core.h"
#include "EnumMacros.h"

// type to hold enum strings
//each enum type will declare its own specialization for Data
//error occurs when an enum does as a specialized template for data
template<typename EnumClass>
struct EnumStrings
{
	static std::vector<std::string> Data;
};

template<typename T, typename v = void>
struct EnumHasMax : std::false_type {};

template<typename T>
struct  EnumHasMax < T, decltype((void)T::Max) > : std::true_type {};

//template to get the max value of an enum, enum must have max as last value
template<typename EnumClass, typename std::enable_if<EnumHasMax<EnumClass>::value>::type* = nullptr>
struct EnumMax
{
	static constexpr unsigned int Max = static_cast<unsigned int>(EnumClass::Max);
};

template<typename EnumClass>
class TEnum
{

private:
	using Type = std::underlying_type_t<EnumClass>;

private:
	static EnumStrings<EnumClass> m_Strings;

	static EnumMax<EnumClass> m_Max;

public:
	TEnum() {
		m_Enum = static_cast<EnumClass>(0);
		m_EnumIndex = (Type)0;
	};

	TEnum(EnumClass e)
	{
		m_Enum = e;
		m_EnumIndex = static_cast<Type>(e);
	};

	TEnum(const TEnum& o)
	{
		m_Enum = o.m_Enum;
		m_EnumIndex = o.m_EnumIndex;
	};

	TEnum(TEnum&& o) noexcept
	{
		m_Enum = o.m_Enum;
		m_EnumIndex = o.m_EnumIndex;
	};

	//Get enum directly
	EnumClass Get() const 
	{
		return m_Enum;
	}

	unsigned int GetAsUInt() const 
	{
		return static_cast<unsigned int>(m_Enum);
	}

	//returns the max value of an enum
	static unsigned int GetMax()
	{
		return (unsigned int)m_Max.Max;
	};

	static std::vector<std::string> GetStrings() 
	{
		return m_Strings.Data;
	};

	std::string& ToString() const {
		return m_Strings.Data[m_EnumIndex];
	};

public:
	inline TEnum& operator=(const TEnum& o)
	{
		m_Enum = o.m_Enum;
		m_EnumIndex = o.m_EnumIndex;
		return *this;
	};

	inline TEnum& operator=(const EnumClass& o)
	{
		m_Enum = o;
		m_EnumIndex = static_cast<Type>(o);
		return *this;
	};

	inline bool operator==(const EnumClass& o) const
	{
		return m_Enum == o;
	};

	inline bool operator==(const TEnum& o) const
	{
		return m_Enum == o.m_Enum;
	};

	inline bool operator!=(const EnumClass& o) const
	{
		return m_Enum != o;
	};

	inline bool operator!=(const TEnum& o) const
	{
		return m_Enum != o.m_Enum;
	};

public:
	TEnum& operator++()
	{
		m_EnumIndex++;
		if(m_EnumIndex == m_Max.Max) m_EnumIndex = (Type)0;
		m_Enum = static_cast<EnumClass>(m_EnumIndex);
		return *this;
	};

	TEnum& operator++(int index)
	{
		++(*this);
		return *this;
	};

	TEnum& operator--(int index)
	{
		--(*this);
		return *this;
	};

	TEnum& operator--()
	{
		m_EnumIndex--;
		if (m_EnumIndex < 0) m_EnumIndex = m_Max.Max - (Type)1;
		m_Enum = static_cast<EnumClass>(m_EnumIndex);
		return *this;
	};

	//bit operators
	inline constexpr EnumClass operator |(const EnumClass& b) const
	{
		auto result = static_cast<Type>(m_Enum) | static_cast<Type>(b);
		return static_cast<EnumClass>(result);
	};

	inline constexpr Type operator &(const EnumClass& b) const
	{ 
		auto result = static_cast<Type>(m_Enum) & static_cast<Type>(b);
		return result;
	}

	inline constexpr EnumClass operator ^(const EnumClass& b) const
	{
		auto result = static_cast<Type>(m_Enum) ^ static_cast<Type>(b);
		return static_cast<EnumClass>(result);
	};
	
	inline constexpr TEnum& operator |=(const EnumClass& b)
	{ 
		return *this = *this | b; 
	};

	inline operator EnumClass() { return m_Enum; }
	

	//Write the enum class value as string
	template<typename T>
	friend std::ostream& operator<<(std::ostream& out, const TEnum<T>& data);

	friend struct std::hash<TEnum>;
private:
	static std::string Data[];

	int m_EnumIndex;
	EnumClass m_Enum;
};

template<typename EnumClass>
EnumMax<EnumClass> TEnum<EnumClass>::m_Max;

template<typename EnumClass>
EnumStrings<EnumClass> TEnum<EnumClass>::m_Strings;

//Write the enum class value as index value
template<typename T>
inline std::ostream& operator<<(std::ostream& out, const TEnum<T>& data)
{
	return out << data.m_EnumIndex;
}

namespace std
{
	//Hash map
	template<typename T>
	struct hash<TEnum<T>>
	{
		std::size_t operator()(const TEnum<T>& k) const
		{
			return (hash<TEnum<T>::Type>()(k.GetAsUInt()));
		}
	};
}


