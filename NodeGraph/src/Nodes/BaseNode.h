#pragma once

#include "PCH.h"
#include "NodeEditorObject.h"
#include "INodeCreation.h"
#include "LinkInfo.h"
#include "Pin.h"

enum class ENodeType
{
	Blueprint,
	Simple,
	Comment
};

class BaseNode : public NodeEditorObject, public INodeCreation
{
public:
	using Children = std::vector<BaseNode*>;
	using LinkData = std::vector<LinkInfo>;
	using Pins = std::vector<Scope<struct Pin>>;

public:
	BaseNode();
	BaseNode(const BaseNode&) = default;

	virtual ~BaseNode();

	Vec2 m_Position;

	const Pins& GetPins() const { return m_Pins; }

	virtual inline Children GetChildren() { return {}; };

	virtual inline LinkData GetLinkData() const { return {}; }

	virtual void AddChild(BaseNode* child) {};

	virtual void RemoveChild(BaseNode* child) {};

	void Execute();

	virtual std::string GetTypeName() const { return "Node"; }

	virtual std::string GetFactoryName() const { return ""; }

	const EObjectType GetObjectType() { return EObjectType::Node; }

	virtual const ENodeType GetNodeType() { return ENodeType::Blueprint; }

	virtual void Serialize(YAML::Emitter& out);

	virtual void DeSerialize(YAML::detail::iterator_value& value);

protected:
	//initilize before exectuion starts
	virtual void OnBeginExecute() {};

	virtual void OnExecute() {};

	virtual void OnEndExecute() {};

private:

	Pins m_Pins;

	bool m_BeginExecution = false;
};