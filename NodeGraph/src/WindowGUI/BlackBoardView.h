#pragma once

#include "ImGui/ImGuiPanel.h"
#include "BlackBoard/BlackBoard.h"
#include "Texture/Texture.h"


class BlackBoardView : public ImGuiPanel
{
public:

	BlackBoardView(ImGuiID id);

	RetEngineEvent<BlackBoard*> OnGetBlackBoard;

	BlackBoardKey* GetSelectedKey() { return m_SelectedKey; }

	void OnRenderWindow() override;

	void DrawKey(Ref<BlackBoardKey>& key);

private:
	BlackBoardKey* m_SelectedKey = nullptr;

	static Ref<Texture> s_CapsuleImage;
};
