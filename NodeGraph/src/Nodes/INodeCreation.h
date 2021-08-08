#pragma once

#include "Core/Core.h"

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
