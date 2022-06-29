#pragma once

#include "Core/UUID.h"
#include <yaml-cpp/yaml.h>

struct LinkInfo
{
	Core::UUID m_StartPinId;

	Core::UUID m_EndPinId;
};


inline YAML::Emitter& operator << (YAML::Emitter& out, const LinkInfo& id)
{
	out << YAML::BeginSeq << (uint64_t)id.m_StartPinId << (uint64_t)id.m_EndPinId << YAML::EndSeq;
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