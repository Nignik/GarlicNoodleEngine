#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Vertex.h>


namespace sphere
{
	inline std::vector<Vertex> generateVertices(float radius, int stackCount, int sectorCount)
	{
		std::vector<Vertex> vertices;

		float x, y, z, xy;
		float nx, ny, nz;
		float lengthInv = 1.0f / radius;

		float PI = glm::pi<float>();
		float sectorStep = 2 * PI / sectorCount;
		float stackStep = PI / stackCount;
		float sectorAngle, stackAngle;

		for (int i = 0; i <= stackCount; ++i)
		{
			stackAngle = PI / 2 - i * stackStep;
			xy = radius * cosf(stackAngle);
			z = radius * sinf(stackAngle);

			for (int j = 0; j <= sectorCount; ++j)
			{
				sectorAngle = j * sectorStep;

				x = xy * cosf(sectorAngle);
				y = xy * sinf(sectorAngle);

				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;

				vertices.emplace_back(glm::vec3(x, y, z), glm::vec3(nx, ny, nz));
			}
		}

		return vertices;
	}

	inline std::tuple<std::vector<int>, std::vector<int>> generateIndices(int stackCount, int sectorCount)
	{
		std::vector<int> indices;
		std::vector<int> lineIndices;
		int k1, k2;
		for (int i = 0; i < stackCount; ++i)
		{
			k1 = i * (sectorCount + 1);
			k2 = k1 + sectorCount + 1;

			for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
			{
				if (i != 0)
				{
					indices.push_back(k1);
					indices.push_back(k2);
					indices.push_back(k1 + 1);
				}

				if (i != (stackCount - 1))
				{
					indices.push_back(k1 + 1);
					indices.push_back(k2);
					indices.push_back(k2 + 1);
				}

				lineIndices.push_back(k1);
				lineIndices.push_back(k2);
				if (i != 0)
				{
					lineIndices.push_back(k1);
					lineIndices.push_back(k1 + 1);
				}
			}
		}

		return { indices, lineIndices };
	}
}