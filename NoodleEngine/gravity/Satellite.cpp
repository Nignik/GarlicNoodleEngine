#include "Satellite.h"

Satellite::Satellite(float mass, float rotationVelocity, float radius, int sectorCount, int stackCount, glm::vec3 position, glm::vec3 velocity, glm::vec3 color, GravityPivot& pivot, Shader shader)
	:
	CelestialBody(mass, rotationVelocity, radius, sectorCount, stackCount, position, velocity, color, shader),
	pivot(std::make_unique<GravityPivot>(pivot))
{
}

void Satellite::Draw(glm::mat4& projection, glm::mat4& view, glm::vec3& cameraPosition)
{
	shader.use();

	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	
	shader.setVec3("lightPos", pivot->GetPosition());
	shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	shader.setVec3("objectColor", color);
	shader.setVec3("viewPos", cameraPosition);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Satellite::UpdatePosition(const float deltaTime)
{
	const float distance = glm::distance(position, pivot->GetPosition());
	const glm::vec3 unitDirection = glm::normalize(pivot->GetPosition() - position);

	const glm::vec3 gravitationalAcceleration = unitDirection * gravitationalConstant * pivot->GetMass() / (distance * distance);
	velocity += gravitationalAcceleration * deltaTime;
	position += velocity * deltaTime;

	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
}
