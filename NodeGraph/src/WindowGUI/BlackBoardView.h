#pragma once

#include "ImGui/ImGuiPanel.h"
#include "BlackBoard/BlackBoard.h"
#include "Renderer/Texture.h"

enum class EKeyContextMenuOptions
{
	Set,
	Get
};


class BlackBoardView : public ImGuiPanel
{
public:

	BlackBoardView(ImGuiID id);

	RetEngineEvent<BlackBoard*> OnGetBlackBoard;

	EngineEvent<const Ref<BlackBoardKey>& ,const EKeyContextMenuOptions&> OnOptionSelected;

	void OnRenderWindow() override;

	void DrawKey(const Ref<BlackBoardKey>& key);

	void CreateContextMenu(const Ref<BlackBoardKey>& key);

private:
	static Ref<Texture> s_CapsuleImage;
};
