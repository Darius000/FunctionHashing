#pragma once

#include "Core/Core.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "yaml-cpp/yaml.h"
#include "Core/UUID/UUID.h"
#include <rttr/type>
#include <rttr/registration.h>
#include <rttr/registration_friend.h>

using namespace rttr;


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

	EngineEvent<class NodeEditorObject*> OnDestroyed;
	
	inline const std::string& GetToolTip() const { return m_ToolTip; }

	inline const std::string& GetName() const { return m_Name; }

	const bool HasToolTip() const { return m_ToolTip.size() > 0; }

	inline const bool IsPendingDestroy() const { return m_PendingDestroy; }

	Core::UUID GetID() const;

	bool operator==(const NodeEditorObject& obj) const; 

	NodeEditorObject& operator=(const NodeEditorObject& obj);

	virtual const EObjectType GetObjectType() { return EObjectType::None; };

	virtual void Serialize(YAML::Emitter& out);

	virtual void DeSerialize(YAML::detail::iterator_value& value);


private:

protected:
	Core::UUID m_ID;

protected:
	std::string m_Name = "";
	std::string m_ToolTip = "";

private:
	bool m_PendingDestroy = false;

	friend class GraphSerializer;

	RTTR_REGISTRATION_FRIEND
	RTTR_ENABLE()
};

