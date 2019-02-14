#pragma once

#ifdef DE_PLATFORM_WINDOWS

extern Defiant::Application* Defiant::CreateApplication();

int main(int argc, char** argv) {
	auto app = Defiant::CreateApplication();
	app->Run();
	delete app;
}

#endif