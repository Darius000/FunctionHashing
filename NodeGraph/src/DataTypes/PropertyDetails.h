#pragma once

#include "Core/Core.h"


struct PropertyDetails
{
	PropertyDetails() = default;
	virtual ~PropertyDetails() = default;

	virtual const ImVec4 GetColor() const = 0;
};

template<typename T>
struct PropertyDetailsT;

template<> 
struct PropertyDetailsT<float> : public PropertyDetails
{
	const ImVec4 GetColor() const { return ImGuiExtras::LightGreen; }
};

template<>
struct PropertyDetailsT<int> : public PropertyDetails
{
	const ImVec4 GetColor() const { return ImGuiExtras::DarkGreen; }
};

template<>
struct PropertyDetailsT<bool> : public PropertyDetails
{
	const ImVec4 GetColor() const { return ImGuiExtras::DarkRed; }
};