#pragma once

#include "Core/Core.h"
#include "NodeEditorObject.h"
#include "DataTypes/Property.h"
#include "NodeEditor/imgui_node_editor.h"
#include "DataTypes/Enum.h"

namespace ed = ax::NodeEditor;

enum class EPinType
{
	None  = 0,
	DataPin,
	ExecutionPin
};

enum class EPinRejectReason : uint8_t
{
	None,
	InValid,
	DifferentPinTypes,
	AlreadyHasConnection,
	DifferentDataTypes,
	Max
};

template<>
std::vector<std::string> EnumStrings<EPinRejectReason>::Data = {
		"None", "InValid", "Different Pin Types" , "Already Has Connection", "Different Data Types"
};

struct Pin : public NodeEditorObject
{
	Pin();
	virtual ~Pin() = default;

	virtual const EPinType GetPinType() const { return EPinType::None; }

	virtual bool IsValidConnection(const Pin& pin, TEnum<EPinRejectReason>& reason) const;

	virtual IProperty* GetProperty() { return nullptr; };

	virtual IProperty* GetProperty() const { return nullptr; };

	virtual void Serialize(YAML::Emitter& out);

	virtual void DeSerialize(YAML::detail::iterator_value& value);

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

	bool IsValidConnection(const Pin& pin, TEnum<EPinRejectReason>& reason) const override;

	virtual IProperty* GetProperty() override { return m_Property.get(); };

	virtual IProperty* GetProperty() const override { return m_Property.get(); };

	Ref<struct IProperty> m_Property ;

	virtual void Serialize(YAML::Emitter& out);

	virtual void DeSerialize(YAML::detail::iterator_value& value);
};
