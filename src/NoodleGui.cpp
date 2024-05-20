#include "NoodleGui.h"
#include <iostream>

NoodleGui::NoodleGui(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

NoodleGui::~NoodleGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void NoodleGui::RenderFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	for (auto& button : buttons)
	{
		if (ImGui::Button((button.label).c_str()))
		{
			button.func();
			std::cout << "Button was clicked!" << std::endl;
		}
	}

	for (auto& slider : sliders)
	{
		if (ImGui::SliderFloat((slider.label).c_str(), &slider.value, slider.minValue, slider.maxValue))
		{
			slider.func(slider.value);
			std::cout << "Slider slided!" << std::endl;
		}
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void NoodleGui::AddButton(Butt&& newButton)
{
	buttons.push_back(std::move(newButton));
}

void NoodleGui::AddSlider(FloatSlider&& newSlider)
{
	sliders.push_back(newSlider);
	FloatSlider& currentSlider = sliders.back();
	currentSlider.func(currentSlider.value);
}



