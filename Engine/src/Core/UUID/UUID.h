#pragma once

#include <stdint.h>
#include <xhash>
#include "yaml-cpp/yaml.h"

namespace Core
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID&) = default;

		operator uint32_t() const { return m_UUID & 0xFFFFFFFF;}

		operator uint64_t() const { return m_UUID;  }

		bool operator==(const UUID& rhs) const
		{
			return m_UUID == rhs.m_UUID;
		}

		UUID operator=(const UUID& rhs)
		{
			m_UUID = rhs.m_UUID;
			return *this;
		}

	private:
		uint64_t m_UUID;
	};
}

namespace std
{
	template<>
	struct hash<Core::UUID>
	{
		std::size_t operator()(const Core::UUID& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}

inline YAML::Emitter& operator << (YAML::Emitter& out, const Core::UUID& id)
{
	out << (uint64_t)id;
	return out;
}

template<>
struct YAML::convert<Core::UUID>
{
	static YAML::Node encode(const Core::UUID& rhs)
	{
		Node node;
		node.push_back((uint64_t)rhs);
		return node;
	}

	static bool decode(const Node& node, Core::UUID& rhs)
	{
		auto v = node[0].as<uint64_t>();
		rhs = Core::UUID(v);
		return true;
	}
};