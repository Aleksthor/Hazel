#include "hzpch.h"
#include "Application.h"
#include "Hazel/Log.h"
#include "Input.h"
#include "Hazel/Renderer/Renderer.h"
#include "Keycodes.h"
#include "Hazel/Renderer/OrthographicCamera.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
	// Singleton Instance initialized in constructor
	Application* Application::s_Instance = nullptr;


	// Constructor
	Application::Application()

	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists")
		s_Instance = this;

		// Setup Window
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(false);

		// Setup an ImGuiLayer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application()
	{
	}


	// Main loop of our Application
	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime(); // Platform::GetTime
			Timestep deltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(deltaTime);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

		}
	}


	// Callback function whenever an event happens. All events go here
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClosed));

		//HZ_CORE_INFO("{0}",e);


		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
			
		}
	}

	// Place a layer on top of existing layers
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	// Place an overlay on top of existing overlays
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	
	// Quit application
	bool Application::onWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}

