#pragma once

#include "BaseObject.h"

class BlackBoardKey : public BaseObject
{
protected:
	BlackBoardKey() {};

	REFLECTABLEV()
};

template<typename T>
class TBlackBoardKey : public BlackBoardKey
{
public:
	TBlackBoardKey(std::string_view name);

	inline const T& GetValue() const { return m_Value; }

	void SetValue(T value);

	void SetToDefault();

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
