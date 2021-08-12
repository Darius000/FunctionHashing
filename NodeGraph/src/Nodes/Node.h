#pragma once

#include "Core/Core.h"
#include "DataTypes/Property.h"
#include "INodeCreation.h"
#include "NodeEditorObject.h"
#include "Registry/NodeRegistry.h"
#include "Pin.h"

template<class T>
using Array = std::vector<Scope<T>>;



enum class ETitleStyle_ : int
{
	Default = 0,
	Custom
};

using Parameters = std::unordered_map<std::string, Ref<PropertyWrapper>>;
using ExecutionPins = std::vector<Ref<ExecutionPin>>;

class Node : public NodeEditorObject, public INodeCreation
{

public:
	Node();
	virtual ~Node() = default;

	virtual std::string GetTypeName() const { return "Node"; }

	virtual void OnDraw() override;
	virtual void OnDrawDetails() override;

	//Execute a function
	void Execute();

protected:
	void BeginDraw();
	void EndDraw();
	void DrawDataPins();

	virtual void CustomDraw();
	virtual void OnExecute() {};

public:
	PropertyWrapper* GetParameter(const std::string& name);

	Parameters& GetParameters() { return m_Parameters; }

	PropertyWrapper* GetParameterWithID(ImGuiID id);

	std::vector<ExecutionPin*> GetExecutionPinsByType(ImNodesAttributeType_ type) const;

protected:
	ETitleStyle_ m_TitleStyle;

	ImVec2 m_DefaultSize;
	ImVec2 m_Size;
	ImVec2 m_ScreenPos;
	ImVec4 m_Color;
	ImVec4 m_TitleColor;
	float m_Rounding;

protected:

	void AddDataPin(const std::string& name, PropertyType type, Ref<IProperty> prop)
	{
		if (m_Parameters.find(name) == m_Parameters.end())
		{
			auto propertywrapper = MakeRef<PropertyWrapper>(type, prop);

			//add lambda to change map key when prop name changes
			prop->OnNameChanged.AddBinding([this, prop](const std::string& name)
			{
				auto it = std::find_if(m_Parameters.begin(), m_Parameters.end(), [prop](const auto& p){
					return p.first == prop->GetName();
				});

				if (it != m_Parameters.end())
				{
					auto nodeHandler = m_Parameters.extract(it->first);
					nodeHandler.key() = name;
					m_Parameters.insert(std::move(nodeHandler));
				}
				
			});

			m_Parameters.emplace(name, propertywrapper);
			if (type == PropertyType::Input)
			{
				m_InputParameters.emplace(name, propertywrapper);
			}
			else
			{
				m_OutputParameters.emplace(name, propertywrapper);
			}
		}
			
	}

	void AddExecutionPin(ImNodesAttributeType_ type);

protected:
	Parameters m_Parameters;
	Parameters m_InputParameters;
	Parameters m_OutputParameters;
	ExecutionPins m_ExecPins;

	bool m_IsSelected = false;
};


