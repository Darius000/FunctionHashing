#pragma once

#include "Core/Core.h"
#include "DataTypes/Property.h"
#include "NodeRegistry.h"
#include "NodeEditorObject.h"
#include "Pin.h"

template<class T>
using Array = std::vector<Scope<T>>;



enum class ETitleStyle_ : int
{
	Default = 0,
	Custom
};

using Pins = std::vector<Ref<Pin>>;
using ParameterMap = std::vector<Ref<DataPin>>;
using ExecutionPins = std::vector<Ref<ExecutionPin>>;

class Node : public NodeEditorObject
{

public:
	Node();
	virtual ~Node() = default;

	virtual std::string GetTypeName() const { return "Node"; }

	virtual void OnDraw() override;

	//Execute a function
	void Execute();

protected:
	void BeginDraw();
	void EndDraw();
	void DrawDataPins();

	virtual void CustomDraw();
	virtual void OnExecute() {};

public:
	DataPin* GetParameter(const std::string& name);

	DataPin* GetParameter(int index);

	ParameterMap& GetParameters() { return m_DataPins; }

	Pin* GetPinWithID(ImGuiID id);

	std::vector<ExecutionPin*> GetExecutionPinsByType(ImNodesAttributeType_ type) const;

protected:
	ETitleStyle_ m_TitleStyle;

	ImVec2 m_DefaultSize;
	ImVec4 m_Color;
	ImVec4 m_TitleColor;
	float m_Rounding;

protected:
	template<typename T>
	void AddDataPin(const std::string& name, ImNodesAttributeType_ type, Ref<IProperty> prop)
	{
		auto dp = MakeRef<DataPinT<T>>(name, type, prop, this);
		m_DataPins.push_back(dp);
		m_Pins.push_back(dp);
	}

	void AddExecutionPin(ImNodesAttributeType_ type);

protected:
	ParameterMap m_DataPins;
	ExecutionPins m_ExecPins;
	Pins m_Pins;

	bool m_IsSelected = false;
};


