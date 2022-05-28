#pragma once

#include "PCH.h"
#include "Core/UUID/UUID.h"

struct LinkInfo
{
	Core::UUID m_StartPinId;

	Core::UUID m_EndPinId;
};


inline YAML::Emitter& operator << (YAML::Emitter& out, const LinkInfo& id)
{
	out << YAML::BeginSeq << (UINT64)id.m_StartPinId << (UINT64)id.m_EndPinId << YAML::EndSeq;
	return out;
}

template<>
struct YAML::convert<LinkInfo> 
{
	static YAML::Node encode(const LinkInfo& rhs)
	{
		Node node;
		node.push_back(rhs.m_StartPinId);
		node.push_back(rhs.m_EndPinId);
		return node;
	}

	static bool decode(const Node& node, LinkInfo& rhs)
	{
		if (!node.IsSequence() || node.size() != 2) return false;

		rhs.m_StartPinId = node[1].as<UINT64>();
		rhs.m_EndPinId = node[2].as<UINT64>();
		return true;
	}
};