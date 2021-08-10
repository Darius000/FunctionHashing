#include "PCH.h"
#include "Pin.h"
#include "DataTypes/Property.h"
#include "Node.h"


Pin::Pin(ImNodesAttributeType_ type, Node* parent)
	:m_Parent(parent)
{
	m_Type = type;
}

EPinType Pin::GetPinType()
{
	return EPinType::None;
}

bool Pin::CanConnect(Pin* other)
{
	return other && GetPinType() == other->GetPinType();
}

void Pin::OnConnected(Pin* other)
{
	m_IsConnected = true;
}

void Pin::OnDisConnected()
{
	m_IsConnected = false;
}

bool Pin::IsConnected() const
{
	return m_IsConnected;
}

ExecutionPin::ExecutionPin(ImNodesAttributeType_ type, Node* parent) 
	:Pin(type, parent), m_Next(nullptr)
{
	m_Type = type;
}

bool ExecutionPin::CanConnect(Pin* other)
{
	return Pin::CanConnect(other);
}

void ExecutionPin::OnConnected(Pin* other)
{
	Pin::OnConnected(other);

	if (m_Type == ImNodesAttributeType_Output)
	{
		m_Next = other->m_Parent;
	}
	else
	{
		if (auto execpin = Cast<ExecutionPin>(other))
		{
			execpin->m_Next = m_Parent;
		}
	}
	
}

void ExecutionPin::OnDisConnected()
{
	Pin::OnDisConnected();

	m_Next = nullptr;
}

EPinType ExecutionPin::GetPinType()
{
	return EPinType::ExecutionPin;
}
