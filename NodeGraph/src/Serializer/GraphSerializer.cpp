#include "GraphSerializer.h"
#include "NodeGraph/NodeGraph.h"
#include <fstream>



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

	out << YAML::Key << "Nodes";
	out << YAML::Value << YAML::BeginSeq;

	for (auto& node : m_Graph->m_Nodes)
	{
		out << YAML::BeginMap;
	
		node->GetNode()->Serialize(out);

		out << YAML::Key << "Position";
		out << YAML::Value << ed::GetNodePosition((UINT64)node->GetNode()->GetID());

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

			BaseNode* newnode = nullptr;

			
			//newnode = NodeRegistry::Instaniate(factoryname);

			/*newnode->DeSerialize(node);
			m_Graph->m_Nodes.push_back(MakeScope<NodeElement>(newnode));

			auto position = node["Position"].as<ImVec2>();
			ed::SetNodePosition((UINT64)newnode->GetID(), position);*/
		}
	}
}
