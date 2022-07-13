#pragma once


#include "Node.h"



template<typename Type>
class Literal : public Node
{
public:
	Literal() :m_Value(Type()) {
	
		m_Name = "Literal";
	}

	Literal(const Type& obj) : m_Value(obj) {
		m_Name = "Literal";
	}

	Type m_Value;

	REFLECTABLEV(Node)
};

