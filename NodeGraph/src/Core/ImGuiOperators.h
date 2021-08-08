#pragma once

#include "imgui.h"

inline ImVec2 operator+(const ImVec2& a, const ImVec2& b)
{
	return { a.x + b.x, a.y + b.y };
}

inline ImVec2 operator-(const ImVec2& a, const ImVec2& b)
{
	return { a.x - b.x, a.y - b.y };
}


inline ImVec2& operator-=(ImVec2& a, const ImVec2& b)
{
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

template<typename T>
inline ImVec2 operator/(const ImVec2& a, const T& b)
{
	return { a.x / (float)b, a.y / (float)b };
}

template<typename T>
inline ImVec2 operator*(const ImVec2& a, const T& b)
{
	return { a.x * b, a.y * b };
}

template<typename T>
inline ImVec2& operator*=(ImVec2& a, const T& b)
{
	a.x *= b;
	a.y *= b;
	return a;
}


template<>
inline ImVec2 operator*(const ImVec2& a, const ImVec2& b)
{
	return { a.x * b.x, a.y * b.y };
}

inline ImVec2 operator/(const ImVec2& a, const ImVec2& b)
{
	return { a.x / b.x, a.y / b.y };
}

inline ImVec2& operator+=(ImVec2& a, const ImVec2& b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

inline bool operator>(const ImVec2& a, const ImVec2& b)
{
	return a.x > b.x && a.y > b.y;
}

inline bool operator<(const ImVec2& a, const ImVec2& b)
{
	return a.x < b.x && a.y < b.y;
}


inline ImVec4 operator+(const ImVec4& a, const ImVec4& b)
{
	return { a.x + b.x, a.y + b.y , a.z + b.z, a.w + b.w };
}

inline ImVec4 operator*(const ImVec4& a, const float& b)
{
	return { a.x * b, a.y * b , a.z * b, a.w };
}

template<typename T>
inline T& Clamp(T& val, const T& min, const T& max)
{
	if(val >= max)
		val = max;

	if(val <= min)
		val = min;

	return val;
}

#define IMU32(x)(int)(x * 255.0f)
#define IMVEC4TOIMU32(v) IM_COL32(IMU32(v.x), IMU32(v.y), IMU32(v.z), IMU32(v.w))
