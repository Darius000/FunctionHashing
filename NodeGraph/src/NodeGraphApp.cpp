#include <Engine.h>
#include <Core/Entrypoint.h>

#include "GraphLayer.h"

class NodeGraphApp : public Application
{
public:

	NodeGraphApp(ApplicationCommandLineArgs args)
		:Application("Node Graph", args)
	{
		PushLayer(new GraphLayer());
	}

	~NodeGraphApp()
	{

	}

};

Application* CreateApplication(ApplicationCommandLineArgs args)
{
	return new NodeGraphApp(args);
}