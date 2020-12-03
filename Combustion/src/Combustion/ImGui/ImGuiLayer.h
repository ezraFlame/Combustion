#pragma once

#include "Combustion/Layer.h"
#include "Combustion/Core.h"
#include "Combustion/Events/MouseEvent.h"
#include "Combustion/Events/KeyEvent.h"
#include "Combustion/Events/ApplicationEvent.h"

namespace Combustion {
	class CB_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0;
	};
}