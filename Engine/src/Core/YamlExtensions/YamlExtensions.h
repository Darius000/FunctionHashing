#pragma once

#include "imgui.h"
#include "yaml-cpp/yaml.h"
#include "glm/glm.hpp"

using Vec2 = glm::vec2;

namespace YAML
{

	inline Emitter& operator <<(Emitter& out, const Vec2& rhs)
	{
		return out << BeginSeq << rhs.x << rhs.y << EndSeq;
	}

	template<>
	struct convert<Vec2>
	{
		static Node encode(const Vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, Vec2& rhs)
		{
			if (!node.IsSequence() && node.size() != 2) return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	//ImVec2
	inline YAML::Emitter& operator<<(YAML::Emitter& out, const ImVec2& vec)
	{
		out << YAML::BeginSeq;
		out << vec.x;
		out << vec.y;
		out << YAML::EndSeq;
		return out;
	}

	template<>
	struct YAML::convert<ImVec2>
	{
		static YAML::Node encode(const ImVec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, ImVec2& rhs)
		{
			if (!node.IsSequence() && node.size() != 2) return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

}