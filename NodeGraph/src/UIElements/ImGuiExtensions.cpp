#include "ImGuiExtensions.h"

namespace ImGui
{
	void TextUnformatted(const char* text, const char* end, TextAlignment_ alignment, TextJustification_ justification)
	{
		auto pos = GetCursorPos();
		auto size = CalcTextSize(text, end);
		auto half_size = ImVec2(size.x / 2.0f, size.y / 2.0f);
		auto frame_padding = GetStyle().FramePadding;
		auto padding = ImVec2(frame_padding.x, frame_padding.y / 2.0f);

		ImVec2 new_pos = pos;

		if (alignment == TextAlignment_::Bottom)
		{
			new_pos.y += size.y - padding.y;
		}
		else if (alignment == TextAlignment_::Center)
		{
			new_pos.y += half_size.y - padding.y;
		}

		if (justification == TextJustification_::Right)
		{
			
		}
		else if (justification == TextJustification_::Center)
		{
			new_pos.x -= half_size.x - padding.x;
		}
		else if (justification == TextJustification_::Left)
		{
			new_pos.x -= size.x + padding.x ;
		}

		SetCursorPos(new_pos);
		TextUnformatted(text, end);
	}
}
