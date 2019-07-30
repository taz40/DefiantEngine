#include <Defiant.h>
#include <Defiant/Renderer/Buffer.h>
#include <Defiant/Renderer/VertexArray.h>
#include <Defiant/Renderer/Shader.h>
#include <Defiant/Renderer/Renderer.h>
#include <Defiant/Renderer/RenderCommand.h>

#include "imgui/imgui.h"
#include <Defiant/Renderer/Camera.h>
#include <Defiant/Events/Event.h>

#include <functional>

class ExampleLayer : public Defiant::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -.9f, .9f){
		m_TriVA.reset(Defiant::VertexArray::Create());
		std::shared_ptr<Defiant::VertexBuffer> triVB;

		m_Camera.SetRotation(45.0f);

		float triVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		triVB.reset(Defiant::VertexBuffer::Create(triVertices, sizeof(triVertices)));
		Defiant::BufferLayout triLayout = {
			{Defiant::ShaderDataType::Float3, "a_Position"},
			{Defiant::ShaderDataType::Float4, "a_Color"}
		};
		triVB->SetLayout(triLayout);
		m_TriVA->AddVertexBuffer(triVB);

		std::shared_ptr<Defiant::IndexBuffer> triIB;

		uint32_t triIndices[3] = {
			0, 1, 2
		};

		triIB.reset(Defiant::IndexBuffer::Create(triIndices, sizeof(triIndices) / sizeof(uint32_t)));
		m_TriVA->SetIndexBuffer(triIB);

		m_SqVA.reset(Defiant::VertexArray::Create());
		std::shared_ptr<Defiant::VertexBuffer> sqVB;

		float verticesSquare[4 * 3] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		sqVB.reset(Defiant::VertexBuffer::Create(verticesSquare, sizeof(verticesSquare)));
		Defiant::BufferLayout sqLayout = {
			{Defiant::ShaderDataType::Float3, "a_Position"}
		};
		sqVB->SetLayout(sqLayout);
		m_SqVA->AddVertexBuffer(sqVB);

		std::shared_ptr<Defiant::IndexBuffer> sqIB;

		uint32_t indicesSquare[6] = {
			0, 1, 2,
			2, 3, 0
		};

		sqIB.reset(Defiant::IndexBuffer::Create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t)));
		m_SqVA->SetIndexBuffer(sqIB);

		std::string vertexTri = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_MVP;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main(){
				v_Color = a_Color;
				v_Position = a_Position;
				gl_Position = u_MVP * vec4(a_Position, 1.0);
			}	
		)";

		std::string fragmentTri = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main(){
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}	
		)";

		std::string vertexSquare = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_MVP;
			
			void main(){
				gl_Position = u_MVP * vec4(a_Position, 1.0);
			}	
		)";

		std::string fragmentSquare = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			void main(){
				color = vec4(0.3, 0.3, 0.8, 1.0);
			}	
		)";

		m_TriShader.reset(new Defiant::Shader(vertexTri, fragmentTri));
		m_SqShader.reset(new Defiant::Shader(vertexSquare, fragmentSquare));

	}

	void OnUpdate() override {
		Defiant::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Defiant::RenderCommand::Clear();

		Defiant::Renderer::BeginScene(m_Camera);
		Defiant::Renderer::Submit(m_SqVA, m_SqShader);
		Defiant::Renderer::Submit(m_TriVA, m_TriShader);
		Defiant::Renderer::EndScene();
		if(Defiant::Input::IsKeyPressed(DE_KEY_LEFT)){
			m_Camera.SetRotation(m_Camera.GetRotation() - 1.0f);
		}else if (Defiant::Input::IsKeyPressed(DE_KEY_RIGHT)) {
			m_Camera.SetRotation(m_Camera.GetRotation() + 1.0f);
		}
	}

	void OnImGuiRender() override {

	}

	void OnEvent(Defiant::Event& event) override {
		
	}
private:
	std::shared_ptr<Defiant::VertexArray> m_TriVA;
	std::shared_ptr<Defiant::VertexArray> m_SqVA;
	std::shared_ptr<Defiant::Shader> m_TriShader;
	std::shared_ptr<Defiant::Shader> m_SqShader;
	Defiant::OrthographicCamera m_Camera;
};

class Sandbox : public Defiant::Application {
public:
	Sandbox() {
		DE_TRACE("Created Sandbox App");
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {
		
	}
};


Defiant::Application* Defiant::CreateApplication() {
	return new Sandbox();
}