#include "PCH.h"
#include "BaseObject.h"

BaseObject::BaseObject()
{	

}

BaseObject::BaseObject(const BaseObject& obj)
{
	m_Name = obj.m_Name;
	m_PendingDestroy = false;
}

BaseObject::~BaseObject()
{
	
}


void BaseObject::Destroy()
{
	m_PendingDestroy = true;
	OnDestroyed.Invoke(this);
}

void BaseObject::SetName(const std::string& str)
{
	m_Name = str;
}

BaseObject& BaseObject::operator=(const BaseObject& obj)
{
	m_Name = obj.m_Name;
	return *this;
}

bool BaseObject::operator==(const BaseObject& obj) const
{
	return m_Name == obj.m_Name && m_ID == obj.m_ID;
}
