#pragma once

#include "CelestialBody.h"

class GravityPivot : public CelestialBody
{
public:
	GravityPivot(float mass, float rotationVelocity, float radius, int sectorCount, int stackCount, glm::vec3 position, glm::vec3 velocity, glm::vec3 color, Shader shader);

	virtual void Draw(glm::mat4& projection, glm::mat4& view, glm::vec3& cameraPosition) override;

};