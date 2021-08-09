#pragma once

#include "Core/Core.h"

template<typename... Args>
class NodeRegistry;

class INodeCreation
{
public:
	INodeCreation() = default;
	virtual ~INodeCreation() = default;
};

template<typename... Args>
struct NodeCreationMethod
{
	using TCreateMethod = class Node* (*)(Args...);

	NodeCreationMethod() {}
	NodeCreationMethod(TCreateMethod method, const std::string& catagory, const std::string& description)
		:m_CreateFunc(method), m_Category(catagory), m_Description(description)
	{

	}

	NodeCreationMethod(const NodeCreationMethod& rhs)
	{
		m_CreateFunc = rhs.m_CreateFunc;
		m_Category = rhs.m_Category;
		m_Description = rhs.m_Description;
	}

	NodeCreationMethod& operator=(const NodeCreationMethod& rhs)
	{
		m_CreateFunc = rhs.m_CreateFunc;
		m_Category = rhs.m_Category;
		m_Description = rhs.m_Description;
		return *this;
	}
	
	TCreateMethod m_CreateFunc;
	std::string m_Category;
	std::string m_Description;
};

#define REGISTER_NODE(Class,  Category, Description, ...)\
	namespace Type##Class\
	{\
		bool registered = NodeRegistry<__VA_ARGS__>::Registrate(Class::GetFactoryName(), \
		NodeCreationMethod(Class::CreateMethod, Category, Description));\
	}

#define DEFINE_REGISTER_NODE(Class, ...)\
	namespace Register##Class\
	{\
		bool registered = NodeRegistry<__VA_ARGS__>::Registrate(Class::GetFactoryName(), \
				NodeCreationMethod(Class::CreateMethod, Class::GetFactoryCategory(),\
				Class::GetFactoryDescription()));\
	}
	

#define DEFINE_NODE_CLASS(Class, Category, Description)\
	virtual std::string GetTypeName() const override { return #Class;}\
	static Node* CreateMethod() { return new Class(); }\
	static std::string GetFactoryName() { return #Class; };\
	static std::string GetFactoryCategory() { return std::string(Category) + Class::GetFactoryName();}\
	static std::string GetFactoryDescription() { return Description; }
