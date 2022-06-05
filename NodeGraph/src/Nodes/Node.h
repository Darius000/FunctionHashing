#pragma once

#include "Core/Core.h"
#include "DataTypes/Property.h"
#include "LinkableNode.h"
#include "NodeEditorObject.h"

class Node : public LinkableNode
{

public:
	Node();
	virtual ~Node() = default;


	template<typename T>
	T GetPinValue(const std::string name)
	{
		Pins::iterator it = std::find_if(m_Inputs.begin(), m_Inputs.end(), [](Ref<Pin>& pin) {
			return pin->GetName() == name;
			});

		if (it != m_Inputs.end())
		{
			return (*it)->GetProperty()->GetValue<T>();
		}

		return -1;
	}

	virtual void* GetValue(const std::string& pinName)
	{
		return nullptr;
	}

	virtual void OnExecute() {};



	Pins m_Inputs;
	Pins m_Outputs;
	int m_NumInputs;
	int m_NumOutputs;
protected:
	
private:

	RTTR_ENABLE(LinkableNode)
};


