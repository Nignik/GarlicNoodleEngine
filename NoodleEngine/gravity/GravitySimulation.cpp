#include "GravitySimulation.h"

GravitySimulation::GravitySimulation()
	: m_SunShader(Shader((shaderRootPathRelative + "lightVertex.vs").c_str(), (shaderRootPathRelative + "lightFragment.fs").c_str())),
	m_PlanetShader(Shader((shaderRootPathRelative + "planetVertex.vs").c_str(), (shaderRootPathRelative + "planetFragment.fs").c_str())),
	m_LineShader(Shader((shaderRootPathRelative + "lineVertex.vs").c_str(), (shaderRootPathRelative + "lineFragment.fs").c_str()))
{
	const int sphereSectorCount = 40;
	const int sphereStackCount = 30;

	m_Pivot = std::make_shared<GravityPivot>(100000.0f, 0.0f, 0.5f, sphereSectorCount, sphereStackCount, glm::vec3(0.0f), glm::vec3(0.0f), Color::YELLOW, m_SunShader);

	std::vector<glm::vec3> planetColors = { Color::RED, Color::GREEN, Color::CYAN, Color::BLUE, Color::PINK };
	for (int i = 0; i < 5; i++)
	{
		auto planetPosition = glm::vec3(4.0f + i, 0.0f, -5.0f - i);
		auto planetVelocity = glm::vec3(2.5f, 0.0f, 0.0f);
		m_Satellites.push_back(std::make_unique<Satellite>(100.0f, 0.0f, 0.25f, sphereSectorCount, sphereStackCount, planetPosition, planetVelocity, planetColors[i], m_Pivot, m_PlanetShader));
	}

	for (int i = 0; i < 5; i++)
	{
		glm::vec3 start = glm::vec3(0.0f), end = m_Satellites[i]->GetVelocity();
		std::vector<float> vertices = { start.x, start.y, start.z, end.x, end.y, end.z };
		m_VelocityVectors.push_back(std::make_unique<Line>(vertices, m_Satellites[i]->GetPosition(), m_LineShader));
	}
}

void GravitySimulation::SwitchVelocityVectors()
{
	m_ShowVelocityVectors = !m_ShowVelocityVectors;
}

bool GravitySimulation::IsShowingVelocityVectors()
{
	return m_ShowVelocityVectors;
}

void GravitySimulation::RenderFrame(float deltaTime, glm::mat4& projection, glm::mat4& view, glm::vec3& cameraPosition)
{
	for (size_t i = 0; i < m_Satellites.size(); i++)
	{
		m_Satellites[i]->Draw(projection, view, cameraPosition);
		m_Satellites[i]->UpdatePosition(deltaTime);
	}

	if (m_ShowVelocityVectors)
	{
		for (size_t i = 0; i < m_VelocityVectors.size(); i++)
		{
			m_VelocityVectors[i]->Update(m_Satellites[i]->GetPosition(), m_Satellites[i]->GetPosition() + m_Satellites[i]->GetVelocity());
			m_VelocityVectors[i]->Draw(projection, view);
		}
	}

	m_Pivot->Draw(projection, view, cameraPosition);
}
