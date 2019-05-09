#include "depch.h"
#include "Application.h"

#include "Defiant/Events/ApplicationEvent.h"
#include "Defiant/Log.h"
#include "Input.h"

#include "Platform/OpenGL/OpenGLRenderer.h"

//WARNING TEMPORARY
#include <glad/glad.h>
#include "Platform/OpenGL/OpenGLVertexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

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

			VertexBuffer* vbo = new OpenGLVertexBuffer();
			float* data = new float[12] { -.5f, .5f, 0, .5f, .5f, 0, -.5f, -.5f, 0, .5f, -.5f, 0 };
			vbo->createBuffer(data, 12);
			vbo->Bind();
			VertexArray* vao = new OpenGLVertexArray();
			vao->createArray();
			vao->Bind();
			unsigned int* indecies = new unsigned int[6] {0, 1, 2, 1, 3, 2};
			IndexBuffer* ibo = new OpenGLIndexBuffer();
			ibo->createBuffer(indecies, 6);
			ibo->Bind();
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