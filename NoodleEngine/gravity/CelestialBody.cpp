#include "CelestialBody.h"
#include <shapes.h>
#include <ObjectsGeneration.h>

CelestialBody::CelestialBody(float mass, float rotationVelocity, float radius, int sectorCount, int stackCount, glm::vec3 position, glm::vec3 velocity, glm::vec3 color, Shader shader)
	:
	mass(mass),
	rotationVelocity(rotationVelocity),
	position(position),
	velocity(velocity),
	color(color),
	shader(shader)
{
	vertices = sphere::generateVertices(radius, stackCount, sectorCount);
	indices = std::get<0>(sphere::generateIndices(stackCount, sectorCount));

	auto [newVBO, newVAO, newEBO] = generateObjects(vertices, indices);
	VBO = newVBO;
	VAO = newVAO;
	EBO = newEBO;

	glm::mat4 newModel = glm::mat4(1.0f);
	model = glm::translate(newModel, position);
}

std::vector<Vertex>& CelestialBody::GetVertices()
{
	return vertices;
}

std::vector<int>& CelestialBody::GetIndices()
{
	return indices;
}

void CelestialBody::Draw(glm::mat4& projection, glm::mat4& view, glm::vec3& cameraPosition)
{
}

float CelestialBody::GetMass() const
{
	return mass;
}

float CelestialBody::GetRotationVelocity() const
{
	return rotationVelocity;
}

glm::vec3 CelestialBody::GetPosition() const
{
	return position;
}

glm::vec3 CelestialBody::GetVelocity() const
{
	return velocity;
}

glm::vec3 CelestialBody::GetColor() const
{
	return color;
}
