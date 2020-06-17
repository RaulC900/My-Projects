#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill);
	Mesh* CreateTriangle(std::string name, glm::vec3 startingPoint, float length, glm::vec3 color, bool fill);
	Mesh* CreateCircle(std::string name, int radius, float posX, float posY, glm::vec3 color, bool fill);
	Mesh* CreateBackground(std::string name, float length, float width);
}

