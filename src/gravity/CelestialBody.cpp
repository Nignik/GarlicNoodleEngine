#include "CelestialBody.h"
#include <shapes.h>
#include <ObjectsGeneration.h>

CelestialBody::CelestialBody(float mass, float radius, glm::vec3 position, glm::vec3 velocity, Shader shader)
	:
	mass(mass),
	position(position),
	velocity(velocity),
	shader(shader)
{
	vertices = sphere::generateVertices(radius);
	indices = std::get<0>(sphere::generateIndices());

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

glm::vec3 CelestialBody::GetPosition() const
{
	return position;
}

glm::vec3 CelestialBody::GetVelocity() const
{
	return velocity;
}