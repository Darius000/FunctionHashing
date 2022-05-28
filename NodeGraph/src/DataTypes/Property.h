#pragma once

#include "Core/Core.h"
#include "NodeEditorObject.h"
#include "DataTypeRegistry.h"

DECLARE_ONE_PARAMETER_EVENT(OnNameChanged, const std::string&, name)

class DataTypeRegistry;

struct IProperty : public NodeEditorObject
{

	IProperty() {};

	virtual ~IProperty() = default;

	FOnNameChangedEvent OnNameChanged;

	virtual ImVec4 GetColor() { return ImVec4(.3f, .3f, .3f, 1.0f); }

	const EObjectType GetObjectType() { return EObjectType::Property; }

	virtual void DrawDetails() {};

	template<typename T>
	T GetValue()
	{
		auto prop = Cast<IPropertyT<T>>(this);
		return prop->Get();
	}

	virtual void SetPtr(IProperty* other) {};

	virtual void Reset(){};

	virtual std::string GetTypeName() const { return ""; }
};

template<typename T>
struct IPropertyT : public IProperty
{
	using Type = T;

	IPropertyT() 
		:m_Prop(), m_DefaultProp(m_Prop)
	{

	}

	IPropertyT(T value)
		:m_Prop(value)
	{

	}

	explicit IPropertyT(const IPropertyT& other)
	{
		m_Prop = other.m_Prop;
	}

	IPropertyT(IPropertyT&& other) noexcept
	{
		m_Prop = other.m_Prop;
	}

	virtual ~IPropertyT()
	{

	}

	virtual void SetPtr(IProperty* other)
	{
		m_Prop = Cast<IPropertyT>(other)->m_Prop;
	}

	virtual void Reset() override { m_Prop = m_DefaultProp; }

	virtual void DrawDetails() override;

	virtual ImVec4 GetColor() override;

	static const std::string GetStaticTypeName();

	virtual std::string GetTypeName() const override { return GetStaticTypeName(); }

	virtual void Serialize(YAML::Emitter& out) override;

	virtual void DeSerialize(YAML::detail::iterator_value& value) override;

	inline static IProperty* Create()
	{
		return new IPropertyT();
	}

	//operators
	IPropertyT& operator=(const IPropertyT& p) { m_Prop = p.m_Prop; return *this; }

	const bool operator==(const Type& t) const { return m_Prop == t; }
	const bool operator!=(const Type& t) const { return m_Prop != t; }
	const bool operator<=(const Type& t) const { return m_Prop <= t; }
	const bool operator<(const Type& t) const { return m_Prop < t; }
	const bool operator>(const Type& t) const { return m_Prop > t; }
	const bool operator>=(const Type& t) const { return m_Prop >= t; }


	Type& Set(const Type& t) { return m_Prop = t; }
	Type& Get() { return m_Prop; }
	Type& GetRef() const { return m_Prop; }
	const Type& GetConstRef() const { return m_Prop; }

	Type m_Prop;
	Type m_DefaultProp;
};

template<typename T>
void IPropertyT<T>::DeSerialize(YAML::detail::iterator_value& value)
{
	NodeEditorObject::DeSerialize(value);

	m_DefaultProp = value["Default Value"].as<T>();
	m_Prop = value["Value"].as<T>();
}

template<typename T>
void IPropertyT<T>::Serialize(YAML::Emitter& out)
{
	NodeEditorObject::Serialize(out);

	out << YAML::Key << "Property Type";
	out << YAML::Value << GetTypeName();

	out << YAML::Key << "Default Value";
	out << YAML::Value << m_DefaultProp;

	out << YAML::Key << "Value";
	out << YAML::Value << m_Prop;
}

#define REGISTER_TYPE(x)\
namespace Type##x\
{\
	bool registered = DataTypeRegistry::Registrate(IPropertyT<x>::GetStaticTypeName(), IPropertyT<x>::Create);\
};
