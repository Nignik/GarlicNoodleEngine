#pragma once

#include <iostream>
#include "CelestialBody.h"
#include "GravityPivot.h"
#include <shader_m.h>
#include <memory>

class Satellite : public CelestialBody
{
public:
	Satellite(float mass, float radius, glm::vec3 position, glm::vec3 velocity, Material&& material, std::shared_ptr<GravityPivot> pivot, Shader shader);

	void Draw(glm::mat4& projection, glm::mat4& view, glm::vec3& cameraPosition) override;

	void UpdatePosition(float deltaTime);

private:
	std::shared_ptr<GravityPivot> pivot;
	Material material;
};