#include "PCH.h"
#include "Node.h"


Node::Node()
{
	m_Color = { .2f, .2f, .2f, .9f };
	m_TitleColor = {0.0f, .2f, 1.0f, .5f};
	m_Rounding = 5.0f;
	m_NumInputs = 0;
	m_NumOutputs = 0;
}

Pin* Node::FindPin(ImGuiID id) const
{
	auto it = std::find_if(m_Pins.begin(), m_Pins.end(), [id](const Ref<Pin> pin)
	{
		return pin->GetID() == id;
	});

	return it != m_Pins.end() ? it->get() : nullptr;
}

void Node::Serialize(YAML::Emitter& out)
{
	NodeEditorObject::Serialize(out);

	out << YAML::Key << "FactoryName";
	out << YAML::Value << GetFactoryName();

	out << YAML::Key << "Pins";
	out << YAML::Value << YAML::BeginSeq;

	for (auto pin : m_Pins)
	{
		out << YAML::BeginMap;
		pin->Serialize(out);
		out << YAML::EndMap;
	}

	out << YAML::EndSeq;
}

void Node::DeSerialize(YAML::detail::iterator_value& value)
{
	NodeEditorObject::DeSerialize(value);

	auto pins = value["Pins"];

	if (pins)
	{
		size_t i = 0;
		for (auto d : pins)
		{
			m_Pins[i++]->DeSerialize(d);
		}
	}

}

DataPin* Node::AddDataPin(const std::string& name, ed::PinKind pinkind,Ref<IProperty> prop)
{
	auto pin = MakeRef<DataPin>();
	pin->pinKind = pinkind;
	pin->m_Property = prop;
	pin->SetName(name);

	//add lambda to change map key when prop name changes
	prop->OnNameChanged.AddBinding([pin](const std::string& name)
	{
		pin->SetName(name);
	});

	m_Pins.push_back(pin);

	if(pinkind == ed::PinKind::Input)	{m_Inputs.push_back(pin); m_NumInputs++;	}
	if(pinkind == ed::PinKind::Output)	{m_Outputs.push_back(pin); m_NumOutputs++;	}
	return pin.get();
}

void Node::AddExecutionPin(const std::string& name, ed::PinKind pinkind)
{
	auto pin = MakeRef<ExecutionPin>();
	pin->pinKind = pinkind;
	pin->SetName(name);

	m_Pins.push_back(pin);
	if (pinkind == ed::PinKind::Input)	{m_Inputs.push_back(pin); m_NumInputs++;	}
	if (pinkind == ed::PinKind::Output) {m_Outputs.push_back(pin);	m_NumOutputs++;	}
}
