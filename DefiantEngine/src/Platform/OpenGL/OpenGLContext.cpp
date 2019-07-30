#include "depch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Defiant {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle){
		DE_CORE_ASSERT(m_WindowHandle, "Window Handle is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DE_CORE_ASSERT(status, "Failed to initialize glad");

		DE_CORE_INFO("OpenGL Info:");
		DE_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		DE_CORE_INFO("	Device: {0}", glGetString(GL_RENDERER));
		DE_CORE_INFO("	Version : {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
	
}