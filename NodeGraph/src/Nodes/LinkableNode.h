#pragma once

#include "BaseNode.h"

class LinkableNode : public BaseNode
{
public:

	LinkableNode();
	LinkableNode(const LinkableNode& other);

	Children GetChildren() override { return m_Children;  }

	void AddChild(BaseNode* child) override;

	void RemoveChild(BaseNode* child) override;

	inline LinkData GetLinkData() const override { return m_LinkData; }

	virtual void Serialize(YAML::Emitter& out) override;

	virtual void DeSerialize(YAML::detail::iterator_value& value) override;

private:

	//called when child node is destroyed
	virtual void OnChildNodeDestroyed(NodeEditorObject* node);


protected:

	virtual void OnAddChild(BaseNode* child) {}

	virtual void OnRemoveChild(BaseNode* child) {}

private:

	Children m_Children;

	LinkData m_LinkData;

	RTTR_ENABLE(BaseNode)

};