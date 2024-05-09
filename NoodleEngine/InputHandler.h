#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "CameraController.h"

inline void mouse_Callback(GLFWwindow* window, double xPosIn, double yPosIn)
{
	CameraController* cameraController = static_cast<CameraController*>(glfwGetWindowUserPointer(window));
	if (cameraController)
	{
		cameraController->onMouseMove(xPosIn, yPosIn);
	}
}

inline void scroll_Callback(GLFWwindow* window, double xOffset, double yOffset)
{
	CameraController* cameraController = static_cast<CameraController*>(glfwGetWindowUserPointer(window));
	if (cameraController)
	{
		cameraController->onScroll(xOffset, yOffset);
	}
}

inline void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		static bool cursorVisible = true;
		cursorVisible = !cursorVisible;

		CameraController* cameraController = static_cast<CameraController*>(glfwGetWindowUserPointer(window));

		if (cursorVisible)
		{
			cameraController->Stop();
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			cameraController->Start();
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
}