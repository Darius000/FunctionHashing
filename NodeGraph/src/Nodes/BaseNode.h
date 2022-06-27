#pragma once

#include "BaseObject.h"
#include "LinkInfo.h"
#include "Core/Types/Color.h"

enum class ENodeType
{
	Blueprint,
	Simple,
	Comment
};

class BaseNode : public BaseObject
{
public:
	using Children = std::vector<BaseNode*>;
	using LinkData = std::vector<LinkInfo>;

public:
	BaseNode();
	BaseNode(const BaseNode&) = default;

	virtual ~BaseNode();

	glm::vec2 m_Position = {0,0};

	glm::vec2 m_Size = {400, 50};

	virtual inline Children GetChildren() { return {}; };

	virtual inline LinkData GetLinkData() const { return {}; }

	virtual void AddChild(BaseNode* child) {};

	virtual void RemoveChild(BaseNode* child) {};

	void Execute();

	virtual const ENodeType GetNodeType() { return ENodeType::Blueprint; }

	virtual Color GetHeaderColor() const { return { .4f, .4f, .4f, 1.0f }; }

	virtual Color GetColor() const { return {.2f, .2f, .2f, 1.0f}; }


protected:
	//initilize before exectuion starts
	virtual void OnBeginExecute() {};

	virtual void OnExecute() {};

	virtual void OnEndExecute() {};

private:

	bool m_BeginExecution = false;

	REFLECTABLEV(BaseObject)
};