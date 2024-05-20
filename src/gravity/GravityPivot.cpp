#include "GravityPivot.h"

GravityPivot::GravityPivot(float mass, float radius, glm::vec3 position, glm::vec3 velocity, Shader shader)
	:
	CelestialBody(mass, radius, position, velocity, shader)
{
	glm::vec3 ambient(0.7f, 0.7f, 0.7f);
	glm::vec3 diffuse(0.5f, 0.5f, 0.5f);
	glm::vec3 specular(1.0f, 1.0f, 1.0f);

	light = {ambient, diffuse, specular};
}

void GravityPivot::Draw(glm::mat4& projection, glm::mat4& view, glm::vec3& cameraPosition)
{
	shader.use();

	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	shader.setFloat("brightness", brightness);

	glBindVertexArray(VAO);
	
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void GravityPivot::ChangeBrightness(float newBrightness)
{
	brightness = newBrightness;
}

Light GravityPivot::GetLightParams()
{
	return light;
}
