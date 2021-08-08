#pragma once

#include "Core/Core.h"
#include "NodeEditorObject.h"
#include "ImNodes/imnodes.h"
#include "ImNodes/imnodes_internal.h"
#include "DataTypes/Property.h"

enum class EPinType
{
	None  = 0,
	DataPin,
	ExecutionPin
};

struct Pin : public NodeEditorObject
{
	Pin(ImNodesAttributeType_ type, class Node* parent);

	virtual EPinType GetPinType();

	virtual bool CanConnect(Pin* other);
	virtual void OnConnected(Pin* other);
	virtual void OnDisConnected();

	bool IsConnected() const;

	ImNodesAttributeType_ m_Type = ImNodesAttributeType_None;

	class Node* m_Parent;
	
protected:
	bool m_IsConnected = false;
};

struct DataPin : public Pin
{
protected:
	DataPin(const std::string& name, ImNodesAttributeType_ type, Node* parent) 
		:Pin(type, parent)
	{
		m_Type = type;
		m_Name = name;
	}

public:
	EPinType GetPinType() override
	{
		return EPinType::DataPin;
	}

	bool CanConnect(Pin* other) override
	{
		return Pin::CanConnect(other);
	}

	void OnConnected(Pin* other) override
	{
		Pin::OnConnected(other);
	}

	void OnDisConnected() override
	{
		Pin::OnDisConnected();
	}

	virtual IProperty* GetProperty() = 0;

	std::string m_Name = "";
};

template<typename T>
struct DataPinT : public DataPin
{
	DataPinT(const std::string& name, ImNodesAttributeType_ type, Ref<IProperty> prop, Node* parent)
		:DataPin(name, type, parent), m_Property(prop) {}

	bool CanConnect(Pin* other) override
	{
		bool same_type = false;

		if (auto casted = Cast<DataPinT>(other))
		{
			same_type = true;
		}

		return DataPin::CanConnect(other) && same_type;
	}

	void OnConnected(Pin* other) override
	{
		DataPin::OnConnected(other);

		if (DataPinT* datapin = Cast<DataPinT>(other))
		{
			if (m_Type == ImNodesAttributeType_Input)
			{
				auto a = Cast<IPropertyT<T>>(m_Property.get());
				auto b = Cast<IPropertyT<T>>(datapin->m_Property.get());

				if (a && b)
				{
					a->m_Prop = b->m_Prop;
				}
				

			}
		}
	}

	IProperty* GetProperty() override
	{
		return m_Property.get();
	}

	void OnDisConnected() override
	{
		DataPin::OnDisConnected();

		if (m_Type == ImNodesAttributeType_Input)
		{
			m_Property->Reset();
		}
	}

	Ref<IProperty> m_Property;
};

struct ExecutionPin : public Pin
{
	ExecutionPin(ImNodesAttributeType_ type, class Node* parent);

	virtual bool CanConnect(Pin* other);
	virtual void OnConnected(Pin* other) override;
	virtual void OnDisConnected() override;

	virtual EPinType GetPinType();

	class Node* m_Next;
};