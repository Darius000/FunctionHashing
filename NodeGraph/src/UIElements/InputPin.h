#pragma once

#include "PinElement.h"

class InputPin : public PinElement
{
public:

	InputPin(std::string_view name, const rttr::property& property, const rttr::instance& obj, bool canMultiConnect);
};

class OutputPin : public PinElement
{
public:
	OutputPin(std::string_view name, const rttr::property& property, const rttr::instance& obj, bool canMultiConnect);
};