#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, width, 0), color),
		VertexFormat(corner + glm::vec3(0, width, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 startingPoint, float length, glm::vec3 color, bool fill)
{
	//startingPoint va fi coltul de jos
	glm::vec3 point = startingPoint;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(point, color),
		VertexFormat(point + glm::vec3(length, length/2, 0), color),
		VertexFormat(point + glm::vec3(0, length, 0), color)
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2 };

	if (!fill) {
		triangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
	}

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Object2D::CreateCircle(std::string name, int radius, float posX, float posY, glm::vec3 color, bool fill) {


	std::vector<VertexFormat> vertices;

	//VertexFormat(center, glm::vec3(0, 0, 255));

	for (float x = 0.0f; x < 2 * M_PI; x += 2 * M_PI / 11) {
		vertices.push_back(VertexFormat(glm::vec3(radius * cos(x) + posX, radius * sin(x) + posY, 0), color));
	}
	//vertices.push_back(center);

	for (float x = 0.0f; x < 2 * M_PI; x += 0.2f * M_PI / 11) {
		VertexFormat(glm::vec3(radius * cos(x) + posX, radius * sin(x) + posY, 0), color);
	}


	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

	Mesh* circle = new Mesh(name);

	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		for (int i = 1; i < 11; i++) {
			indices.push_back(i);
			indices.push_back(0);
			indices.push_back(i + 1);
		}
	}
	

	circle->InitFromData(vertices, indices);
	return circle;

}

Mesh* Object2D::CreateBackground(std::string name, float length, float width)
{

	std::vector<glm::vec3> vertices
	{
		glm::vec3(-1, -1, 0.0f),	// Bottom Left
		glm::vec3(1, -1, 0.0f), // Bottom  Right
		glm::vec3(1, 1, 0.0f),	// Top Right
		glm::vec3(-1, 1, 0.0f),	// Top Left
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	std::vector<glm::vec3> normals
	{
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),

	};

	std::vector<glm::vec2> textureCoords
	{
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0)
	};

	rectangle->InitFromData(vertices, normals, textureCoords, indices);
	return rectangle;
}