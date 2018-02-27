#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>

#include "../Laborator5/LabCamera.h"

class Laborator6 : public SimpleScene
{
	public:
		Laborator6();
		~Laborator6();

		void Init() override;

		Mesh * CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, glm::vec3 colorFigure);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

protected:
	Laborator::Camera *camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget, forward, backward, rotateLeft, rotateRight;
	float fov;
	float left, right, bot, top;
	float 	xTrunk ,zTrunk ,xPar ,zPar ,xLBWheel ,zLBWheel ,xRBWheel ,zRBWheel ,xRFWheel,zRFWheel ,xLFWheel,zLFWheel, radians,xCenterWheel, zCenterWheel;
	float deplasament, speed, angle, speedRotating, centerX, centerZ;
	GLenum polygonMode;
};
