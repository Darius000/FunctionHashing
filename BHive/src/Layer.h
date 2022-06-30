#pragma once

namespace BHive
{
	class Layer
	{
	public:
		Layer() {}
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDetach() {};

		virtual void OnUIRender() {}
	};

}