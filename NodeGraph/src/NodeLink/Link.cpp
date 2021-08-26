#include "PCH.h"
#include "Link.h"

YAML::Emitter& operator << (YAML::Emitter& out, const ed::PinId& id)
{
	out << id.Get();
	return out;
}

template<>
struct YAML::convert<ed::PinId>
{
	static YAML::Node encode(const ed::PinId& rhs)
	{
		Node node;
		node.push_back((unsigned int)rhs.Get());
		return node;
	}

	static bool decode(const Node& node, ed::PinId& rhs)
	{
		auto v = node[0].as<unsigned int>();
		rhs = v;
		return true;
	}
};

Link::Link(ed::PinId startpin, ed::PinId endpin)
	:m_StartPin(startpin), m_EndPin(endpin)
{
	
}

void Link::Serialize(YAML::Emitter& out)
{
	NodeEditorObject::Serialize(out);

	out << YAML::Key << "StartPin";
	out << YAML::Value << (unsigned int)m_StartPin.Get();
	out << YAML::Key << "EndPin";
	out << YAML::Value << (unsigned int)m_EndPin.Get();

}

void Link::DeSerialize(YAML::detail::iterator_value& value)
{
	NodeEditorObject::DeSerialize(value);

	m_StartPin = value["StartPin"].as<unsigned int>();
	m_EndPin = value["EndPin"].as<unsigned int>();
}

