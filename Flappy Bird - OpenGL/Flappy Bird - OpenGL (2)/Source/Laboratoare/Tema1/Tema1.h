#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <queue> 

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::mat4 & viewMatrix, const glm::mat4 & prjMatrix, Texture2D* texture1);

	protected:
		glm::mat3 modelMatrix;
		glm::mat4 modelMatrix1;
		float scaleX, scaleY1, scaleY2; //2 scaleY pt 2 tevi
		float yPos; //pozitia pe y a pasarii
		float up, gravity;
		bool keyPressed;
		float len, wid;
		int radius;
		int resX, resY;
		float pipeX;
		float pipesGap;
		float randomLength1, randomLength2, randomLength3, randomLength4;
		float gameSpeed;
		bool newGame;
		int score;
		int nr;
		const unsigned char* img;
		Texture2D* texture;
		Texture2D* texture1;
		bool spacePressed;
		float pipeX1, pipeX2, pipeX3, pipeX4;
};
