#pragma once

#include "Combustion/Core.h"
#include "Combustion/Events/Event.h"
#include "Combustion/Core/Timestep.h"

namespace Combustion {
	class CB_API Layer {
	public:
		Layer(const std::string& name = "Layer");

		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}