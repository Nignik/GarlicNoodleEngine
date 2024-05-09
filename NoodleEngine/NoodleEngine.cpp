#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <shapes.h>
#include <ObjectsGeneration.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <chrono>
#include <shader_m.h>

#include <iostream>
#include <map>

#include "Camera.h"
#include "InputHandler.h"
#include "gravity/GravityPivot.h"
#include "gravity/Satellite.h"
#include "Line.h"
#include "CameraController.h"


GLFWwindow* windowInit();
void imguiInit(GLFWwindow* window);
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
	const int sphereSectorCount = 40;
	const int sphereStackCount = 30;

	std::map<std::string, glm::vec3> colors = {
		{"red", glm::vec3(1.0f, 0.0f, 0.0f)},
		{"yellow", glm::vec3(0.8f, 0.8f, 0.0f)},
		{"green", glm::vec3(0.0f, 0.85f, 0.0f)},
		{"cyan", glm::vec3(0.0f, 0.85f, 0.85f)},
		{"blue", glm::vec3(0.0f, 0.0f, 1.0f)},
		{"pink", glm::vec3(0.8f, 0.0f, 0.5f)}
	};
	std::vector<std::string> planetColors = { "red", "green", "cyan", "blue", "pink" };

	GLFWwindow* window = windowInit();
	imguiInit(window);

	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	std::unique_ptr<CameraController> cameraController = std::make_unique<CameraController>(camera);
	glfwSetWindowUserPointer(window, cameraController.get());

	glEnable(GL_DEPTH_TEST);

	Shader sunShader((shaderRootPathRelative + "lightVertex.vs").c_str(), (shaderRootPathRelative + "lightFragment.fs").c_str());
	Shader planetShader((shaderRootPathRelative + "planetVertex.vs").c_str(), (shaderRootPathRelative + "planetFragment.fs").c_str());
	Shader lineShader((shaderRootPathRelative + "lineVertex.vs").c_str(), (shaderRootPathRelative + "lineFragment.fs").c_str());

	GravityPivot sun(100000.0f, 0.0f, 0.5f, sphereSectorCount, sphereStackCount, glm::vec3(0.0f), glm::vec3(0.0f), colors["yellow"], sunShader);

	std::vector<std::unique_ptr<Satellite>> planets;
	for (int i = 0; i < 5; i++)
	{
		auto planetPosition = glm::vec3(4.0f + i, 0.0f, -5.0f - i);
		auto planetVelocity = glm::vec3(2.5f, 0.0f, 0.0f);
		planets.push_back(std::make_unique<Satellite>(100.0f, 0.0f, 0.25f, sphereSectorCount, sphereStackCount, planetPosition, planetVelocity, colors[planetColors[i]], sun, planetShader));
	}

	std::vector<std::unique_ptr<Line>> velocityVectors;
	for (int i = 0; i < 5; i++)
	{
		glm::vec3 start = glm::vec3(0.0f), end = planets[i]->GetVelocity();
		std::vector<float> vertices = { start.x, start.y, start.z, end.x, end.y, end.z };
		velocityVectors.push_back(std::make_unique<Line>(vertices, planets[i]->GetPosition(), lineShader));
	}

	bool showVelocityVectors = true;

	while (!glfwWindowShouldClose(window))
	{	
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();
		ImGui::Begin("settings");
		
		if (ImGui::Button("show velocity vectors"))
		{
			showVelocityVectors = !showVelocityVectors;
			std::cout << "Button was clicked!" << std::endl;
		}

		ImGui::SameLine();
		ImGui::Text(showVelocityVectors ? "True" : "False");

		ImGui::End();
		ImGui::Render();

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		cameraController->processInput(window, deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
		glm::mat4 view = camera->GetViewMatrix();
		
		for (size_t i = 0; i < planets.size(); i++)
		{
			planets[i]->Draw(projection, view, camera->Position);
			planets[i]->UpdatePosition(deltaTime);
		}

		if (showVelocityVectors)
		{
			for (size_t i = 0; i < velocityVectors.size(); i++)
			{
				velocityVectors[i]->Update(planets[i]->GetPosition(), planets[i]->GetPosition() + planets[i]->GetVelocity());
				velocityVectors[i]->Draw(projection, view);
			}
		}

		sun.Draw(projection, view, camera->Position);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

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

void imguiInit(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, false);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void frameBuffer_Size_Callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}


