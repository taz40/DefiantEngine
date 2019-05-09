#include "depch.h"
#include "Application.h"

#include "Defiant/Events/ApplicationEvent.h"
#include "Defiant/Log.h"
#include "Input.h"

#include "Platform/OpenGL/OpenGLRenderer.h"

//WARNING TEMPORARY
#include <glad/glad.h>

namespace Defiant {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		DE_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//WARNING! TEMPORARY CODE
		renderer = new OpenGLRenderer();
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;

			}
		}
	}

	void Application::Run() {
		while (m_Running) {
			renderer->clear();

			unsigned int vbo;
			unsigned int vao;
			unsigned int ibo;
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			glEnableVertexAttribArray(0);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			float* vertecies = new float[12] {-.5f, .5f, 0, .5f, .5f, 0, -.5f, -.5f, 0, .5f, -.5f, 0};
			glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertecies, GL_STATIC_DRAW);
			unsigned int* indecies = new unsigned int[6] {0, 1, 2, 1, 3, 2};
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indecies, GL_STATIC_DRAW);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

}