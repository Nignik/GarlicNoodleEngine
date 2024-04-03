#include "CameraController.h"

CameraController* CameraController::currentInstance = nullptr;

CameraController::CameraController(GLFWwindow* window, std::shared_ptr<Camera> camera)
	: window(window), camera(camera), lastX(400), lastY(300), firstMouse(true)
{
	currentInstance = this; // Set the current instance to this object.
	glfwSetCursorPosCallback(window, CameraController::mouse_Callback);
	glfwSetScrollCallback(window, CameraController::scroll_Callback);
	// Initially disable cursor for camera movement.
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CameraController::processInput(float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
}

void CameraController::mouse_Callback(GLFWwindow* window, double xPosIn, double yPosIn)
{
	if (currentInstance) // Ensure the current instance is valid.
	{
		currentInstance->onMouseMove(xPosIn, yPosIn);
	}
}

void CameraController::scroll_Callback(GLFWwindow* window, double xOffset, double yOffset)
{
	if (currentInstance) // Ensure the current instance is valid.
	{
		currentInstance->onScroll(xOffset, yOffset);
	}
}

void CameraController::onMouseMove(double xPosIn, double yPosIn)
{
	float xPos = static_cast<float>(xPosIn);
	float yPos = static_cast<float>(yPosIn);

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos; // Reversed since y-coordinates go from bottom to top

	lastX = xPos;
	lastY = yPos;

	camera->ProcessMouseMovement(xOffset, yOffset);
}

void CameraController::onScroll(double xOffset, double yOffset)
{
	camera->ProcessMouseScroll(static_cast<float>(yOffset));
}