#pragma once

#include "imgui.h"

template<typename T>
struct Value
{
	T value;

	Value()
	{
		value = T();
	}

	Value(T v)
	{
		value = v;
	}

	Value(const Value& other)
	{
		value = other.value;
	}

	Value operator=(const Value& rhs) 
	{
		value = rhs.value;
		return *this;
	}

	Value operator=(const T& rhs)
	{
		value = rhs;
		return *this;
	}

	bool operator==(const Value& rhs) const { return value == rhs.value; }
	bool operator==(const T& rhs) const { return value == rhs; }

	operator T()
	{
		return value;
	}
};

struct Color
{
	Value<float> r = 1.0f;
	Value<float> g = 1.0f;
	Value<float> b = 1.0f;
	Value<float> a = 1.0f;

	operator ImVec4()
	{
		return ImVec4(r, g, b, a);
	}
};

struct Position
{
	Value<float> top = 0.0f;
	Value<float> left = 0.0f;
	Value<float> right = 300.0f;
	Value<float> bottom = 100.0f;
};

struct Length
{

	Value<float> value = 0.0f;
};

struct FontSize
{
	Value<float> value = 13.0f;
};

struct FontStyle
{
	FontSize size { 13.0f };

	Color color {1.0f, 0.0f, 0.0f, 1.0f};

	ImFont* font{ ImGui::GetDefaultFont() };
};

struct ToolTipStyle
{
	FontStyle m_FontStyle;
};

struct HoveredStyle
{
	Color color = {.5f, .5f, .5f, 1.0f};

	ImGuiMouseCursor cursor = ImGuiMouseCursor_Hand;
};

enum class LayoutDirection : UINT8
{
	Column,
	ColumnReverse,
	Row,
	RowReverse
};

enum class Justify
{
	Start, //items packed at start
	Center, // center items along line
	End, //items packed at end
	SpaceBetween, //evenly distrubuted in the line
	SpaceAround //evenly distrubuted with equal space around the items
};

enum class Align
{
	Auto, //let Flex Decide
	Start, //start of itm is place at start of axis
	Center, //items are centered at axis
	End, // end of item placed at end axis
	Strecth // fill axis respecting min and max values
};

struct UIElementStyle
{
	Position m_Position;
	Color m_Color;
	HoveredStyle hoveredStyle;
	FontStyle m_FontStyle;
	ToolTipStyle m_ToolTipStyle;

	//Rounding
	Length m_BorderRadius;
	Length m_BorderWidth;
	Color m_BorderColor;
};