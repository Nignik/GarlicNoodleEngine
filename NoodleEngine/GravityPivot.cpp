#include "GravityPivot.h"

GravityPivot::GravityPivot(float mass, float rotationVelocity, float radius, int sectorCount, int stackCount, glm::vec3 position, glm::vec3 velocity, glm::vec3 color, Shader shader)
	:
	CelestialBody(mass, rotationVelocity, radius, sectorCount, stackCount, position, velocity, color, shader)
{
}

void GravityPivot::Draw(glm::mat4& projection, glm::mat4& view)
{
	shader.use();

	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	glBindVertexArray(VAO);
	
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
