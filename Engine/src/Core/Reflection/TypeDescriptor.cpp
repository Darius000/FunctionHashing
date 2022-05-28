#pragma once

#include "PCH.h"
#include "TypeDescriptor.h"

struct FloatTypeDescriptor : public TypeDescriptor
{
	FloatTypeDescriptor() : TypeDescriptor("float", sizeof(float)) {}

	virtual void dump(const void* obj) const override {
		std::cout << "float {" << *(const float*)(obj) << "}\n";
	}
};

template <>
TypeDescriptor* getPrimitiveDescriptor<float>() {
	static FloatTypeDescriptor typeDesc;
	return &typeDesc;
};

struct BoolTypeDescriptor : public TypeDescriptor
{
	BoolTypeDescriptor() : TypeDescriptor("bool", sizeof(float)) {}

	virtual void dump(const void* obj) const override {
		std::cout << "bool {" << *(const bool*)(obj) << "}\n";
	}
};

template <>
TypeDescriptor* getPrimitiveDescriptor<bool>() {
	static BoolTypeDescriptor typeDesc;
	return &typeDesc;
};

struct IntTypeDescriptor : public TypeDescriptor
{
	IntTypeDescriptor() : TypeDescriptor("int", sizeof(float)) {}

	virtual void dump(const void* obj) const override{
		std::cout << "int {" << *(const int*)(obj) << "}\n";
	}
};

template <>
TypeDescriptor* getPrimitiveDescriptor<int>() {
	static IntTypeDescriptor typeDesc;
	return &typeDesc;
};