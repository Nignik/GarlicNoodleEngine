#pragma once

#include "CelestialBody.h"


class GravityPivot : public CelestialBody
{
public:
	GravityPivot(float mass, float radius, glm::vec3 position, glm::vec3 velocity, Shader shader);

	void Draw(glm::mat4& projection, glm::mat4& view, glm::vec3& cameraPosition) override;
	void ChangeBrightness(float newBrightness);

	Light GetLightParams();

private:
	Light light;
	float brightness;
};