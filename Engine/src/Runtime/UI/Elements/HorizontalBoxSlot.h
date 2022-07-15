#pragma once 

#include "LayoutSlot.h"

struct SlotConfiguration : public LayoutConfig
{
	SlotConfiguration(float sw = 1.0f, float sp = -1.0f, float ew = 0.0f, float es = 0.0f)
		:m_StartWeight(sw), m_StartSpacing(sp), m_EndWeight(ew), m_EndSpacing(es)
	{

	}

	float m_StartWeight = 1.0f;

	float m_StartSpacing = -1.0f;

	float m_EndWeight = 0.0f;

	float m_EndSpacing = 0.0f;

	void DrawWindow(const std::string& name)
	{
		if (ImGui::Begin((name + "Configuration").c_str()))
		{
			ImGui::DragFloat("Start Weight",	&m_StartWeight	, .1f, -1.0f, 1.0f);
			ImGui::DragFloat("Start Space",		&m_StartSpacing	, .1f, -1.0f, 1.0f);
			ImGui::DragFloat("End Weight",		&m_EndWeight	, .1f, -1.0f, 1.0f);
			ImGui::DragFloat("End Space",		&m_EndSpacing	, .1f, -1.0f, 1.0f);
			ImGui::End();
		}
	}
};

class HorizontalBoxSlot : public LayoutSlot
{
public:
	HorizontalBoxSlot() {}
	HorizontalBoxSlot(const LayoutConfig& config) : m_Configuration((const SlotConfiguration&)config) {}

protected:
	virtual void OnBeginSlotLayout() override;

	virtual void OnEndSlotLayout() override;

public:
	
	SlotConfiguration m_Configuration;

	REFLECTABLEV(LayoutSlot)
};

