#pragma once

#include "Nodes/Node.h"

class NodeBuilder
{
public:
	NodeBuilder(class Node* node);


	void DrawNode();

private:
	void DrawPin(typename ImGuiID id, EPinType pintype = EPinType::DataPin,
		float size = 6.0f, const ImVec4& color = ImGuiExtras::White,
		const ImVec4& innercolor = ImGuiExtras::Black);

	void DrawPinTriangle(ImGuiID id, float size = 6.0f, const ImVec4& color = ImGuiExtras::White,
		const ImVec4& innercolor = ImGuiExtras::Black, const ImVec2& offset = ImVec2());

	void DrawInputs();

	void DrawOutputs();

	void DrawCommentResizeButton(class Comment* commentNode);

	class Node* m_CurrentNode = nullptr;

	static float m_PinPadding;

	static Ref<class Texture> m_HeaderTexture;
};


class LinkBuilder
{
public:
	LinkBuilder(struct Link* link);

	void Draw();

	static float m_LinkThickness;

private:
	struct Link* m_CurrentLink = nullptr;
};