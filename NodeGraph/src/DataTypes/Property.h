#pragma once

#include "Core/Core.h"
#include "NodeEditorObject.h"
#include "DataTypeRegistry.h"

DECLARE_ONE_PARAMETER_EVENT(OnNameChanged, const std::string&, name)

class DataTypeRegistry;

struct IProperty : public NodeEditorObject
{
protected:
	IProperty() {};

public:
	virtual ~IProperty() = default;

	using NodeRefs = std::vector<ImGuiID>;

	FOnNameChangedEvent OnNameChanged;


public:
	virtual ImVec4 GetColor() { return ImVec4(.3f, .3f, .3f, 1.0f); }

	const EObjectType GetObjectType() { return EObjectType::Property; }

	virtual void DrawDetails() {};

	virtual void SetPtr(IProperty* other) {};
	virtual void Reset(){};

	virtual std::string GetTypeName() { return ""; }

	void AddRef(ImGuiID node_id)
	{
		m_NodeIds.push_back(node_id);
	}

	NodeRefs GetRefs() const {
		return m_NodeIds;
	}

protected:
	//store node ids referencing this prop
	NodeRefs m_NodeIds;
};

template<typename T>
struct IPropertyT : public IProperty
{
	using Type = T;

	IPropertyT() 
		:m_Prop(new T()), m_DefaultProp(m_Prop)
	{

	}

	explicit IPropertyT(T* t)
		:m_Prop(t), m_DefaultProp(t)
	{

	}

	explicit IPropertyT(const IPropertyT& other)
	{
		m_Prop = other.m_Prop;
	}

	IPropertyT(IPropertyT&& other) noexcept
	{
		m_Prop = std::move(other.m_Prop);
	}

	virtual ~IPropertyT()
	{
		delete m_Prop;
		m_DefaultProp = nullptr;
	}

	virtual void SetPtr(IProperty* other)
	{
		m_Prop = Cast<IPropertyT>(other)->m_Prop;
	}

	virtual void Reset() override { m_Prop = m_DefaultProp; }


	virtual void DrawDetails() override;

	virtual ImVec4 GetColor() override;

	static std::string GetStaticTypeName();

	virtual std::string GetTypeName() { return GetStaticTypeName(); }

	inline static IProperty* Create()
	{
		return new IPropertyT();
	}

	//operators
	IPropertyT& operator=(const IPropertyT& p) { m_Prop = p.m_Prop; return *this; }
	IPropertyT& operator=(IPropertyT&& p) { m_Prop = std::move(p.m_Prop); return *this; }
	const bool operator==(const Type& t) const { return *m_Prop == t; }
	const bool operator!=(const Type& t) const { return *m_Prop != t; }
	const bool operator<=(const Type& t) const { return *m_Prop <= t; }
	const bool operator<(const Type& t) const { return *m_Prop < t; }
	const bool operator>(const Type& t) const { return *m_Prop > t; }
	const bool operator>=(const Type& t) const { return *m_Prop >= t; }

	Type& Set(const Type& t) { return *m_Prop = t; }
	Type* Get() { return m_Prop; }
	Type& GetRef() const { return *m_Prop; }
	const Type& GetConstRef() const { return *m_Prop; }

	Type* m_Prop;
	Type* m_DefaultProp;
};



#define REGISTER_TYPE(x)\
namespace Type##x\
{\
	bool registered = DataTypeRegistry::Registrate(IPropertyT<x>::GetStaticTypeName(), IPropertyT<x>::Create);\
};
