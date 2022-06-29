#pragma once

#include "Core/Core.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "Types/Color.h"


struct FontStyle
{
	float size { 16.0f };

	Color color {1.0f, 1.0f, 1.0f, 1.0f};

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

enum class LayoutDirection : uint8_t
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
	ImVec2 m_Position;
	ImVec2 m_Size;
	Color m_Color;
	HoveredStyle hoveredStyle;
	FontStyle m_FontStyle;
	ToolTipStyle m_ToolTipStyle;

	//Rounding
	float m_BorderRadius;
	float m_BorderWidth;
	Color m_BorderColor;
};