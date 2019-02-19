#include "Application.h"

#include "Defiant/Events/ApplicationEvent.h"
#include "Defiant/Log.h"

namespace Defiant {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run() {

		WindowResizeEvent e(1280, 720);
		DE_TRACE(e);

		while (true) {
			
		}
	}

}