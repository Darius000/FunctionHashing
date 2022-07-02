#pragma once

#include "ImGui/ImGuiPanel.h"
#include "BlackBoard/BlackBoard.h"
#include "Renderer/Texture.h"


class BlackBoardView : public ImGuiPanel
{
public:

	BlackBoardView(ImGuiID id);

	RetEngineEvent<BlackBoard*> OnGetBlackBoard;

	void OnRenderWindow() override;

	void DrawKey(Ref<BlackBoardKey>& key);

private:
	static Ref<Texture> s_CapsuleImage;
};
