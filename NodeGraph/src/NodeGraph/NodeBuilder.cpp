#include "PCH.h"
#include "NodeBuilder.h"
#include "imgui.h"
#include "Nodes\CommentNode.h"
#include "Core\Texture\Texture.h"
#include "NodeLink\Link.h"

NodeBuilder::NodeBuilder(class Node* node)
{
	m_CurrentNode = node;

	if(!m_HeaderTexture) m_HeaderTexture = MakeRef<Texture>("resources/raw_perlin.png");
}


void NodeBuilder::DrawNode()
{
	auto id = m_CurrentNode->GetID();


	ed::PushStyleColor(ed::StyleColor_NodeBg, m_CurrentNode->m_Color);
	ed::PushStyleVar(ed::StyleVar_NodeRounding, m_CurrentNode->m_Rounding);
	ed::PushStyleVar(ed::StyleVar_PinBorderWidth, 3.0f);

	bool hasheader = m_CurrentNode->GetNodeType() != ENodeType::Simple;
	bool hasInputs = m_CurrentNode->m_NumInputs > 0;
	bool hasOutputs = m_CurrentNode->m_NumOutputs > 0;

	ed::BeginNode(id);


	ImGui::PushID(id);

	ImGui::BeginVertical("node");

	if (hasheader)
	{
		ImGui::BeginHorizontal("header");

		if (m_CurrentNode->GetNodeType() != ENodeType::Comment)
		{
			ImGui::TextUnformatted(m_CurrentNode->GetTypeName().c_str());
		}
		else
		{
			auto comment = Cast<Comment>(m_CurrentNode);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGuiExtras::Clear);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImGuiExtras::Clear);
			ImGui::SetNextItemWidth(comment->m_Size.x);

			auto& str = comment->m_Comment;
			auto textSize = ImGui::CalcTextSize(str.c_str());

			auto cursorpos = ImGui::GetCursorPosY();
			ImGui::SetCursorPosY(cursorpos -textSize.y / 2.0f);

			if (ImGui::InputText("", &str))
			{
				comment->m_Comment = str;
			}
			ImGui::PopStyleColor(2);
		}

		ImGui::EndHorizontal();

	}

	ImGui::BeginHorizontal("content");
	if (m_CurrentNode->GetNodeType() != ENodeType::Comment)
	{

		if (hasInputs)
		{
			DrawInputs();
		}
		else
		{
			ImGui::Spring();
		}

		if (!hasheader)
		{
			ImGui::BeginVertical("custom");
			ImGui::Spring();
			ImGui::TextUnformatted(m_CurrentNode->GetTypeName().c_str());
			ImGui::Spring();
			ImGui::EndVertical();
		}

		if (hasOutputs)
		{
			DrawOutputs();
		}
	}
	else
	{
		auto comment = Cast<Comment>(m_CurrentNode);
		ImGui::Dummy(comment->m_Size);
	}


	ImGui::EndHorizontal();

	ImGui::EndVertical();

	ImGui::PopID();


	ed::EndNode();

	ed::PopStyleVar(2);
	ed::PopStyleColor();

	//Draw header
	if (hasheader)
	{
		auto drawlist = ed::GetNodeBackgroundDrawList(id);
		auto pos = ed::GetNodePosition(id);
		auto size = ed::GetNodeSize(id);
		auto node_border_width = ed::GetStyle().NodeBorderWidth;

		drawlist->AddLine(pos + ImVec2(0.0f, 28.0f) + ImVec2(node_border_width, -node_border_width),
			pos - ImVec2(node_border_width, node_border_width)
			+ ImVec2(size.x, 28.0f), ImColor(ImGuiExtras::White));

		drawlist->AddImageRounded((void*)m_HeaderTexture->GetRenderID(),
			pos + ImVec2(node_border_width, node_border_width),
			pos - ImVec2(node_border_width, node_border_width)
			+ ImVec2(size.x, 28.0f), ImVec2(0, 0), ImVec2(1, .2f),
			ImColor(m_CurrentNode->m_TitleColor), m_CurrentNode->m_Rounding, ImDrawCornerFlags_Top);

	}

	if (m_CurrentNode->GetNodeType() == ENodeType::Comment)
	{
		auto comment = Cast<Comment>(m_CurrentNode);
		DrawCommentResizeButton(comment);
	}
}

void NodeBuilder::DrawPin(typename ImGuiID id, EPinType pintype, float size , const ImVec4& color , const ImVec4& innercolor )
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *ImGui::GetCurrentContext();
	ImDrawList* drawlist = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetCursorScreenPos();
	ImRect bounds;

	auto TotalSize = ImVec2(size, size) * 2;
	ImVec2 offset = ImVec2(size * 2.0f, 0.0f);
	auto borderwidth = ed::GetStyle().PinBorderWidth;

	switch (pintype)
	{
	case EPinType::None:
		break;
	case EPinType::DataPin:
	{

		drawlist->AddCircle(pos + TotalSize, size / 2.0f, ImColor(color), 0, borderwidth);
		drawlist->AddCircleFilled(pos + TotalSize, size / 2.0f, ImColor(innercolor));
		bounds = ImRect(pos, pos + TotalSize * 2.0f);
	}
	break;
	case EPinType::ExecutionPin:
	{
		auto pinpos = pos;
		float halfsize = size / 2.0f;
		ImVec2 points[] = {
			pinpos + TotalSize + ImVec2(-halfsize, halfsize),
			pinpos + TotalSize + ImVec2(0.0f, halfsize),
			pinpos + TotalSize + ImVec2(halfsize, 0.0f),
			pinpos + TotalSize + ImVec2(0.0f, -halfsize),
			pinpos + TotalSize + ImVec2(-halfsize, -halfsize)
		};

		drawlist->AddPolyline(points, 5, ImColor(color), true, borderwidth);
		drawlist->AddConvexPolyFilled(points, 5, ImColor(innercolor));

		bounds = ImRect(pinpos, pinpos + TotalSize * 2.0f);
	}
	break;
	default:
		break;
	}

	ImGui::ItemSize(bounds);
	if (!ImGui::ItemAdd(bounds, id))
		return;

}

void NodeBuilder::DrawPinTriangle(ImGuiID id, float size, const ImVec4& color , const ImVec4& innercolor , const ImVec2& offset )
{
	ImGuiContext& g = *ImGui::GetCurrentContext();
	ImDrawList* drawlist = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetCursorScreenPos();
	ImRect bounds;

	auto TotalSize = ImVec2(size, size);


	ImVec2 points[] =
	{
		pos + offset + ImVec2(0, 0),
		pos + offset + ImVec2(size , size / 2.0f),
		pos + offset + ImVec2(0.0f, size)
	};

	auto borderwidth = ed::GetStyle().PinBorderWidth;
	drawlist->AddTriangleFilled(points[0], points[1], points[2], ImColor(innercolor));
	drawlist->AddTriangle(points[0], points[1], points[2], ImColor(color), borderwidth);
	bounds = ImRect(pos + offset, pos + offset + TotalSize);

	//drawlist->AddRectFilled(bounds.Min, bounds.Max, ImColor(color)); //[DEBUG]

	ImGui::ItemSize(bounds);
	if (!ImGui::ItemAdd(bounds, id))
		return;

}

void NodeBuilder::DrawInputs()
{
	auto style = ed::GetStyle();

	ImGui::BeginVertical("inputs");

	for (int i = 0; i < m_CurrentNode->m_NumInputs; i++)
	{
		auto input = m_CurrentNode->m_Inputs[i];
		auto id = input->GetID();

		IProperty* prop = input->GetProperty();

		auto color = prop ? prop->GetColor() : ImGuiExtras::White;
		auto innercolor = input->m_Connections > 0 ? prop ? prop->GetColor() : ImGuiExtras::White : ImGuiExtras::Black;

		auto txt = input->GetName();

		auto posy = ImGui::GetCursorPosY();
		ImGui::SetCursorPosY(posy + m_PinPadding);

		ImGui::BeginHorizontal(id);

		ed::BeginPin(id, input->pinKind);
		DrawPin(id, input->GetPinType(), style.PinRadius, color, innercolor);
		ed::EndPin();

		if (input->GetPinType() == EPinType::DataPin)
		{
			ImGui::Spring(0, 0);
			DrawPinTriangle(id, style.PinRadius, color, innercolor, { -style.PinRadius, 0 });


		}

		if (!txt.empty()) { ImGui::Spring(); ImGui::TextUnformatted(txt.c_str()); ImGui::Spring(); }

		if (prop && input->m_Connections == 0)
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGuiExtras::Grey);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImGuiExtras::Grey);
			ImGui::Spring();
			ImGui::SetNextItemWidth(50.0f);
			prop->DrawDetails();
			ImGui::PopStyleColor(2);
		}

		ImGui::EndHorizontal();
	}

	ImGui::EndVertical();
}

void NodeBuilder::DrawOutputs()
{
	auto style = ed::GetStyle();

	ImGui::BeginVertical("outputs");

	for (int i = 0; i < m_CurrentNode->m_NumOutputs; i++)
	{
		auto input = m_CurrentNode->m_Outputs[i];
		auto id = input->GetID();



		IProperty* prop = input->GetProperty();
		auto color = prop ? prop->GetColor() : ImGuiExtras::White;

		auto innercolor = input->m_Connections > 0 ? prop ? prop->GetColor() : ImGuiExtras::White : ImGuiExtras::Black;

		auto txt = input->GetName();

		auto posy = ImGui::GetCursorPosY();
		ImGui::SetCursorPosY(posy + m_PinPadding);

		ImGui::BeginHorizontal(id);

		ImGui::Spring();

		if (!txt.empty()) { ImGui::TextUnformatted(txt.c_str()); ImGui::Spring(0.0f); }


		ed::BeginPin(id, input->pinKind);

		DrawPin(id, input->GetPinType(), style.PinRadius, color, innercolor);

		ed::EndPin();

		if (input->GetPinType() == EPinType::DataPin)
		{
			ImGui::Spring(0, 0);

			DrawPinTriangle(id, style.PinRadius, color, innercolor, { -style.PinRadius, 0 });

		}


		ImGui::EndHorizontal();

	}

	ImGui::EndVertical();
}

void NodeBuilder::DrawCommentResizeButton(class Comment* commentNode)
{
	auto id = commentNode->GetID();


	//Add Resize Button
	ImDrawList* drawlist = ed::GetNodeBackgroundDrawList(id);
	auto pos = ed::GetNodePosition(id);
	auto size = ed::GetNodeSize(id);

	ImVec2 buttonsize = { 30, 30 };
	ImRect rect = { pos + size - buttonsize, pos + size };
	drawlist->AddRectFilled(rect.Min, rect.Max, ImGui::GetColorU32({ .1f, .1f , .1f , .1f }));

	ImGui::ItemSize(rect);
	ImGui::ItemAdd(rect, id);

	bool hovered = ImGui::ItemHoverable(rect, id);
	hovered = ImGui::IsMouseHoveringRect(rect.Min, rect.Max, false);

	if (hovered)
	{
		auto window = ImGui::GetCurrentWindow();
		ImGui::SetHoveredID(id);
		ImGui::SetActiveID(id, window);
		ImGui::SetFocusID(id, window);

		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);

		if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			auto deltaPos = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left, 0.01f);
			commentNode->m_Size += deltaPos;
			ImGui::ResetMouseDragDelta(ImGuiMouseButton_Left);
		}
	}
}

float NodeBuilder::m_PinPadding = 5.0f;

Ref<class Texture> NodeBuilder::m_HeaderTexture;

LinkBuilder::LinkBuilder(struct Link* link)
{
	m_CurrentLink = link;
}

void LinkBuilder::Draw()
{
	auto id = m_CurrentLink->GetID();
	auto start = m_CurrentLink->m_StartPin;
	auto end = m_CurrentLink->m_EndPin;

	ed::Link(id, start, end, ImGuiExtras::White, m_LinkThickness);
}

float LinkBuilder::m_LinkThickness = 3.0f;
