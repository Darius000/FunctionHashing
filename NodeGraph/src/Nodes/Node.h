#pragma once

#include "Core/Core.h"
#include "DataTypes/Property.h"
#include "INodeCreation.h"
#include "NodeEditorObject.h"
#include "Registry/NodeRegistry.h"
#include "Pin.h"

enum class ENodeType
{
	Blueprint,
	Simple,
	Comment
};

using Pins = std::vector<Ref<struct Pin>>;

class Node : public NodeEditorObject, public INodeCreation
{

public:
	Node();
	virtual ~Node() = default;

	virtual std::string GetTypeName() const { return "Node"; }
	virtual std::string GetFactoryName() const { return ""; }

	//Execute a function
	void Execute();

	virtual void OnExecute() {};

	const EObjectType GetObjectType() { return EObjectType::Node; }

	virtual const ENodeType GetNodeType() { return ENodeType::Blueprint; }

	Pin* FindPin(ImGuiID id) const;

	virtual void Serialize(YAML::Emitter& out);

	virtual void DeSerialize(YAML::detail::iterator_value& value);

	Pins m_Pins;
	Pins m_Inputs;
	Pins m_Outputs;
	int m_NumInputs;
	int m_NumOutputs;
	ImVec4 m_Color;
	ImVec4 m_TitleColor;
	float m_Rounding;

protected:
	

	DataPin* AddDataPin(const std::string& name, ed::PinKind pinkind, Ref<IProperty> prop);

	void AddExecutionPin(const std::string& name, ed::PinKind pinkind);

};


