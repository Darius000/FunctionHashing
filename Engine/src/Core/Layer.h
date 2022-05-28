#pragma once
#include "Event.h"

class Layer
{
public:
	Layer(const std::string& name = "Layer") { m_Name = name; }
	virtual ~Layer() {};
	virtual void OnAttach() {};
	virtual void OnUpdate(float deltaTime) {};
	virtual void OnImGuiRender() {}
	virtual void OnDetach() {};

	virtual void ProcessEvents(Event& e){};

protected:
	std::string m_Name;
};

class LayerStack
{
	using Layers = std::vector<Layer*>;

public:

	LayerStack();

	~LayerStack();

	//add new layer to stack
	void PushLayer(Layer* layer);

	//remove layer from stack
	void PopLayer(Layer* layer);

	Layers GetLayers() const { return m_Layers; }

	Layers::iterator begin() { return m_Layers.begin(); }

	Layers::iterator end() { return m_Layers.end(); }

	Layers::const_iterator cbegin() { return m_Layers.cbegin(); }

	Layers::const_iterator cend() { return m_Layers.cend(); }

private:
	Layers m_Layers;

	uint32_t m_LayerInsertIndex = 0;
};