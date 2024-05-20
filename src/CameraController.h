#pragma once

#include <iostream>

#include "Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class CameraController
{
public:
	CameraController(std::shared_ptr<Camera> camera);
	void processInput(GLFWwindow* window, float deltaTime);
	void onMouseMove(double xPosIn, double yPosIn);
	void onScroll(double xOffset, double yOffset);

	void Stop();
	void Start();

private:
	std::shared_ptr<Camera> m_Camera;
	float lastX, lastY;
	bool firstMouse;
	bool m_CanMove;
};