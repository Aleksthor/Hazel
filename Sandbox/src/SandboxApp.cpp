#include <Hazel.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-3.2, 3.2, -1.8, 1.8), m_CameraPosition(0.f,0.f,0.f), m_TrianglePosition (-2.f,0.f,0.f)
	{
		// Setup an Open GL Triangle
		#pragma region Triangle Vertex/Index/Layout

		// Create Vertex Array
		m_TriangleVertexArray.reset(Hazel::VertexArray::Create());

		// Verteces
		float TriangleVerteces[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // X,Y,Z, R,G,B,A
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // X,Y,Z, R,G,B,A
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f  // X,Y,Z, R,G,B,A
		};

		// Create Vertex Buffer
		Hazel::Ref<Hazel::VertexBuffer> TriangleVertexBuffer;
		TriangleVertexBuffer.reset(Hazel::VertexBuffer::Create(TriangleVerteces, sizeof(TriangleVerteces)));

		// Setup Buffer Layout

		Hazel::BufferLayout layout = {
			{ Hazel::ShaderDataType::Float3, "a_Position"},
			{ Hazel::ShaderDataType::Float4, "a_Color" }
		};

		TriangleVertexBuffer->SetLayout(layout);

		// Add Buffer to Vertex Array
		m_TriangleVertexArray->AddVertexBuffer(TriangleVertexBuffer);



		unsigned int indeces[3] =
		{
			0, 1, 2
		};

		// Create Index Buffer
		Hazel::Ref<Hazel::IndexBuffer> TriangleIndexBuffer;
		TriangleIndexBuffer.reset(Hazel::IndexBuffer::Create(indeces, sizeof(indeces) / sizeof(uint32_t)));
		m_TriangleVertexArray->SetIndexBuffer(TriangleIndexBuffer);
		#pragma endregion

		// Setup and Open GL Square
		#pragma region Square Vertex/Index/Layout

		// Create a Square Vertex Array
		m_SquareVertexArray.reset(Hazel::VertexArray::Create());

		// Verteces
		float SquareVerteces[5 * 4] =
		{
			-1.0f, -1.0f, 0.0f, 0.f, 0.f,
			 1.0f, -1.0f, 0.0f, 1.f, 0.f,
			 1.0f,  1.0f, 0.0f, 1.f, 1.f,
			-1.0f,  1.0f, 0.0f, 0.f, 1.f
		};

		// Create Buffer
		Hazel::Ref<Hazel::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Hazel::VertexBuffer::Create(SquareVerteces, sizeof(SquareVerteces)));

		// Setup Square Buffer Layout
		Hazel::BufferLayout Squarelayout = {
			{ Hazel::ShaderDataType::Float3, "a_Position"},
			{ Hazel::ShaderDataType::Float2, "a_TexCoord"}
		};

		squareVertexBuffer->SetLayout(Squarelayout);
		// Add Buffer to Vertex Array
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		// Indeces

		unsigned int squareIndeces[6] =
		{
			0, 1, 2, 2, 3, 0
		};
		// Create Index Buffer
		Hazel::Ref<Hazel::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Hazel::IndexBuffer::Create(squareIndeces, sizeof(squareIndeces) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);


		#pragma endregion


		// Shaders

		m_ShaderLibrary.Load("assets/shaders/examples/ExampleTriangle.glsl");
		m_ShaderLibrary.Load("assets/shaders/examples/ExampleSquare.glsl");


		auto TextureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Hazel::Texture2D::Create("assets/textures/Nidaros.png");

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(TextureShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Hazel::Timestep dT) override
	{
		float deltaTime = dT;
		HZ_TRACE("Delta Time: {0}, ({1}ms)", dT.GetSeconds(), dT.GetMilliseconds());

		//Move Triangle
		#pragma region WASD
		if (Hazel::Input::IsKeyPressed(KEY_W))
		{
			m_TrianglePosition.y += 1.f * deltaTime;
		}

		if (Hazel::Input::IsKeyPressed(KEY_A))
		{
			m_TrianglePosition.x -= 1.f * deltaTime;
		}

		if (Hazel::Input::IsKeyPressed(KEY_S))
		{
			m_TrianglePosition.y -= 1.f * deltaTime;
		}

		if (Hazel::Input::IsKeyPressed(KEY_D))
		{
			m_TrianglePosition.x += 1.f * deltaTime;
		}

		#pragma endregion 

		//Rotate Camera
		#pragma region QE

		if (Hazel::Input::IsKeyPressed(KEY_Q))
		{
			m_Camera.SetRotation(m_Camera.GetRotation() + 60.f * deltaTime);
		}
		if (Hazel::Input::IsKeyPressed(KEY_E))
		{
			m_Camera.SetRotation(m_Camera.GetRotation() - 60.f * deltaTime);
		}

		#pragma endregion

		//Move Camera
		#pragma region UP/LEFT/DOWN/RIGHT

		if (Hazel::Input::IsKeyPressed(KEY_UP))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.f, m_CameraSpeed, 0.f) * deltaTime);
		}
		if (Hazel::Input::IsKeyPressed(KEY_LEFT))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(-m_CameraSpeed, 0.f, 0.f) * deltaTime);
		}
		if (Hazel::Input::IsKeyPressed(KEY_DOWN))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.f, -m_CameraSpeed, 0.f) * deltaTime);
		}
		if (Hazel::Input::IsKeyPressed(KEY_RIGHT))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(m_CameraSpeed, 0.f, 0.f) * deltaTime);
		}


		#pragma endregion

		Hazel::RenderCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommands::Clear();

		Hazel::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
		glm::vec4 redColor(0.3f, 0.8f, 0.3f, 1.f);

		
		auto squareShader = m_ShaderLibrary.Get("ExampleSquare");

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(squareShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(squareShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		auto triangleShader = m_ShaderLibrary.Get("ExampleTriangle");

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(triangleShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(triangleShader)->UploadUniformFloat3("u_Color", m_TriangleColor);
		
		for (int i{}; i < 10; i++)
		{
			for (int j{}; j < 10; j++)
			{
				glm::vec3 pos(i * 0.22f - 1.f, j * 0.22f - 1.f , 0.f);
				glm::mat4 squareTransform = glm::translate(glm::mat4(1.f), pos) * scale;
				Hazel::Renderer::Submit(m_SquareVertexArray, squareShader, squareTransform);

			}
		}

		m_Texture->Bind();
		
		auto textureShader = m_ShaderLibrary.Get("Texture");

		scale = glm::scale(glm::mat4(1.f), glm::vec3(0.8f));
		glm::vec3 pos(2.2f, -0.7f, 0.f);
		glm::mat4 textureTransform = glm::translate(glm::mat4(1.f), pos) * 0.8f;
		Hazel::Renderer::Submit(m_SquareVertexArray, textureShader, textureTransform);

		glm::mat4 triangleTransform = glm::translate(glm::mat4(1.f), m_TrianglePosition);
		Hazel::Renderer::Submit(m_TriangleVertexArray, triangleShader, triangleTransform);

		Hazel::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("SquareSettings");
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));
		ImGui::End();

		ImGui::Begin("TriangleSettings");
		ImGui::ColorEdit3("TriangleColor", glm::value_ptr(m_TriangleColor));
		ImGui::End();
	}

	void OnEvent(Hazel::Event& event) override
	{
		Hazel::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Hazel::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Hazel::KeyPressedEvent& event)
	{

		return false; // Block other layers?
	}

private:
	Hazel::ShaderLibrary m_ShaderLibrary;

	Hazel::Ref<Hazel::VertexArray> m_TriangleVertexArray;
	Hazel::Ref<Hazel::VertexArray> m_SquareVertexArray;

	Hazel::Ref<Hazel::Texture2D> m_Texture;



	Hazel::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.6f;

	glm::vec3 m_TrianglePosition = { -5.f,0.f,0.f };
	float m_TriangleRotation = 0.f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
	glm::vec3 m_TriangleColor = { 0.2f, 0.8f, 0.2f };
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}