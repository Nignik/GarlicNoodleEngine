#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Planetary.h"

inline glm::vec3 calculateGravitationalAcceleration(const Planet& primaryBody, const Planet& satellite)
{
	float gravitationalConstant = 0.0007f;

	float distance = glm::distance(primaryBody.position, satellite.position);
	glm::vec3 unitDirection = glm::normalize(primaryBody.position - satellite.position);

	glm::vec3 gravitationalAcceleration = unitDirection * gravitationalConstant * primaryBody.mass / (distance * distance);
	return gravitationalAcceleration;
}