#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <camera.h>

class CameraController
{
public:
	CameraController(GLFWwindow* window, std::shared_ptr<Camera> camera);
	void processInput(float deltaTime);
	static void mouse_Callback(GLFWwindow* window, double xPosIn, double yPosIn);
	static void scroll_Callback(GLFWwindow* window, double xOffset, double yOffset);

private:
	GLFWwindow* window;
	std::shared_ptr<Camera> camera;
	float lastX, lastY;
	bool firstMouse;
	static CameraController* currentInstance;

	void onMouseMove(double xPosIn, double yPosIn);
	void onScroll(double xOffset, double yOffset);
};