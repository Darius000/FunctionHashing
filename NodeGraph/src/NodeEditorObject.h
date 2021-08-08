#pragma once

#include "Core/Core.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_stdlib.h"

class NodeEditorObject
{
public:
	NodeEditorObject();
	NodeEditorObject(const NodeEditorObject& obj);

	virtual ~NodeEditorObject();

	void Draw();
	void Destroy();
	void SetName(const std::string& str);

	virtual void OnDraw();

	inline std::string& GetName() { return m_Name; }
	inline const bool IsPendingDestroy() const { return m_PendingDestroy; }
	ImGuiID GetID() const;

	const bool operator==(const NodeEditorObject& obj);
	NodeEditorObject& operator=(const NodeEditorObject& obj);

private:
	static ImGuiID GetNextAvialableID();

protected:
	ImGuiID m_ID;

protected:
	std::string m_Name;

private:
	bool m_PendingDestroy;
	static ImGuiID s_ID;
	static std::vector<ImGuiID> s_DeletedIDs;
};

