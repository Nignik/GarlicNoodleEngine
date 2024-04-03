#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <shapes.h>
#include <ObjectsGeneration.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <camera.h>
#include <chrono>
#include <shader_m.h>

#include <iostream>
#include <map>

#include "GravityPivot.h"
#include "Satellite.h"
#include "Line.h"
#include "CameraController.h"


GLFWwindow* windowInit();
void frameBuffer_Size_Callback(GLFWwindow* window, int width, int height);

// Settings
constexpr unsigned int SCR_WIDTH = 1200;
constexpr unsigned int SCR_HEIGHT = 800;

// Paths
const std::string shaderRootPathRelative = "../../../../NoodleEngine/shaders/";
const std::string shaderRootPathAbsolute = "C:/DEV/GraphicsCookbook/GameEngines/NoodleEngine/shaders/";

// Camera settings
std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3(0.0f, 35.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

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
	CameraController cameraController(window, camera);

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

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		cameraController.processInput(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
		glm::mat4 view = camera->GetViewMatrix();
		
		for (size_t i = 0; i < planets.size(); i++)
		{
			planets[i]->Draw(projection, view);
			planets[i]->UpdatePosition(deltaTime);
		}

		for (size_t i = 0; i < velocityVectors.size(); i++)
		{
			velocityVectors[i]->Update(planets[i]->GetPosition(), planets[i]->GetPosition() + planets[i]->GetVelocity());
			velocityVectors[i]->Draw(projection, view);
		}

		sun.Draw(projection, view);

		glfwSwapBuffers(window);
		glfwPollEvents();
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
	glfwSetCursorPosCallback(window, CameraController::mouse_Callback);
	glfwSetScrollCallback(window, CameraController::scroll_Callback);

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


