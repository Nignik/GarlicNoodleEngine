#pragma once

#include <iostream>
#include "CelestialBody.h"
#include "GravityPivot.h"
#include <shader_m.h>

class Satellite : public CelestialBody
{
public:
	Satellite(float mass, float rotationVelocity, float radius, int sectorCount, int stackCount, glm::vec3 position, glm::vec3 velocity, glm::vec3 color, GravityPivot& pivot, Shader shader);

	virtual void Draw(glm::mat4& projection, glm::mat4& view, glm::vec3& cameraPosition) override;

	void UpdatePosition(float deltaTime);

private:
	std::unique_ptr<GravityPivot> pivot;
};