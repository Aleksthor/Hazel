#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_layers.begin();
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_layers.emplace(m_LayerInsert, layer);
	}
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
			m_LayerInsert--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
		}
	}
}