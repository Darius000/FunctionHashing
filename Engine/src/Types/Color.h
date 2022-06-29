#pragma once

#include "imgui.h"

class Color
{
public:
	Color()
		:r(1.0f), g(1.0f), b(1.0f), a(1.0f)
	{}

	Color(float _r, float _g, float _b, float _a = 1.0f)
		:r(_r), g(_g), b(_b), a(_a)
	{}

	Color(const ImVec4& color)
		:r(color.x), g(color.y), b(color.z), a(color.w)
	{

	}

	Color(const ImColor& color)
		:Color(color.Value)
	{

	}

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;

	Color& operator=(const Color& rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		a = rhs.a;

		return *this;
	}

	Color& operator=(const ImColor& rhs)
	{
		r = rhs.Value.x;
		g = rhs.Value.y;
		b = rhs.Value.z;
		a = rhs.Value.w;

		return *this;
	}

	Color& operator=(const ImVec4& rhs)
	{
		r = rhs.x;
		g = rhs.y;
		b = rhs.z;
		a = rhs.w;

		return *this;
	}

	bool operator==(const Color& rhs) const
	{
		return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
	}

	bool operator<(const Color& rhs) const
	{
		return r < rhs.r || g < rhs.g || b < rhs.b || a < rhs.a;
	}

	operator ImVec4()
	{
		return ImVec4(r, g, b, a);
	}

	operator ImColor()
	{
		return ImColor(r, g, b, a);
	}

	operator ImU32()
	{
		return *(ImColor*)(this);
	}
};

