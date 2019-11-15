#include <depch.h>
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Defiant {

	struct Renderer2DStorage {
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init() {

		s_Data = new Renderer2DStorage();

		s_Data->QuadVertexArray = VertexArray::Create();
		Ref<VertexBuffer> sqVB;

		float verticesSquare[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		sqVB = VertexBuffer::Create(verticesSquare, sizeof(verticesSquare));
		BufferLayout sqLayout = {
			{ShaderDataType::Float3, "a_Position"}
		};
		sqVB->SetLayout(sqLayout);
		s_Data->QuadVertexArray->AddVertexBuffer(sqVB);

		Ref<IndexBuffer> sqIB;

		uint32_t indicesSquare[6] = {
			0, 1, 2,
			2, 3, 0
		};

		sqIB = IndexBuffer::Create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(sqIB);


		s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown() {
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene() {

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetFloat4("u_Color", color);
		glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->FlatColorShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}