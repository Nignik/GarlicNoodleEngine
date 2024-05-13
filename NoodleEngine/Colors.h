#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Color
{
	constexpr glm::vec3 RED = glm::vec3(1.0f, 0.0f, 0.0f);
	constexpr glm::vec3 YELLOW = glm::vec3(0.8f, 0.8f, 0.0f);
	constexpr glm::vec3 GREEN = glm::vec3(0.0f, 0.85f, 0.0f);
	constexpr glm::vec3 CYAN = glm::vec3(0.0f, 0.85f, 0.85f);
	constexpr glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 1.0f);
	constexpr glm::vec3 PINK = glm::vec3(0.8f, 0.0f, 0.5f);
}