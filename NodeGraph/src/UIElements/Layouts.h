#ifndef LAYOUTS_H
#define LAYOUTS_H


#include "UIElement.h"


class LayoutElement : public UIElement
{
protected:
	LayoutElement() {};

protected:

	virtual void BeginLayout(uint32_t id) = 0;

	virtual void EndLayout() = 0;

	virtual void OnBeginChildLayout() {}

	virtual void OnEndChildLayout() {}

public:
	void AddChild(UIElement* element);

	void RemoveElement(UIElement* element);

	void RemoveElement(const std::string& name);

	std::vector<Ref<UIElement>>& GetChildren() { return m_Children; }

	size_t GetChildCount() const { return m_Children.size(); }


	void Clear();


protected:

	void OnDrawElement() override;

	bool HandleEvents() override;

private:
	std::vector<Ref<UIElement>> m_Children;

};


class HorizontalElement : public LayoutElement
{
public:

	HorizontalElement();

protected:
	void BeginLayout(uint32_t id) override;

	void EndLayout() override;

	virtual void OnBeginChildLayout() override;

	virtual void OnEndChildLayout() override;
};

class VerticalElement : public LayoutElement
{
public:

	VerticalElement() {}

protected:
	void BeginLayout(uint32_t id) override;

	void EndLayout() override;

	virtual void OnBeginChildLayout() override;

	virtual void OnEndChildLayout() override;
};

#endif // !HORIZONTALELEMENT_H
