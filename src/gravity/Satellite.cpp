#include "Satellite.h"

Satellite::Satellite(float mass, float radius, glm::vec3 position, glm::vec3 velocity, Material&& material, std::shared_ptr<GravityPivot> pivot, Shader shader)
	:
	CelestialBody(mass, radius, position, velocity, shader),
	pivot(pivot),
	material(std::move(material))
{
}

void Satellite::Draw(glm::mat4& projection, glm::mat4& view, glm::vec3& cameraPosition)
{
	shader.use();

	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	
	shader.setVec3("material.ambient", material.ambient);
	shader.setVec3("material.diffuse", material.diffuse);
	shader.setVec3("material.specular", material.specular);
	shader.setFloat("material.shininess", material.shininess);

	Light light = pivot->GetLightParams();
	shader.setVec3("lgith.position", pivot->GetPosition());
	shader.setVec3("light.ambient", light.ambient);
	shader.setVec3("light.diffuse", light.diffuse);
	shader.setVec3("light.specular", light.specular);

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
