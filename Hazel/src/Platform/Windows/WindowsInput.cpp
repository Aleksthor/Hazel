#include "hzpch.h"
#include "WindowsInput.h"
#include "Hazel/Application.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
	// Singleton Instance
	Input* Input::s_Instance = new WindowsInput();

	// Is Key Pressed?
	bool Hazel::WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	// Is Mouse Button Pressed?
	bool Hazel::WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	// Where is Mouse Xpos
	float Hazel::WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePosImpl();

		return x;
	}


	// Where is Mouse Ypos
	float Hazel::WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePosImpl();

		return y;
	}


	// Where is MouseePos
	std::pair<float, float> Hazel::WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}
}