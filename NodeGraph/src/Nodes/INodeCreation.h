#pragma once

#include "Core/Core.h"


class NodeRegistry;

class INodeCreation
{
public:
	INodeCreation() = default;
	virtual ~INodeCreation() = default;

	virtual std::string GetTypeName() const = 0;
};

template<typename R, typename ... Args>
struct NodeCreationMethod
{
	using ReturnType = R;
	using ReturnTypeNoPtr = std::remove_pointer<ReturnType>;
	using TCreateMethod = ReturnType(*)(Args...);

	NodeCreationMethod(TCreateMethod method, const std::string& catagory, bool displayincatgeories,
		const std::string& description)
		:m_CreateFunc(method), m_Category(catagory), m_PlaceInCategories(displayincatgeories),
		m_Description(description)
	{

	}

	NodeCreationMethod(const NodeCreationMethod& rhs)
	{
		m_CreateFunc = rhs.m_CreateFunc;
		m_Category = rhs.m_Category;
		m_PlaceInCategories = rhs.m_PlaceInCategories;
		m_Description = rhs.m_Description;
	}

	NodeCreationMethod& operator=(const NodeCreationMethod& rhs)
	{
		m_CreateFunc = rhs.m_CreateFunc;
		m_Category = rhs.m_Category;
		m_PlaceInCategories = rhs.m_PlaceInCategories;
		m_Description = rhs.m_Description;
		return *this;
	}
	
	TCreateMethod m_CreateFunc;
	std::string m_Category;
	bool m_PlaceInCategories;
	std::string m_Description;
};


#define DEFINE_REGISTER_NODE(Class)\
	namespace Register##Class\
	{\
		bool registered = NodeRegistry::Registrate(Class::GetFactoryName(), \
				NodeCreationMethod(Class::CreateMethod, Class::GetFactoryCategory(),\
				Class::GetVisibleInCategories(),\
				Class::GetFactoryDescription()));\
	}

#define DEFINE_NODE_CLASS(Class, Category, Description, DisplayCategory )\
	virtual std::string GetTypeName() const override { return #Class;}\
	static std::string GetFactoryName() { return #Class; };\
	static bool GetVisibleInCategories()  { return DisplayCategory; }\
	static std::string GetFactoryCategory() { return std::string(Category) + Class::GetFactoryName();}\
	static std::string GetFactoryDescription() { return Description; }
