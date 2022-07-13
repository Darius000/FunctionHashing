#pragma once

#include "Runtime/BaseObject/BaseObject.h"

class BlackBoardKey : public BaseObject
{
protected:
	BlackBoardKey() {};

	REFLECTABLEV(BaseObject)
};

template<typename T>
class TBlackBoardKey : public BlackBoardKey
{
public:
	TBlackBoardKey(std::string_view name);

	TBlackBoardKey(const TBlackBoardKey&& other)
	{
		m_Value = other.m_Value;
	}

	inline const T& GetValue() const { return m_Value; }

	void SetValue(T value);

	void SetToDefault();

	TBlackBoardKey& operator=(const TBlackBoardKey& rhs)
	{
		m_Value = rhs.m_Value;

		return *this;
	}

private:

	T m_Value;

	REFLECTABLEV(BlackBoardKey)
};


template<typename T>
inline TBlackBoardKey<T>::TBlackBoardKey(std::string_view name)
	:m_Value()
{
	m_Name = name.data();
}

template<typename T>
inline void TBlackBoardKey<T>::SetValue(T value)
{
	m_Value = value;
}

template<typename T>
inline void TBlackBoardKey<T>::SetToDefault()
{
	m_Value = T();
}
