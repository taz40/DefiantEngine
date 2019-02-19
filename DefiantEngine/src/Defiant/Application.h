#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Defiant {

	class DE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();

}