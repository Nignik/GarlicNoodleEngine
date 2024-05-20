#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <vector>
#include <string>
#include <functional>

struct Butt
{
	std::string label;
	std::function<void()> func;
};

struct FloatSlider
{
	std::string label;
	std::function<void(float)> func;
	float value;
	float minValue;
	float maxValue;
};

class NoodleGui
{
public:
	NoodleGui(GLFWwindow* window);
	~NoodleGui();

	void RenderFrame();
	void AddButton(Butt&& newButton);

	void AddSlider(FloatSlider&& newSlider);

private:
	std::vector<Butt> buttons;
	std::vector<FloatSlider> sliders;
};