#pragma once

#include "Core.h"

namespace Combustion {
	class CB_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//to be defined in CLIENT
	Application* CreateApplication();
}