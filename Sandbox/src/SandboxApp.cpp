#include <Defiant.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Defiant::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -.9f, .9f), camera_pos(0, 0, 0), m_SquarePos(0){
		m_TriVA = Defiant::VertexArray::Create();
		Defiant::Ref<Defiant::VertexBuffer> triVB;

		m_Camera.SetRotation(0.0f);

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

		Defiant::Ref<Defiant::IndexBuffer> triIB;

		uint32_t triIndices[3] = {
			0, 1, 2
		};

		triIB.reset(Defiant::IndexBuffer::Create(triIndices, sizeof(triIndices) / sizeof(uint32_t)));
		m_TriVA->SetIndexBuffer(triIB);

		m_SqVA = Defiant::VertexArray::Create();
		Defiant::Ref<Defiant::VertexBuffer> sqVB;

		float verticesSquare[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		sqVB.reset(Defiant::VertexBuffer::Create(verticesSquare, sizeof(verticesSquare)));
		Defiant::BufferLayout sqLayout = {
			{Defiant::ShaderDataType::Float3, "a_Position"},
			{Defiant::ShaderDataType::Float2, "a_TexCoord"}
		};
		sqVB->SetLayout(sqLayout);
		m_SqVA->AddVertexBuffer(sqVB);

		Defiant::Ref<Defiant::IndexBuffer> sqIB;

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

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main(){
				v_Color = a_Color;
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_TriShader.reset(Defiant::Shader::Create(vertexTri, fragmentTri));

		std::string vertexFlatColor = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			
			void main(){
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}	
		)";

		std::string fragmentFlatColor = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;
			
			void main(){
				color = vec4(0.3, 0.3, 0.8, 1.0);
				color = vec4(u_Color, 1.0);
			}	
		)";

		m_FlatColorShader.reset(Defiant::Shader::Create(vertexFlatColor, fragmentFlatColor));

		std::string vertexTexture = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			
			void main(){
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}	
		)";

		std::string fragmentTexture = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform sampler2D u_Texture;

			in vec2 v_TexCoord;
			
			void main(){
				color = texture(u_Texture, v_TexCoord);
			}	
		)";

		m_TextureShader.reset(Defiant::Shader::Create(vertexTexture, fragmentTexture));
		m_Texture = Defiant::Texture2D::Create("assets/textures/checkerboard.png");
		m_ChernoTexture = Defiant::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Defiant::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Defiant::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Defiant::TimeStep ts) override {
		
		m_Camera.SetPosition(m_SquarePos);
		Defiant::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Defiant::RenderCommand::Clear();

		Defiant::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(.1f));

		std::dynamic_pointer_cast<Defiant::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Defiant::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Defiant::Renderer::Submit(m_SqVA, m_FlatColorShader, transform);
			}
		}
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePos) * glm::scale(glm::mat4(1.0f), glm::vec3(.2f));
		m_Texture->Bind();
		Defiant::Renderer::Submit(m_SqVA, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ChernoTexture->Bind();
		Defiant::Renderer::Submit(m_SqVA, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Defiant::Renderer::Submit(m_TriVA, m_TriShader, transform);
		//Defiant::Renderer::Submit(m_TriVA, m_TriShader);
		Defiant::Renderer::EndScene();

		if (Defiant::Input::IsKeyPressed(DE_KEY_LEFT)) {
			m_SquarePos.x -= 1 * ts;
		}
		if (Defiant::Input::IsKeyPressed(DE_KEY_RIGHT)) {
			m_SquarePos.x += 1 * ts;
		}

		if (Defiant::Input::IsKeyPressed(DE_KEY_UP)) {
			m_SquarePos.y += 1 * ts;
		}
		if (Defiant::Input::IsKeyPressed(DE_KEY_DOWN)) {
			m_SquarePos.y -= 1 * ts;
		}
	}

	void OnImGuiRender() override {

		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();

	}

	void OnEvent(Defiant::Event& event) override {
		
	}
private:
	Defiant::Ref<Defiant::VertexArray> m_TriVA;
	Defiant::Ref<Defiant::VertexArray> m_SqVA;
	Defiant::Ref<Defiant::Shader> m_TriShader;
	Defiant::Ref<Defiant::Shader> m_FlatColorShader;
	Defiant::Ref<Defiant::Shader> m_TextureShader;
	Defiant::Ref<Defiant::Texture> m_Texture;
	Defiant::Ref<Defiant::Texture> m_ChernoTexture;
	glm::vec3 camera_pos;
	Defiant::OrthographicCamera m_Camera;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	glm::vec3 m_SquarePos;
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