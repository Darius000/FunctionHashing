#pragma once

#include "ImGui/ImGuiPanel.h"
#include "BlackBoard/BlackBoard.h"
#include "Renderer/Texture.h"

enum class EKeyContextMenuOptions
{
	Delete,
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

	void Spring(float w = 1.0f, float s = -1.0f);

private:
	static Ref<Texture> s_CapsuleImage;
};
