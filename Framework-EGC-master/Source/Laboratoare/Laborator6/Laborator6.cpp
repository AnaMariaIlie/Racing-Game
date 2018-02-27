#include "Laborator6.h"
#include "../Laborator5/Laborator5.h"
#include "../Laborator5/LabCamera.h"
#include "../Laborator4/Transform3D.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator6::Laborator6()
{
}

Laborator6::~Laborator6()
{
}

void Laborator6::Init()
{
	renderCameraTarget = false;
	fov = 50;
	right = 10.f;
	deplasament = 2.5f;
	forward = false;
	backward = false;
	speed = 1;
	radians = 0.0f;
	xTrunk = 0.0f;
	zTrunk = 0.0f;
	xPar = 0.0f;
	zPar = 0.0f;
	centerX = xPar;
	centerZ = zPar;
	//roata stanga spate
	xLBWheel = -0.9f;
	zLBWheel = -0.6f;
	//roata dreapta spate
	xRBWheel = -0.9f;
	zRBWheel = 0.6f;
	//roata dreapta fata
	xRFWheel = 0.9f;
	zRFWheel = 0.6f;
	//roata stanga fata
	xLFWheel = 0.9f;
	zLFWheel = -0.6f;
	angle = 0.0f;
	rotateRight = false;
	rotateLeft = false;
	camera = new Laborator::Camera();
	polygonMode = GL_FILL;
	camera->Set(glm::vec3(0, 2, 7.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("trunk");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "trunk.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("par");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "par.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("cylinder");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "cylinder.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("square");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "square.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("parStreet");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "parStreet.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("1");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives/Traffic Cone/Models and Textures", "1.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	
	{
		Mesh* mesh = new Mesh("lowpolytree");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "lowpolytree.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	//dreptunghi
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(0, 2.93, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(6.4, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(6.4, 2.93, 0), glm::vec3(1, 0, 0)),
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,
			1, 2, 3,
		};
		Mesh *dreptunghi = CreateMesh("dreptunghi", vertices, indices);
	}

	//dreptunghi
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(0, 2.93, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(7.7, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(7.7 , 2.93, 0), glm::vec3(1, 0, 0)),
		};
		vector<unsigned short> indices =
		{
			0, 1, 2,
			1, 2, 3,
		};
		Mesh *dreptunghi1 = CreateMesh("dreptunghi1", vertices, indices);
	}

	//roata
	{
		glm::vec3 color = glm::vec3(1.000, 0.412, 0.706);
		float radius = 2.0f;
		float z = sqrt((radius*radius) / 2);
		glm::vec3 corner = glm::vec3(0, 0, 0);
		float latime = 1.5f;
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color + glm::vec3(0,0,1)),
			VertexFormat(corner + glm::vec3(z,-(radius - z),0),color),
			VertexFormat(corner + glm::vec3(2 * z, 0, 0),color),
			VertexFormat(corner + glm::vec3(radius + z,z,0),color),
			VertexFormat(corner + glm::vec3(2 * z, 2 * z, 0),color),
			VertexFormat(corner + glm::vec3(z, radius + z, 0),color),
			VertexFormat(corner + glm::vec3(0, 2 * z, 0),color),
			VertexFormat(corner + glm::vec3(-(radius - z), z, 0),color),
			VertexFormat(corner + glm::vec3(z, z, 0),color),//centrul

			VertexFormat(corner + glm::vec3(0,0,-latime), color),
			VertexFormat(corner + glm::vec3(z,-(radius - z),-latime),color),
			VertexFormat(corner + glm::vec3(2 * z, 0, -latime),color),
			VertexFormat(corner + glm::vec3(radius + z,z,-latime),color),
			VertexFormat(corner + glm::vec3(2 * z, 2 * z, -latime),color),
			VertexFormat(corner + glm::vec3(z, radius + z, -latime),color),
			VertexFormat(corner + glm::vec3(0, 2 * z, -latime),color),
			VertexFormat(corner + glm::vec3(-(radius - z), z, -latime),color),
			VertexFormat(corner + glm::vec3(z, z, -latime),color)//centrul

		};
		vector<unsigned short> indices =
		{
			0,1,8,
			1,2,8,
			2,3,8,
			3,4,8,
			4,5,8,
			5,6,8,
			6,7,8,
			7,0,8,


			9,10,17,
			10,11,17,
			11,12,17,
			12,13,17,
			13,14,17,
			14,15,17,
			15,16,17,
			16,9,17,

			0,1,9,
			9,1,10,
			1,2,10,
			10,2,11,
			2,3,11,
			11,3,12,
			3,4,12,
			12,4,13,
			4,5,13,
			13,5,14,
			5,6,14,
			14,6,15,
			6,7,15,
			15,7,16,

		};
		Mesh *wheel = CreateMesh("wheel", vertices, indices);
	}
	projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f);

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderLab6");
		shader->AddShader("Source/Laboratoare/Laborator6/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator6/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

Mesh* Laborator6::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}


void Laborator6::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator6::Update(float deltaTimeSeconds)
{
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
	if (forward) {

		xTrunk += cos(RADIANS(angle))*deltaTimeSeconds*speed;
		zTrunk -= sin(RADIANS(angle))*deltaTimeSeconds*speed;
		xPar += cos(RADIANS(angle))*deltaTimeSeconds*speed;
		zPar -= sin(RADIANS(angle))*deltaTimeSeconds*speed;
		radians -= deltaTimeSeconds*speed;
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(22.0f, 0.0f, 0.0f);
		modelMatrix *= Transform3D::Scale(0.4f,0.4f,0.4f);
		RenderMesh(meshes["1"], shaders["Color"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-24.0f, 0.0f, 0.0f);
		modelMatrix *= Transform3D::Scale(0.4f, 0.4f, 0.4f);
		RenderMesh(meshes["1"], shaders["Color"], modelMatrix);
	}
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-24.0f, 0.0f, -24.0f);
		modelMatrix *= Transform3D::RotateOY(RADIANS(90.0f));
		modelMatrix *= Transform3D::Scale(0.8f, 0.8f, 0.8f);
		RenderSimpleMesh(meshes["lowpolytree"], shaders["ShaderLab6"], modelMatrix, glm::vec3(0.000, 0.392, 0.000));
	}
	
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-11.0f, 0.0f, 22.0f);
		modelMatrix *= Transform3D::RotateOY(RADIANS(90.0f));
		modelMatrix *= Transform3D::Scale(0.8f, 0.8f, 0.8f);
		RenderSimpleMesh(meshes["lowpolytree"], shaders["ShaderLab6"], modelMatrix, glm::vec3(0.000, 0.392, 0.000));
	}
	/*********masina**********/
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(xTrunk, 1.15f, zTrunk);
		modelMatrix *= Transform3D::RotateOY(RADIANS(angle));
		modelMatrix *= Transform3D::Scale(1.0f, 1.0f, 1.0f);
		RenderMesh(meshes["trunk"], shaders["VertexNormal"], modelMatrix);

	}
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(xPar, 1.15f, zPar);
		modelMatrix *= Transform3D::RotateOY(RADIANS(angle));
		modelMatrix *= Transform3D::Scale(1.0f, 1.0f, 1.0f);
		RenderMesh(meshes["par"], shaders["VertexNormal"], modelMatrix);
	}


	//dreapta-spate
	{

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(xPar, 0.35, zPar);
		modelMatrix *= Transform3D::RotateOY(RADIANS(angle));
		modelMatrix *= Transform3D::Translate(xRBWheel, 0.0, zRBWheel);
		modelMatrix *= Transform3D::RotateOZ(RADIANS(radians+5));
		modelMatrix *= Transform3D::Scale(0.55f, 0.55f, 0.55f);
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}



	//dreapta-fata
	{

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(xPar, 0.35, zPar);
		modelMatrix *= Transform3D::RotateOY(RADIANS(angle));
		modelMatrix *= Transform3D::Translate(xRFWheel, 0.0, zRFWheel);
		modelMatrix *= Transform3D::RotateOZ(RADIANS(radians + 5));
		modelMatrix *= Transform3D::Scale(0.55f, 0.55f, 0.55f);
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}
	//stanga-spate
	{	
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(xPar, 0.35, zPar);
		modelMatrix *= Transform3D::RotateOY(RADIANS(angle));
		modelMatrix *= Transform3D::Translate(xLBWheel, 0.0, zLBWheel);
		modelMatrix *= Transform3D::RotateOZ(RADIANS(radians + 5));
		modelMatrix *= Transform3D::Scale(0.55f, 0.55f, 0.55f);
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}

	//stanga-fata
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(xPar, 0.35, zPar);
		modelMatrix *= Transform3D::RotateOY(RADIANS(angle));
		modelMatrix *= Transform3D::Translate(xLFWheel, 0.0, zLFWheel);
		modelMatrix *= Transform3D::RotateOZ(RADIANS(radians + 5));
		modelMatrix *= Transform3D::Scale(0.55f, 0.55f, 0.55f);
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}
	/*********masina**********/


	//cerul
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = modelMatrix *= Transform3D::Scale(80.0f, 80.0f, 80.0f);
		glm::vec3 colorSphere = glm::vec3(0.000f, 1.000f, 1.000f);
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab6"], modelMatrix, colorSphere);
	}

	//pamantul
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		glm::vec3 colorGround = glm::vec3(0.196f, 0.804f, 0.196f);
		RenderSimpleMesh(meshes["square"], shaders["ShaderLab6"], modelMatrix, colorGround);
	}

	//borduri sosea
	deplasament = -16.1;
	for (int i = 0; i < 14; i++) {
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(deplasament, 0.3f, 3.2f));
			glm::vec3 colorBorders = glm::vec3(0.863, 0.863, 0.863);
			RenderSimpleMesh(meshes["parStreet"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(deplasament, 0.3f, -3.2f));
			glm::vec3 colorBorders = glm::vec3(0.863, 0.863, 0.863);
			RenderSimpleMesh(meshes["parStreet"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(deplasament, 0.3f, 18.6f));
			glm::vec3 colorBorders = glm::vec3(0.863, 0.863, 0.863);
			RenderSimpleMesh(meshes["parStreet"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(deplasament, 0.3f, -18.6f));
			glm::vec3 colorBorders = glm::vec3(0.863, 0.863, 0.863);
			RenderSimpleMesh(meshes["parStreet"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}

		deplasament += 2.5f;
	}
	//afara jos
	deplasament = -25.0f;
	for (int i = 0; i < 20; i++) {
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(deplasament, 0.3f, 25.0f));
			glm::vec3 colorBorders = glm::vec3(0.863, 0.863, 0.863);
			RenderSimpleMesh(meshes["parStreet"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(deplasament, 0.3f, -25.0f));
			glm::vec3 colorBorders = glm::vec3(0.863, 0.863, 0.863);
			RenderSimpleMesh(meshes["parStreet"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}


		deplasament += 2.5f;
	}


	deplasament = 24.0f;
	for (int i = 0; i < 20; i++) {
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(24.0f, 0.3f, deplasament));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
			glm::vec3 colorBorders = glm::vec3(0.863, 0.863, 0.863);
			RenderSimpleMesh(meshes["parStreet"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-26.0f, 0.3f, deplasament));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
			glm::vec3 colorBorders = glm::vec3(0.863, 0.863, 0.863);
			RenderSimpleMesh(meshes["parStreet"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}


		deplasament -= 2.5f;
	}

	deplasament = 17.3f;
	for (int i = 0; i < 6; i++) {
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(18.0f, 0.3f, deplasament));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
			glm::vec3 colorBorders = glm::vec3(0.863, 0.863, 0.863);
			RenderSimpleMesh(meshes["parStreet"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-18.0f, 0.3f, deplasament));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
			glm::vec3 colorBorders = glm::vec3(0.863, 0.863, 0.863);
			RenderSimpleMesh(meshes["parStreet"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}


		deplasament -= 2.5f;
	}

	deplasament = -4.6f;
	for (int i = 0; i < 6; i++) {
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(18.0f, 0.3f, deplasament));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
			glm::vec3 colorBorders = glm::vec3(0.863, 0.863, 0.863);
			RenderSimpleMesh(meshes["parStreet"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-18.0f, 0.3f, deplasament));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
			glm::vec3 colorBorders = glm::vec3(0.863, 0.863, 0.863);
			RenderSimpleMesh(meshes["parStreet"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}


		deplasament -= 2.5f;
	}
	
	//sosea
	
	deplasament = -23.0f;
	for (int i = 0; i < 17; i++) {
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(deplasament, 0.05f, -3.2f));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 0, 1));
			glm::vec3 colorBorders = glm::vec3(0.412, 0.412, 0.412);
			RenderSimpleMesh(meshes["dreptunghi"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}


		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(deplasament, 0.05f, -25.0f));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 0, 1));
			glm::vec3 colorBorders = glm::vec3(0.412, 0.412, 0.412);
			RenderSimpleMesh(meshes["dreptunghi"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}


		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(deplasament, 0.05f, 18.5f));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 0, 1));
			glm::vec3 colorBorders = glm::vec3(0.412, 0.412, 0.412);
			RenderSimpleMesh(meshes["dreptunghi"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}
		deplasament += 2.93f;
	}

	//placi-lat
	deplasament = 25.0f;
	for (int i = 0; i < 17; i++) {
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(24.25f, 0.05f, deplasament));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(180.0f), glm::vec3(0, 0, 1));
			glm::vec3 colorBorders = glm::vec3(0.412, 0.412, 0.412);
			RenderSimpleMesh(meshes["dreptunghi"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}


		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-18.0f, 0.05f, deplasament));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(180.0f), glm::vec3(0, 0, 1));
			glm::vec3 colorBorders = glm::vec3(0.412, 0.412, 0.412);
			RenderSimpleMesh(meshes["dreptunghi1"], shaders["ShaderLab6"], modelMatrix, colorBorders);
		}
		deplasament -= 2.93f;
	}

	// Render the camera target. Useful for understanding where is the rotation point in Third-person camera movement
	if (renderCameraTarget)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}
}

void Laborator6::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator6::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, glm::vec3 colorFigure)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	int location = glGetUniformLocation(shader->program, "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	location = glGetUniformLocation(shader->program, "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	location = glGetUniformLocation(shader->program, "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	//culoooooooare
	location = glGetUniformLocation(shader->program, "colorSphere");
	glUniform3fv(location, 1, glm::value_ptr(colorFigure));
	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

	location = glGetUniformLocation(shader->program, "time");
	float time = Engine::GetElapsedTime()/5;
	glUniform1f(location, cos(time));



}

void Laborator6::OnInputUpdate(float deltaTime, int mods)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 10.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(cameraSpeed * deltaTime);
		}
	}

	if (window->KeyHold(GLFW_KEY_UP))
	{
		forward = true;
		speed += 0.1;
		backward = false;
	}
	else if (window->KeyHold(GLFW_KEY_DOWN)) {
		speed -= 0.02;
	}
	else if (window->KeyHold(GLFW_KEY_RIGHT)) {
		speedRotating += 0.1;
		angle -= 1;
		rotateRight = true;
		
	}
	else if (window->KeyHold(GLFW_KEY_LEFT)) {
		speedRotating += 0.1;
		angle += 1;
		rotateLeft = true;
	}


}

void Laborator6::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}

void Laborator6::OnKeyRelease(int key, int mods)
{


	float sensivityOX = 0.001f;
	float sensivityOY = 0.001f;

	if (window->GetSpecialKeyState() == 0) {
		renderCameraTarget = false;
		// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
		// use the sensitivity variables for setting up the rotation speed
		camera->RotateFirstPerson_OX(sensivityOX * 0.35f);
		camera->RotateFirstPerson_OY(sensivityOY * xPar);
	}

	if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
		renderCameraTarget = true;
		// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
		// use the sensitivity variables for setting up the rotation speed
		camera->RotateThirdPerson_OX(sensivityOX * 0.35f);
		camera->RotateThirdPerson_OY(sensivityOY * xPar);
	}
}

void Laborator6::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Laborator6::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Laborator6::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Laborator6::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator6::OnWindowResize(int width, int height)
{
}
