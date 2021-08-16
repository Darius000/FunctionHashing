#pragma once

#include "Core/Core.h"
#include "NodeEditorObject.h"
#include "DataTypes/Property.h"
#include "NodeEditor/imgui_node_editor.h"

namespace ed = ax::NodeEditor;

enum class EPinType
{
	None  = 0,
	DataPin,
	ExecutionPin
};

struct Pin : public NodeEditorObject
{
	Pin();
	virtual ~Pin() = default;

	virtual const EPinType GetPinType() const { return EPinType::None; }

	virtual bool IsValidConnection(const Pin& pin) const;

	virtual IProperty* GetProperty() { return nullptr; };

	virtual IProperty* GetProperty() const { return nullptr; };

	ed::PinKind pinKind;

	int m_Connections;
};

struct ExecutionPin : public Pin 
{
	virtual const EPinType GetPinType() const override{ return EPinType::ExecutionPin; }
};

struct DataPin : public Pin 
{
	virtual const EPinType GetPinType() const override { return EPinType::DataPin; }

	bool IsValidConnection(const Pin& pin) const override;

	virtual IProperty* GetProperty() override { return m_Property.get(); };

	virtual IProperty* GetProperty() const override { return m_Property.get(); };

	Ref<struct IProperty> m_Property ;
};
