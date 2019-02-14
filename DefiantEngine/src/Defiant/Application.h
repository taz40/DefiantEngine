#pragma once

#include "Core.h"

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