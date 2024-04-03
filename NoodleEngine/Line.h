#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>
#include <vector>

class Line
{
public:
	Line(std::vector<float>& vertices, glm::vec3 position, Shader shader);

	void Update(glm::vec3 position, glm::vec3 newDirection);

	void Draw(glm::mat4& projection, glm::mat4& view);

private:
	GLuint VBO, VAO;

	Shader shader;
	glm::mat4 model;
};