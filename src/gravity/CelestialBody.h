#pragma once

#include <vector>
#include <vertex.h>
#include <glm/glm.hpp>
#include <shader_m.h>
#include <ShaderStructs.h>


class CelestialBody
{
public:
	CelestialBody(float mass, float radius, glm::vec3 position, glm::vec3 velocity, Shader shader);

	std::vector<Vertex>& GetVertices();
	std::vector<int>& GetIndices();

	virtual void Draw(glm::mat4& projection, glm::mat4& view, glm::vec3& cameraPosition);

	float GetMass() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetVelocity() const;

protected:
	GLuint VBO, VAO, EBO;
	glm::mat4 model;

	float gravitationalConstant = 0.0007f;
	float mass;

	Shader shader;

	std::vector<Vertex> vertices;
	std::vector<int> indices;
	glm::vec3 position;
	glm::vec3 velocity;
};