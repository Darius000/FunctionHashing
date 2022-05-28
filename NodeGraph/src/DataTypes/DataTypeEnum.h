#pragma once

#include <Engine.h>

enum class EDataType : uint8_t
{
	DT_None,
	DT_float,
	DT_bool,
	DT_int,
	Max
};

template<>
std::vector<std::string> EnumStrings<EDataType>::Data = {
		"DT_None", "DT_float", "DT_bool" , "DT_int"
};

