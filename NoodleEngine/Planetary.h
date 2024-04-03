#pragma once

#include <glm/glm.hpp>

struct Planet
{
	float mass;
	float rotationVelocity;

	glm::vec3 velocity;
	glm::vec3 position;
};