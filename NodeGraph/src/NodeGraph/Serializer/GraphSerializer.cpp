#include "PCH.h"
#include "GraphSerializer.h"
#include "yaml-cpp/yaml.h"
#include "NodeGraph/NodeGraph.h"
#include <fstream>

YAML::Emitter& operator<<(YAML::Emitter& out, const ImVec2& vec)
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
		if(!node.IsSequence() && node.size() != 2) return false;

		rhs.x = node[0].as<float>();
		rhs.y = node[1].as<float>();
		return true;
	}
};

GraphSerializer::GraphSerializer(const Ref<class NodeGraph>& graph)
	:m_Graph(graph)
{

}

void GraphSerializer::Serialize(const std::string& filepath) 
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "Graph";
	out << YAML::Value << "Name";
	out << YAML::Key << "Properties";

	out << YAML::Value << YAML::BeginSeq;

	for (auto prop : m_Graph->m_Properties)
	{
		out << YAML::BeginMap;
		prop->Serialize(out);
		out << YAML::EndMap;
	}

	out << YAML::EndSeq;

	out << YAML::Key << "Links";
	out << YAML::Value << YAML::BeginSeq;

	for (auto& link : m_Graph->m_NodeLinks)
	{
		out << YAML::BeginMap;

		link.second->Serialize(out);

		out << YAML::EndMap;
	}

	out << YAML::EndSeq;

	out << YAML::Key << "Nodes";
	out << YAML::Value << YAML::BeginSeq;

	for (auto& node : m_Graph->m_Nodes)
	{
		out << YAML::BeginMap;
	
		node.second->Serialize(out);

		out << YAML::Key << "Position";
		out << YAML::Value << ed::GetNodePosition(node.first);

		out << YAML::EndMap;
	}

	out << YAML::EndSeq;

	out << YAML::EndMap;

	std::ofstream fout(filepath);
	fout << out.c_str();
}

void GraphSerializer::DeSerialize(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::stringstream strstream;
	strstream << stream.rdbuf();

	YAML::Node data = YAML::Load(strstream.str());
	if(!data["Graph"])
		return;

	std::string graphName = data["Graph"].as<std::string>();
	LOG("Loading Graph... %s", graphName.c_str());

	auto properties = data["Properties"];
	if (properties)
	{
		for (auto property : properties)
		{
			auto type = property["Property Type"].as<std::string>();
			
			auto prop = DataTypeRegistry::Instaniate(type);
			prop->DeSerialize(property);
	
			m_Graph->m_Properties.push_back(Ref<IProperty>(prop));
		}
	}

	auto nodes = data["Nodes"];
	if (nodes)
	{
		for (auto node : nodes)
		{	auto factoryname = node["FactoryName"].as<std::string>();

			bool hasPropertyNode = node["PropertyID"].IsDefined();

			Node* newnode = nullptr;

			if (hasPropertyNode)
			{
				auto id = node["PropertyID"].as<ImGuiID>();

				auto& property = m_Graph->FindProperty(id);

				newnode = NodeRegistry::Instaniate(factoryname, property);
			}			
			else
				newnode = NodeRegistry::Instaniate(factoryname);

			newnode->DeSerialize(node);
			m_Graph->m_Nodes.emplace(newnode->GetID(), Scope<Node>(newnode));

			auto position = node["Position"].as<ImVec2>();
			ed::SetNodePosition(newnode->GetID(), position);
		}
	}

	auto links = data["Links"];
	if (links)
	{
		for (auto link : links)
		{
			Link* nodelink = new Link();
			nodelink->DeSerialize(link);
			m_Graph->m_NodeLinks.emplace(nodelink->GetID(), Scope<Link>(nodelink));
		}
	}

	
}
