#pragma once

#include "imgui.h"
#include "imgui_internal.h"

enum class TextJustification_
{
	Left,
	Center,
	Right
};

enum class TextAlignment_
{
	Top,
	Center,
	Bottom
};

namespace ImGui
{
	void TextUnformatted(const char* text, const char* end, TextAlignment_ alignment,
		TextJustification_ justification);
}