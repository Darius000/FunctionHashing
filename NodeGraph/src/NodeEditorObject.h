#pragma once

#include "Core/Core.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_stdlib.h"

DECLARE_ONE_PARAMETER_EVENT(OnDestroyed, class NodeEditorObject*, obj)

enum class EObjectType
{	
	None,
	Node,
	Property
};

class NodeEditorObject
{
public:
	NodeEditorObject();
	NodeEditorObject(const NodeEditorObject& obj);

	virtual ~NodeEditorObject();

	void Destroy();
	void SetName(const std::string& str);
	void SetToolTip(const std::string& tooltip);

	FOnDestroyedEvent OnDestroyed;
	
	inline std::string& GetToolTip() { return m_ToolTip; }
	inline std::string& GetName() { return m_Name; }
	const bool HasToolTip() const { return m_ToolTip.size() > 0; }
	inline const bool IsPendingDestroy() const { return m_PendingDestroy; }
	ImGuiID GetID() const;

	const bool operator==(const NodeEditorObject& obj);
	NodeEditorObject& operator=(const NodeEditorObject& obj);
	virtual const EObjectType GetObjectType() { return EObjectType::None; };

private:
	static ImGuiID GetNextAvialableID();

protected:
	ImGuiID m_ID;

protected:
	std::string m_Name;
	std::string m_ToolTip = "";

private:
	bool m_PendingDestroy;
	static ImGuiID s_ID;
	static std::vector<ImGuiID> s_DeletedIDs;
};

