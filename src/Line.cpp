#include "Line.h"

Line::Line(std::vector<float>& vertices, glm::vec3 position, Shader shader)
	:
	shader(shader)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	model = glm::mat4(1.0f);
}

void Line::Update(glm::vec3 start, glm::vec3 end)
{
	std::vector<float> newVertices = {
		start.x, start.y, start.z,
		end.x, end.y, end.z
	};

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, newVertices.size() * sizeof(float), newVertices.data(), GL_STATIC_DRAW);
}

void Line::Draw(glm::mat4& projection, glm::mat4& view)
{
	shader.use();
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 2);
}
