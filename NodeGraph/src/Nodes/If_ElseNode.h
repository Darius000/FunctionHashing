#pragma once

#include "Core/Core.h"
#include "Node.h"

namespace TOO
{
	ENUM()
	enum class E_Alignment
	{
		AlignLeft = 0x0001,
		AlignRight = 0x0002,
		AlignHCenter = 0x0004,
		AlignJustify = 0x0008
	};
}

CLASS(Category = "Branching | ", Description = "Condition determines next node path")
class If_ElseNode :public Node
{
public:
	If_ElseNode();

	FUNCTION()
		void OnExecute() override;

	ImVec4 GetHeaderColor() const override { return { 1.0f, 0.0f, 0.0f, 1.0f }; }

	PROPERTY()
		bool m_InCondition;

	RTTR_ENABLE(Node)
};

#include "If_ElseNode.generated.h"