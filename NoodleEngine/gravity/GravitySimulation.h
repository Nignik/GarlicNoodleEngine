#pragma once

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

#include <shader_m.h>

#include "GravityPivot.h"
#include "Satellite.h"
#include "../Line.h"
#include "Planetary.h"
#include "../Colors.h"



class GravitySimulation
{
public:
	GravitySimulation();

	void SwitchVelocityVectors();
	bool IsShowingVelocityVectors();
	void RenderFrame(float deltaTime, glm::mat4& projection, glm::mat4& view, glm::vec3& cameraPosition);

private:
	const std::string shaderRootPathRelative = "../../../../NoodleEngine/shaders/";
	const std::string shaderRootPathAbsolute = "C:/DEV/GraphicsCookbook/GameEngines/NoodleEngine/shaders/";
	Shader m_SunShader, m_PlanetShader, m_LineShader;

	std::shared_ptr<GravityPivot> m_Pivot;
	std::vector<std::unique_ptr<Satellite>> m_Satellites;
	std::vector<std::unique_ptr<Line>> m_VelocityVectors;

	bool m_ShowVelocityVectors = false;
};

inline glm::vec3 calculateGravitationalAcceleration(const Planet& primaryBody, const Planet& satellite)
{
	float gravitationalConstant = 0.0007f;

	float distance = glm::distance(primaryBody.position, satellite.position);
	glm::vec3 unitDirection = glm::normalize(primaryBody.position - satellite.position);

	glm::vec3 gravitationalAcceleration = unitDirection * gravitationalConstant * primaryBody.mass / (distance * distance);
	return gravitationalAcceleration;
}