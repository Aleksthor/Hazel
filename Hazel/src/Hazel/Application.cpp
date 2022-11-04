#include "hzpch.h"
#include "Application.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace Hazel
{

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}


	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

}

