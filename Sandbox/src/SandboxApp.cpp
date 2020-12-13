#include <Combustion.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>

class TestLayer : public Combustion::Layer {
public:
	TestLayer() : Layer("Test"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
		m_VertexArray.reset(Combustion::VertexArray::Create());

		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		Combustion::Ref<Combustion::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Combustion::VertexBuffer::Create(vertices, sizeof(vertices)));

		Combustion::BufferLayout layout = {
			{ Combustion::ShaderDataType::Float3, "a_Position" },
			{ Combustion::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Combustion::Ref<Combustion::IndexBuffer> indexBuffer;
		indexBuffer.reset(Combustion::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Combustion::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		Combustion::Ref<Combustion::VertexBuffer> squareVB;
		squareVB.reset(Combustion::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Combustion::BufferLayout squareVBLayout = {
			{ Combustion::ShaderDataType::Float3, "a_Position" },
			{ Combustion::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(squareVBLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Combustion::Ref<Combustion::IndexBuffer> squareIB;
		squareIB.reset(Combustion::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Combustion::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main() {
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			uniform vec3 u_Color;

			void main() {
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Combustion::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main() {
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			uniform sampler2D u_Texture;

			in vec2 v_TexCoord;

			void main() {
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Combustion::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Combustion::Texture2D::Create("assets/textures/Arrow.png");

		std::dynamic_pointer_cast<Combustion::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Combustion::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	bool showChild = false;

	void OnUpdate(Combustion::Timestep ts) override {
		//Camera Movement
		if (Combustion::Input::IsKeyPressed(CB_KEY_W)) {
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}
		else if (Combustion::Input::IsKeyPressed(CB_KEY_S)) {
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}
		if (Combustion::Input::IsKeyPressed(CB_KEY_D)) {
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}
		else if (Combustion::Input::IsKeyPressed(CB_KEY_A)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		if (Combustion::Input::IsKeyPressed(CB_KEY_Q)) {
			m_CameraRotation += m_CameraRotateSpeed * ts;
		}
		else if (Combustion::Input::IsKeyPressed(CB_KEY_E)) {
			m_CameraRotation -= m_CameraRotateSpeed * ts;
		}

		Combustion::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Combustion::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Combustion::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Combustion::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Combustion::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Combustion::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		//Combustion::Renderer::Submit(m_Shader, m_VertexArray);

		{
			glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));

			m_Texture->Bind();
			Combustion::Renderer::Submit(m_TextureShader, m_SquareVA, transform);
		}

		Combustion::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Movement");
		ImGui::SliderFloat("Move Speed", &m_CameraMoveSpeed, 0.0f, 10.0f);
		ImGui::SliderFloat("Rotate Speed", &m_CameraRotateSpeed, 0.0f, 50.0f);
		ImGui::End();

		ImGui::Begin("Rendering");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
private:
	Combustion::Ref<Combustion::Shader> m_Shader;
	Combustion::Ref<Combustion::VertexArray> m_VertexArray;

	Combustion::Ref<Combustion::Shader> m_FlatColorShader;
	Combustion::Ref<Combustion::VertexArray> m_SquareVA;

	Combustion::Ref<Combustion::Texture2D> m_Texture;

	Combustion::Ref<Combustion::Shader> m_TextureShader;

	Combustion::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotateSpeed = 10.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3, 0.8f };
};

class Sandbox : public Combustion::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
	}

	~Sandbox() {

	}
};

Combustion::Application* Combustion::CreateApplication() {
	return new Sandbox();
}