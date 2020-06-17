#include "Tema1.h"
#include <Core/GPU/Texture2D.h>
#include <random>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include <iostream>
#include <Windows.h>
#include <MMSystem.h>

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	yPos = 250;
	glm::vec3 corner = glm::vec3(0, 0, 0);
	len = 25;
	wid = 20;
	radius = 10;
	scaleX = 1;
	scaleY1 = 1;
	scaleY2 = 1;
	up = 800;
	gravity = 300;
	keyPressed = false;
	gameSpeed = 200;
	pipesGap = 300;

	const string textureLoc = "Source/Laboratoare/Tema1/";
	texture = new Texture2D();
	texture->Load2D((textureLoc + "8-bit-wallpaper.jpg").c_str(), GL_REPEAT);
	

	Mesh* rectangle1 = Object2D::CreateRectangle("rectangle1", corner, len, wid, glm::vec3(1, 0, 0), true);
	AddMeshToList(rectangle1);

	Mesh* rectangle2 = Object2D::CreateRectangle("rectangle2", corner, -40, -10, glm::vec3(0, 1, 0), true);
	AddMeshToList(rectangle2);

	Mesh* triangle1 = Object2D::CreateTriangle("triangle1", corner, wid, glm::vec3(0, 0, 1), true);
	AddMeshToList(triangle1);

	Mesh* triangle2 = Object2D::CreateTriangle("triangle2", corner, wid, glm::vec3(1, 0, 1), true);
	AddMeshToList(triangle2);

	Mesh* pipe1 = Object2D::CreateRectangle("pipe1", corner, 80, 160, glm::vec3(0, 0.9, 0), true);
	AddMeshToList(pipe1);

	Mesh* pipe2 = Object2D::CreateRectangle("pipe2", corner, 90, 20, glm::vec3(0, 0.85, 0), true);
	AddMeshToList(pipe2);

	Mesh* circle = Object2D::CreateCircle("circle", radius, 0.0f, 0.0f, glm::vec3(0, 0, 0), true);
	AddMeshToList(circle);

	glViewport(0, 0, resolution.x, resolution.y);
	resX = resolution.x;
	resY = resolution.y;
	pipeX = (float)resX;

	score = 0;
	newGame = true;

	Mesh* background = Object2D::CreateBackground("background", (float)resX, (float)resY);
	AddMeshToList(background);

	pipeX1 = (float)resX;
	pipeX2 = pipeX1 + 480;
	pipeX3 = pipeX2 + 960;
	pipeX4 = pipeX3 + 1440;

	nr = rand() % 2000;
	randomLength1 = (float)(nr % (resY - (int)pipesGap - 30));

	nr = rand() % 2000;
	randomLength2 = (float)(nr % (resY - (int)pipesGap - 30));

	nr = rand() % 2000;
	randomLength3 = (float)(nr % (resY - (int)pipesGap - 30));

	nr = rand() % 2000;
	randomLength4 = (float)(nr % (resY - (int)pipesGap - 30));

	//PlaySound(TEXT("africa-toto.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
	resX = resolution.x;
	resY = resolution.y;


}

void Tema1::Update(float deltaTimeSeconds)
{
	if (newGame)
	{

		glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
		glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
		glm::mat4 modelMatrix1 = glm::mat4(1);
		modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(0, 0, 0));
		RenderSimpleMesh(meshes["background"], shaders["Screen"], glm::mat4(1), glm::mat4(1), glm::mat4(1), texture);

		if (!keyPressed)
		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(150, yPos);
			modelMatrix *= Transform2D::Rotate(1);
			modelMatrix *= Transform2D::Translate(17, -12);
			RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(150 + len + radius, yPos + wid / 2);
			RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

			glDepthFunc(GL_ALWAYS); //render peste celelalte
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(150 + len + radius, yPos + wid / 2);
			modelMatrix *= Transform2D::Rotate((float)4.5f * 3.14159f / 8);
			modelMatrix *= Transform2D::Translate(50, 5);
			RenderMesh2D(meshes["rectangle2"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(150 + len + 2 * radius, yPos);
			modelMatrix *= Transform2D::Rotate(-1);
			modelMatrix *= Transform2D::Translate(2, -14);
			RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);
		}

		if (keyPressed)
		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(150, yPos);
			modelMatrix *= Transform2D::Rotate(-1);
			modelMatrix *= Transform2D::Translate(2, 2);
			RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(150 + len + radius, yPos + wid / 2);
			RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

			glDepthFunc(GL_ALWAYS); //render peste celelalte
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(150 + len + radius, yPos + wid / 2);
			modelMatrix *= Transform2D::Rotate((float)5 * 3.14159f / 4);
			modelMatrix *= Transform2D::Translate(50, 5);
			RenderMesh2D(meshes["rectangle2"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(150 + len + 2 * radius, yPos);
			modelMatrix *= Transform2D::Rotate(-1);
			modelMatrix *= Transform2D::Translate(-28, 2);
			RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);
		}

		//tevi
		std::default_random_engine generator((unsigned int)deltaTimeSeconds);
		std::uniform_real_distribution<double> distribution(0, 1000 * (resY - (int)pipesGap - 100));

		scaleY1 = randomLength1 / 160.0f;
		scaleY2 = resY - randomLength1 - pipesGap / 160.0f;

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX1, 0);
		modelMatrix *= Transform2D::Scale(scaleX, scaleY1);
		RenderMesh2D(meshes["pipe1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX1 - 5, randomLength1);
		modelMatrix *= Transform2D::Scale(scaleX, 1);
		RenderMesh2D(meshes["pipe2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX1, randomLength1 + pipesGap);
		modelMatrix *= Transform2D::Scale(scaleX, scaleY2);
		RenderMesh2D(meshes["pipe1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX1 - 5, randomLength1 + pipesGap - 20);
		modelMatrix *= Transform2D::Scale(scaleX, 1);
		RenderMesh2D(meshes["pipe2"], shaders["VertexColor"], modelMatrix);

		scaleY1 = randomLength2 / 160.0f;
		scaleY2 = resY - randomLength2 - pipesGap / 160.0f;

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX2, 0);
		modelMatrix *= Transform2D::Scale(scaleX, scaleY1);
		RenderMesh2D(meshes["pipe1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX2 - 5, randomLength2);
		modelMatrix *= Transform2D::Scale(scaleX, 1);
		RenderMesh2D(meshes["pipe2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX2, randomLength2 + pipesGap);
		modelMatrix *= Transform2D::Scale(scaleX, scaleY2);
		RenderMesh2D(meshes["pipe1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX2 - 5, randomLength2 + pipesGap - 20);
		modelMatrix *= Transform2D::Scale(scaleX, 1);
		RenderMesh2D(meshes["pipe2"], shaders["VertexColor"], modelMatrix);

		scaleY1 = randomLength3 / 160.0f;
		scaleY2 = resY - randomLength3 - pipesGap / 160.0f;

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX3, 0);
		modelMatrix *= Transform2D::Scale(scaleX, scaleY1);
		RenderMesh2D(meshes["pipe1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX3 - 5, randomLength3);
		modelMatrix *= Transform2D::Scale(scaleX, 1);
		RenderMesh2D(meshes["pipe2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX3, randomLength3 + pipesGap);
		modelMatrix *= Transform2D::Scale(scaleX, scaleY2);
		RenderMesh2D(meshes["pipe1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX3 - 5, randomLength3 + pipesGap - 20);
		modelMatrix *= Transform2D::Scale(scaleX, 1);
		RenderMesh2D(meshes["pipe2"], shaders["VertexColor"], modelMatrix);

		scaleY1 = randomLength4 / 160.0f;
		scaleY2 = resY - randomLength4 - pipesGap / 160.0f;

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX4, 0);
		modelMatrix *= Transform2D::Scale(scaleX, scaleY1);
		RenderMesh2D(meshes["pipe1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX4 - 5, randomLength4);
		modelMatrix *= Transform2D::Scale(scaleX, 1);
		RenderMesh2D(meshes["pipe2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX4, randomLength4 + pipesGap);
		modelMatrix *= Transform2D::Scale(scaleX, scaleY2);
		RenderMesh2D(meshes["pipe1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(pipeX4 - 5, randomLength4 + pipesGap - 20);
		modelMatrix *= Transform2D::Scale(scaleX, 1);
		RenderMesh2D(meshes["pipe2"], shaders["VertexColor"], modelMatrix);


		pipeX -= deltaTimeSeconds * gameSpeed;
		pipeX1 -= deltaTimeSeconds * gameSpeed;
		pipeX2 -= deltaTimeSeconds * gameSpeed;
		pipeX3 -= deltaTimeSeconds * gameSpeed;
		pipeX4 -= deltaTimeSeconds * gameSpeed;

		//cand dispar din cadru, fac alte tevi
		if (pipeX1 <= -80)
		{
			pipeX1 += pipeX4 + 480;
			nr = rand() % 2000;
			randomLength1 = (float)(nr % (resY - (int)pipesGap - 30));
			score += 1;
			printf("Score: %d\n", score);

		}

		if (pipeX2 <= -80)
		{
			pipeX2 += pipeX1 + 480;
			nr = rand() % 2000;
			randomLength2 = (float)(nr % (resY - (int)pipesGap - 30));
			score += 1;
			printf("Score: %d\n", score);
		}

		if (pipeX3 <= -80)
		{
			pipeX3 += pipeX2 + 480;
			nr = rand() % 2000;
			randomLength3 = (float)(nr % (resY - (int)pipesGap - 30));
			score += 1;
			printf("Score: %d\n", score);

		}

		if (pipeX4 <= -80)
		{
			pipeX4 += pipeX3 + 480;
			nr = rand() % 2000;
			randomLength4 = (float)(nr % (resY - (int)pipesGap - 30));
			score += 1;
			printf("Score: %d\n", score);
		}

		//maresc dificultatea
		if (score == 10)
		{
			pipesGap = 250;
		}

		if (score == 20)
		{
			pipesGap = 220;
		}

		if (score == 30)
		{
			gameSpeed = 300;
			pipesGap = 250;
		}
		if (score == 40)
		{
			gameSpeed = 400;
			pipesGap = 220;
		}
		if (score == 50)
		{
			gameSpeed = 500;
			pipesGap = 220;
		}
		if (score == 60)
		{
			gameSpeed = 600;
			pipesGap = 200;
		}
		if (score == 70)
		{
			gameSpeed = 700;
			pipesGap = 200;
		}

		// coliziunile
		if (((yPos <= randomLength1) && (pipeX1 <= 150) && (pipeX1 + 80 >= 150)) ||
			((yPos >= randomLength1 + pipesGap - 20) && (pipeX1 <= 150) && (pipeX1 + 80 >= 150) ||
			(pipeX1 <= 150 + len + radius && pipeX1 + 80 >= 190 && randomLength1 >= yPos - 40) ||
			(pipeX1 <= 150 + len + radius && pipeX1 + 80 >= 190 && randomLength1 + pipesGap - 20 <= yPos + wid)) ||
			yPos <= 0)
		{

			newGame = false;
			printf("DEAD\n");
			//PlaySound(TEXT("classic_hurt.wav"), NULL, SND_FILENAME | SND_ASYNC);

		}

		if (((yPos <= randomLength2) && (pipeX2 <= 150) && (pipeX2 + 80 >= 150)) ||
			((yPos >= randomLength2 + pipesGap - 20) && (pipeX2 <= 150) && (pipeX2 + 80 >= 150) ||
			(pipeX2 <= 150 + len + radius && pipeX2 + 80 >= 190 && randomLength2 >= yPos - 40) ||
				(pipeX2 <= 150 + len + radius && pipeX2 + 80 >= 190 && randomLength2 + pipesGap - 20 <= yPos + wid)) ||
			yPos <= 0)
		{

			newGame = false;
			printf("DEAD\n");
			//PlaySound(TEXT("classic_hurt.wav"), NULL, SND_FILENAME | SND_ASYNC);

		}

		if (((yPos <= randomLength3) && (pipeX3 <= 150) && (pipeX3 + 80 >= 150)) ||
			((yPos >= randomLength3 + pipesGap - 20) && (pipeX3 <= 150) && (pipeX3 + 80 >= 150) ||
			(pipeX3 <= 150 + len + radius && pipeX3 + 80 >= 190 && randomLength3 >= yPos - 40) ||
				(pipeX3 <= 150 + len + radius && pipeX3 + 80 >= 190 && randomLength3 + pipesGap - 20 <= yPos + wid)) ||
			yPos <= 0)
		{

			newGame = false;
			printf("DEAD\n");
			//PlaySound(TEXT("classic_hurt.wav"), NULL, SND_FILENAME | SND_ASYNC);

		}

		if (((yPos <= randomLength4) && (pipeX4 <= 150) && (pipeX4 + 80 >= 150)) ||
			((yPos >= randomLength4 + pipesGap - 20) && (pipeX4 <= 150) && (pipeX4 + 80 >= 150) ||
			(pipeX4 <= 150 + len + radius && pipeX4 + 80 >= 190 && randomLength4 >= yPos - 40) ||
				(pipeX4 <= 150 + len + radius && pipeX4 + 80 >= 190 && randomLength4 + pipesGap - 20 <= yPos + wid)) ||
			yPos <= 0)
		{

			newGame = false;
			printf("DEAD\n");
			//PlaySound(TEXT("classic_hurt.wav"), NULL, SND_FILENAME | SND_ASYNC);

		}
	}
}

void Tema1::FrameEnd()
{
	
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	//VK_SPACE	32	[Space] key

	if (keyPressed && yPos <= resY - wid)
	{
		yPos += deltaTime * up;
		keyPressed = true;
	}

	if (!keyPressed && yPos >= 0)
	{
		yPos -= deltaTime * gravity;
	}
}

void Tema1::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE)
	{
		keyPressed = true;
	}
	if (key == GLFW_KEY_N)
	{
		newGame = true;
		printf("NEW GAME\n");
		Tema1::Init();
	}

}

void Tema1::OnKeyRelease(int key, int mods)
{
	if (key == GLFW_KEY_SPACE)
	{
		keyPressed = false;
	}

}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{

}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

void Tema1::RenderSimpleMesh(Mesh *mesh, Shader* shader, const glm::mat4 & modelMatrix, const glm::mat4 & viewMatrix,
							const glm::mat4 & prjMatrix, Texture2D* texture1)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(prjMatrix));

	if (texture1)
	{
		int i = 0;
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "u_texture_0"), i);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}
