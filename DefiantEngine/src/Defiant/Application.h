#pragma once

#include "Core.h"

#include "Window.h"
#include "Defiant/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

#include "Defiant/Renderer/Shader.h"
#include "Defiant/Renderer/Buffer.h"
#include "Defiant/Renderer/VertexArray.h"

namespace Defiant {

	class DE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static inline Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Shader> m_ShaderSquare;

		static Application* s_Instance;
	};

	Application* CreateApplication();

}
