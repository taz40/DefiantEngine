#pragma once

#ifdef DE_PLATFORM_WINDOWS

extern Defiant::Application* Defiant::CreateApplication();

int main(int argc, char** argv) {

	Defiant::Log::Init();
	DE_CORE_TRACE("Log initialized");

	auto app = Defiant::CreateApplication();
	app->Run();
	delete app;
}

#endif