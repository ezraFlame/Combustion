#include "cbpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glad/glad.h>

namespace Combustion {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
		CB_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CB_CORE_ASSERT(status, "Failed to initilize Glad!");

		CB_CORE_INFO("OpenGL Info:");
		CB_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CB_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CB_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}