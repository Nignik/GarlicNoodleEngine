#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <map>

#include "Camera.h"
#include "InputHandler.h"
#include "Line.h"
#include "CameraController.h"
#include "gravity/GravitySimulation.h"
#include "NoodleGui.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


GLFWwindow* windowInit();
void frameBuffer_Size_Callback(GLFWwindow* window, int width, int height);

// Settings
constexpr unsigned int SCR_WIDTH = 1200;
constexpr unsigned int SCR_HEIGHT = 800;

// Paths
const std::string shaderRootPathRelative = "../../../../NoodleEngine/shaders/";
const std::string shaderRootPathAbsolute = "C:/DEV/GraphicsCookbook/GameEngines/NoodleEngine/shaders/";

// Time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	GLFWwindow* window = windowInit();
	NoodleGui gui(window);

	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	std::unique_ptr<CameraController> cameraController = std::make_unique<CameraController>(camera);
	glfwSetWindowUserPointer(window, cameraController.get());

	glEnable(GL_DEPTH_TEST);

	GravitySimulation simulation;
	
	float brihtnessValue = 0.5;
	gui.AddButton(Butt("Enable/Disable velocity vectors", [&] {simulation.SwitchVelocityVectors(); }));
	gui.AddSlider(FloatSlider(
		"Change sun brightness",
		[&](float newValue) {simulation.ChangeSunBrightness(newValue); },
		brihtnessValue,
		0.0,
		1.0
	));

	while (!glfwWindowShouldClose(window))
	{	
		glfwPollEvents();

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		cameraController->processInput(window, deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
		glm::mat4 view = camera->GetViewMatrix();

		simulation.RenderFrame(deltaTime, projection, view, camera->Position);

		gui.RenderFrame();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

GLFWwindow* windowInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBuffer_Size_Callback);
	glfwSetCursorPosCallback(window, mouse_Callback);
	glfwSetScrollCallback(window, scroll_Callback);
	glfwSetKeyCallback(window, key_Callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	return window;
}

void frameBuffer_Size_Callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}


