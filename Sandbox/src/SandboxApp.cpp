#include <Combustion.h>
#include "imgui/imgui.h"


class TestLayer : public Combustion::Layer {
public:
	TestLayer() : Layer("Test"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
		m_VertexArray.reset(Combustion::VertexArray::Create());

		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<Combustion::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Combustion::VertexBuffer::Create(vertices, sizeof(vertices)));

		Combustion::BufferLayout layout = {
			{ Combustion::ShaderDataType::Float3, "a_Position" },
			{ Combustion::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Combustion::IndexBuffer> indexBuffer;
		indexBuffer.reset(Combustion::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Combustion::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f
		};

		std::shared_ptr<Combustion::VertexBuffer> squareVB;
		squareVB.reset(Combustion::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Combustion::BufferLayout squareVBLayout = {
			{ Combustion::ShaderDataType::Float3, "a_Position" }
		};

		squareVB->SetLayout(squareVBLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Combustion::IndexBuffer> squareIB;
		squareIB.reset(Combustion::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() {
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(Combustion::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	bool showChild = false;

	void OnUpdate() override {
		if (m_GoodMovement) {
			if (Combustion::Input::IsKeyPressed(CB_KEY_W)) {
				m_CameraPosition.y += m_CameraMoveSpeed;
			}
			else if (Combustion::Input::IsKeyPressed(CB_KEY_S)) {
				m_CameraPosition.y -= m_CameraMoveSpeed;
			}
			if (Combustion::Input::IsKeyPressed(CB_KEY_D)) {
				m_CameraPosition.x += m_CameraMoveSpeed;
			}
			else if (Combustion::Input::IsKeyPressed(CB_KEY_A)) {
				m_CameraPosition.x -= m_CameraMoveSpeed;
			}
			if (Combustion::Input::IsKeyPressed(CB_KEY_Q)) {
				m_CameraRotation -= m_CameraRotateSpeed;
			}
			else if (Combustion::Input::IsKeyPressed(CB_KEY_E)) {
				m_CameraRotation += m_CameraRotateSpeed;
			}
		}

		Combustion::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Combustion::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Combustion::Renderer::BeginScene(m_Camera);
		Combustion::Renderer::Submit(m_BlueShader, m_SquareVA);
		Combustion::Renderer::Submit(m_Shader, m_VertexArray);
		Combustion::Renderer::EndScene();
	}

	void OnEvent(Combustion::Event& event) override {
		Combustion::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Combustion::KeyPressedEvent>(CB_BIND_EVENT_FN(TestLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Combustion::KeyPressedEvent& event) {
		if (!m_GoodMovement) {
			switch (event.GetKeyCode()) {
			case CB_KEY_W:
				m_CameraPosition.y += m_CameraMoveSpeed;
				break;
			case CB_KEY_A:
				m_CameraPosition.x -= m_CameraMoveSpeed;
				break;
			case CB_KEY_S:
				m_CameraPosition.y -= m_CameraMoveSpeed;
				break;
			case CB_KEY_D:
				m_CameraPosition.x += m_CameraMoveSpeed;
				break;
			case CB_KEY_Q:
				m_CameraRotation -= m_CameraRotateSpeed;
				break;
			case CB_KEY_E:
				m_CameraRotation += m_CameraRotateSpeed;
				break;
			}
		}

		return false;
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Movement");
		ImGui::Checkbox("Smooth Movement?", &m_GoodMovement);
		ImGui::SliderFloat("Move Speed", &m_CameraMoveSpeed, 0.0f, 0.2f);
		ImGui::SliderFloat("Rotate Speed", &m_CameraRotateSpeed, 0.0f, 10.0f);
		ImGui::End();
	}
private:
	std::shared_ptr<Combustion::Shader> m_Shader;
	std::shared_ptr<Combustion::VertexArray> m_VertexArray;

	std::shared_ptr<Combustion::Shader> m_BlueShader;
	std::shared_ptr<Combustion::VertexArray> m_SquareVA;

	Combustion::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotateSpeed = 2.0f;

	bool m_GoodMovement = false;
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