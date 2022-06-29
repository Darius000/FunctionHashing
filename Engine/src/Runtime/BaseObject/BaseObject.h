#pragma once

#include "Core/Core.h"
#include "Core/UUID.h"
#include "Reflection/Reflection.h"

class BaseObject 
{
public:
	BaseObject();
	BaseObject(const BaseObject& obj);

	virtual ~BaseObject();

	void Destroy();

	void SetName(const std::string& str);

	EngineEvent<class BaseObject*> OnDestroyed;
	
	inline const std::string& GetName() const { return m_Name; }

	inline const bool IsPendingDestroy() const { return m_PendingDestroy; }

	inline Core::UUID GetID() const { return m_ID; };

	bool operator==(const BaseObject& obj) const; 

	BaseObject& operator=(const BaseObject& obj);

private:
	Core::UUID m_ID;

protected:
	std::string m_Name = "";

private:
	bool m_PendingDestroy = false;

	REFLECTABLEV()
};

