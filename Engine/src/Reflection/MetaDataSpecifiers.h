#pragma once

enum class ClassMetaData
{
	Category,
	Description,
	ToolTip
};

enum class EPropertyMetaData
{
	ClampMin,
	ClmapMax,
	ToolTip,
	DisplayName,
	PinType
};

enum class FunctionMetaData
{
	DisplayName,
	Hidden,
	ToolTip
};

enum class EnumMetaData
{
	DisplayName,
	Hidden,
	ToolTip
};

enum class EPinType
{
	None = 0,
	Input = 1 << 0,
	Output = 1 << 1,
	InputOutput = Input | Output,
	FlowInput = 1 << 2,
	FlowOutput = 1 << 3,
	FlowInputOutput = FlowInput | FlowOutput
};

inline int operator&(const EPinType& lhs, const EPinType& rhs)
{
	return (static_cast<int>(lhs) & static_cast<int>(rhs));
}

inline EPinType operator |(const EPinType& lhs, const EPinType& rhs) 
{
	auto result = static_cast<int>(lhs) | static_cast<int>(rhs);
	return static_cast<EPinType>(result);
};

inline EPinType operator |=(EPinType& lhs, const EPinType& rhs)
{
	return lhs = (lhs | rhs);
};