#pragma once
#define _USE_MATH_DEFINES

#include "ImguiMenus.h"
#include "MeshModel.h"
#include "Utils.h"
#include <cmath>
#include <memory>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <nfd.h>
#include <random>
#include "Renderer.h"
#include <iostream>


bool showDemoWindow = false;
bool showSurfaceReflection = false;
bool showFeaturesWindow = false;
bool showLightWindow = false;
bool showAddLightWindow = false;
bool showOrthoProjection = true;
bool showPerspProjection = false;
bool showControlWindow = false;
bool showCameraControlWindow = false;
static char buf[256];

glm::vec3 objectColor;
glm::vec3 lightColor;

const glm::vec4 GetClearColor()
{
	return glm::vec4(1.0f, 1.f, 1.0f, 1.00f);
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene, Renderer& renderer)
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	/*if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}*/

	{
		static bool isdragged = true;
		static bool firstClick = true;
		ImVec2 size = ImGui::GetWindowSize();
		ImVec2 pos = ImGui::GetWindowPos();
		ImVec2 cursorLast, cursorCurrent;

		if (ImGui::IsMouseClicked(0))
		{
			cursorLast = ImGui::GetMousePos();
			firstClick = true;
		}
		if (ImGui::IsMouseDown(0) /*&& renderer.getCurrentModel() != NULL*/)
		{
			if (!firstClick)
			{
				if (!ImGui::IsMouseHoveringAnyWindow())
				{
					cursorCurrent = ImGui::GetMousePos();
					scene.getCurrentModel()->setRotationTransform(1.0f, (cursorCurrent.x - cursorLast.x), 1.0f);
					scene.getCurrentModel()->setRotationTransform((cursorCurrent.y - cursorLast.y), 1.0f, 1.0f);
				}
			}
			else
				firstClick = false;
		}
		if (ImGui::IsMouseReleased(0))
			isdragged = true;
	}

	// 2. Show controls window
	if ( showControlWindow )
	{
		//static float objectColor;
		static float modelAIntensity = 0.2f, modelDIntensity = 0.2f, modelSIntensity = 0.2f;
		static float scale = 1500.0f;
		static float turnUpDown = 0.0f;
		static float fov = 50.0f;
		static float rotateLocalX = 1.0f;
		static float rotateLocalY = 1.0f;
		static float rotateLocalZ = 1.0f;
		static float scaleX = 0.0f;
		static float scaleY = 0.0f;
		static float scaleZ = 0.0f;
		static float translateLocalX = 0.0f;
		static float translateLocalY = 0.0f;
		static float translateLocalZ = 0.0f;
		static float ar = 1.0;
		static float n = 1.0;
		static float fa = 10.0;
		static float worldX = 0.0f;
		static float worldY = 0.0f;
		static float worldZ = 0.0f;
		static float rotateWorldX = 0.0f;
		static float rotateWorldY = 0.0f;
		static float rotateWorldZ = 0.0f;
		ImGui::Begin("Model control", &showControlWindow);
		//ImGui::BeginChild("Controls", ImVec2(200,200), ImGuiWindowFlags_AlwaysVerticalScrollbar);
		
		/*ImGui::Text("This is some useful text.");*/               // Display some text (you can use a format strings too)
		//ImGui::Checkbox("Demo Window", &showDemoWindow);      // Edit bools storing our window open/close state
		//ImGui::Checkbox("Another Window", &showControlWindow);
		//ImGui::Text("Current Camera:");
	
		/*if (ImGui::SliderFloat("model ambient intensity:", &modelAIntensity, 0.0f, 1.0f) && renderer.isHasModel()) {
			renderer.getCurrentModel()->setModelAIntensity(modelAIntensity);}
		if (ImGui::SliderFloat("model Diffusive intensity:", &modelDIntensity, 0.0f, 1.0f) && renderer.isHasModel()) {
			renderer.getCurrentModel()->setModelDIntensity(modelDIntensity);}
		if (ImGui::SliderFloat("model Specular intensity:", &modelSIntensity, 0.0f, 1.0f) && renderer.isHasModel()) {
			renderer.getCurrentModel()->setModelSIntensity(modelSIntensity);}
		ImGui::Separator();*/

		//if (ImGui::SliderFloat("turn left or right", &turnUpDown, 0.0f, 360.0f) && renderer.isHasModel()) {
		//	renderer.setEyeX(turnUpDown);
		//}// Edit 1 float using a slider from 0.0f to 2000.0f
		//if (ImGui::SliderFloat("FOV", &fov, 0.0f, 90.0f) && renderer.isHasModel()) {
		//	renderer.setPerspective(fov,ar,(int)n,(int)fa);
		//}
		//if (ImGui::SliderFloat("ASPECT RATIO", &ar, 1.0f, 90.0f) && renderer.isHasModel()) {
		//	renderer.setPerspective(fov, ar, (int)n, (int)fa);
		//}
		//if (ImGui::SliderFloat("NEAR", &n, 1.0f, 90.0f) && renderer.isHasModel()) {
		//	renderer.setPerspective(fov, ar, (int)n, (int)fa);
		//	//renderer.setProj(fov, ar, n, fa); 
		//}
		//if (ImGui::SliderFloat("FAR", &fa, 10.0f, 150.0f) && renderer.isHasModel()) {
		//	renderer.setPerspective(fov, ar, (int)n, (int)fa);
		//}

		//local transformations
		ImGui::Text("Current Object:");
		ImGui::Text("Local Rotations");
		if (ImGui::SliderFloat("Rotate local x", &rotateLocalX, 0.0, 360.0f) && renderer.isHasModel()) {
			scene.getCurrentModel()->setRotationTransform(rotateLocalX, 1.0f, 1.0f);
		}
		if (ImGui::SliderFloat("Rotate local y", &rotateLocalY, 0.0, 360.0f) && renderer.isHasModel()) {
			scene.getCurrentModel()->setRotationTransform(1.0f, rotateLocalY, 1.0f);
		}
		if (ImGui::SliderFloat("Rotate local z", &rotateLocalZ, 0.0, 360.0f) && renderer.isHasModel()) {
			scene.getCurrentModel()->setRotationTransform(1.0f, 1.0f, rotateLocalZ);
		}
		ImGui::Text("Local Translations");
		if (ImGui::SliderFloat("Translate local x", &translateLocalX, 0.0, 360.0f) && renderer.isHasModel()) {
			scene.getCurrentModel()->setTranslationTransform(translateLocalX, translateLocalY, translateLocalZ);
		}
		if (ImGui::SliderFloat("Translate local y", &translateLocalY, 0.0, 360.0f) && renderer.isHasModel()) {
			scene.getCurrentModel()->setTranslationTransform(translateLocalX, translateLocalY, translateLocalZ);
		}
		if (ImGui::SliderFloat("Translate local z", &translateLocalZ, 0.0, 360.0f) && renderer.isHasModel()) {
			scene.getCurrentModel()->setTranslationTransform(translateLocalX, translateLocalY, translateLocalZ);
		}
		//scaling
		ImGui::Text("Scaling:");
		if (ImGui::SliderFloat("uniform scale", &scale, 0.0f, 1600.0f) && renderer.isHasModel()) {
			scene.getCurrentModel()->setScaleTransform(scale, scale, scale);
		}
		// world transformations
		ImGui::Text("World Translations");
		if (ImGui::SliderFloat("X:", &worldX, 0.0f, 1280.0f)) {
			scene.getCurrentModel()->setWorldTranslation(worldX, worldY, worldZ);
		}
		if (ImGui::SliderFloat("Y:", &worldY, 0.0f, 1280.0f)) {
			scene.getCurrentModel()->setWorldTranslation(worldX, worldY, worldZ);
		}
		if (ImGui::SliderFloat("Z:", &worldZ, 0.0f, 80.0f)) {
			scene.getCurrentModel()->setWorldTranslation(worldX, worldY, worldZ);
		}
		ImGui::Text("World Rotations");
		if (ImGui::SliderFloat("Rotate world x", &rotateWorldX, 0.0, 360.0f) && renderer.isHasModel()) {
			scene.getCurrentModel()->setWorldRotation(rotateWorldX, 1.0f, 1.0f);
		}
		if (ImGui::SliderFloat("Rotate world y", &rotateWorldY, 0.0, 360.0f) && renderer.isHasModel()) {
			scene.getCurrentModel()->setWorldRotation(1.0f, rotateWorldY, 1.0f);
		}
		if (ImGui::SliderFloat("Rotate world z", &rotateWorldZ, 0.0, 360.0f) && renderer.isHasModel()) {
			scene.getCurrentModel()->setWorldRotation(1.0f, 1.0f, rotateWorldZ);
		}	
		ImGui::End();
	}

	// 3. Show features window.
	if (showFeaturesWindow)
	{
		static int counter = 0;
		static float reflection = 1.0f;
		ImGui::Begin("Features", &showFeaturesWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		//ImGui::BeginChild("window", ImVec2(200, 200));
		//ImGui::Text("Hello from another window!");
		//showboundering cube (toggle)
		if (ImGui::Button("cube"))
		{
			renderer.setToDrawaCube(!renderer.getToDrawaCube());
			std::cout << "draw cube: " << renderer.getToDrawaCube() << std::endl;
		}
		//fill triangles (toggle)
		if (ImGui::Button("fill triangles"))
		{
			renderer.setFillTriangles(!renderer.getFillTriangles());
		}
		//draw triangles lines DEBUG (toggle)
		if (ImGui::Button("draw triangle lines"))
		{
			renderer.setdrawLines(!renderer.getdrawLines());
		}
		//show face normals (toggle)
		if (ImGui::Button("face normals"))
		{
			renderer.setToDrawFaceNormals(!renderer.getToDrawFaceNormals());
			std::cout << "face normals" << renderer.getToDrawFaceNormals() << std::endl;
		}
		//show lines normals (toggle)
		if (ImGui::Button("lines normals"))
		{
			renderer.setToDrawFaceNormals(!renderer.getToDrawFaceNormals());
			std::cout << "lines normals" << renderer.getToDrawFaceNormals() << std::endl;
		}
		//show vertices normals (toggle)
		if (ImGui::Button("vertices normals"))
		{
			renderer.setToDrawVertexNormals(!renderer.getToDrawVertexNormals());
			std::cout << "vertex normals" << renderer.getToDrawVertexNormals() << std::endl;
		}
		//projection
		/*if (ImGui::Button("Projection"))
		{
			renderer.setProjection(!renderer.getProjection());
			std::cout << "projection=" << renderer.getProjection() << std::endl;
		}*/
		/*if (ImGui::Button("Close Me"))
		{
			showFeaturesWindow = false;
		}*/
		/*ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);*/
		if (ImGui::SliderFloat("object reflection:", (float *)&reflection, -1, 1)) { renderer.setReflection(reflection);  }
		/*if (ImGui::ColorEdit3("object color:", (float*)&objectColor)) {
			renderer.getScene().getCurrentModel()->SetColor(objectColor);
		}*/
		//ImGui::EndChild();
		ImGui::End();
	}

	// 3.1 Show add light window.
	if (showAddLightWindow)
	{
		int type = 0;
		int diameterVal = 20;
		bool showtextBox = false;
		static int x_pos = 0;
		static int y_pos = 0;
		static int z_pos = 0;
		static float x_dir = 0.0f;
		static float y_dir = 0.0f;
		static float z_dir = 0.0f;
		static int diffusive;
		static int specular;

		
		//float clearColor;
		Light light;
		ImGui::Begin("Light", &showAddLightWindow);   
		ImGui::Columns(2);

		ImGui::BeginGroup();
		ImGui::Text("Light position:");
		if (ImGui::SliderInt(" x position", (int*)&x_pos, -5000, 5000) && renderer.isHasModel()) { }
		if (ImGui::SliderInt(" y position", (int*)&y_pos, -5000, 5000) && renderer.isHasModel()) { }
		if (ImGui::SliderInt(" z position", (int*)&z_pos, -5000, 5000) && renderer.isHasModel()) { }
		ImGui::NextColumn();
		ImGui::BeginGroup();
		ImGui::Text("Light direction:");
		if (ImGui::SliderFloat(" x direction", (float*)&x_dir, -1, 1) && renderer.isHasModel()) {}
		if (ImGui::SliderFloat(" y direction", (float*)&y_dir, -1, 1) && renderer.isHasModel()) {}
		if (ImGui::SliderFloat(" z direction", (float*)&z_dir, -1, 1) && renderer.isHasModel()) {}
		ImGui::EndGroup();
		ImGui::Separator();
		
		ImGui::Columns(1);
		ImGui::RadioButton("diffusive", &diffusive, 1);
		if (diffusive)
		{
			type = 1; specular = 0; showtextBox = !showtextBox;
		} 
		if (showtextBox ) 
		{
			/*ImGui::SameLine();
			ImGui::Text("Diameter:");*/
			ImGui::SameLine();
			ImGui::InputText("Diameter", buf, 5, ImGuiInputTextFlags_EnterReturnsTrue); 
		}
		if (ImGui::RadioButton("specular", &specular, 2)) { type = 2; diffusive = 0; }
		ImGui::Separator();
		ImGui::ColorEdit3("clear color", (float*)&lightColor);
		ImGui::EndGroup();


		ImGui::Separator();
		if (ImGui::Button("add"))
		{
			light.setPosition(glm::vec3(x_pos, y_pos, z_pos));
			light.setDirection(glm::vec3(x_dir, y_dir, z_dir));
			light.setNormal(glm::normalize(glm::vec3(x_pos, y_pos, z_pos) - glm::vec3(x_dir, y_dir, z_dir)));
			light.setColor(lightColor);
			light.setActive(true);
			light.setType(type);
			if (diffusive && (diameterVal = atoi(buf)) <= 1000) light.setDiameter(diameterVal);
			//renderer.addLight(light);
			showAddLightWindow = false;
		}
		
		
		ImGui::End();
	}
	
	// 3.2 Show lights window.
	if (showLightWindow)
	{
		//TODO: add controls to translate existing light

		static float Intensity = 0.5f, factor = 0.5f;
		static int light_x, light_y, light_z;
		std::vector <Light> lights = scene.getLights();
		std::vector <Light>::iterator l = lights.begin();
		
		//float clearColor;
		Light light;
		ImGui::Begin("Lights", &showLightWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		
		ImGui::Text("Ambient light");
		//if (ImGui::SliderFloat("factor", (float*)&factor, 0.0f, 1.0f) && renderer.isHasModel()) { renderer.setAmbientCoefficient(factor); }
		if (ImGui::ColorEdit3("ambient color", (float*)&lightColor)) { renderer.setAmbientColor(lightColor); }
		if (ImGui::SliderFloat("ambient intensity", (float*)&Intensity, 0.0f, 1.0f)) { renderer.setAmbientIntensity(Intensity); }
		ImGui::Separator();
		
	
		if (lights.size() > 0)
		{
			int count = 0;
			for ( /*l = lights.begin()*/; l != lights.end(); l++, count++)
			{
				glm::vec3 pos = (*l).getLightPos();
				ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Light #%d", count + 1);
				if (ImGui::SliderInt("light x pos", (int*)&light_x, -3000, 3000)) { 
					l->setPosition(glm::vec3(pos.x + light_x, pos.y, pos.z)); 
					scene.getLights().at(count).setPosition(glm::vec3(pos.x + light_x, pos.y + light_y, pos.z + light_z));
				}
				if (ImGui::SliderInt("light y pos", (int*)&light_y, -3000, 3000)) { l->setPosition(glm::vec3(pos.x, pos.y + light_y, pos.z)); }
				if (ImGui::SliderInt("light z pos", (int*)&light_z, -3000, 3000)) { l->setPosition(glm::vec3(pos.x, pos.y, pos.z + light_z)); }
				ImGui::Separator();
			}
			/*for (size_t i = 0; i < renderer.getScene().getLights().size(); i++)
			{
				Light *l = &(renderer.getScene().getLights().at(i));
				glm::vec3 pos = (*l).getLightPos();
				ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Light #%d", i);
				if (ImGui::SliderInt("light x pos", (int*)&light_x, -3000, 3000)) { (*l).setPosition(glm::vec3(pos.x + light_x, pos.y, pos.z)); }
				if (ImGui::SliderInt("light y pos", (int*)&light_y, -3000, 3000)) { (*l).setPosition(glm::vec3(pos.x, pos.y + light_y, pos.z)); }
				if (ImGui::SliderInt("light z pos", (int*)&light_z, -3000, 3000)) { (*l).setPosition(glm::vec3(pos.x, pos.y, pos.z + light_z)); }
				ImGui::Separator();
			}*/
		}
		
		
		ImGui::End();
	}

	// 3.3 change projection functionality
	if (showPerspProjection)
	{
		renderer.setIsProjPerspective(true);
		renderer.setIsProjOrthographic(false);
	}
	else if (showOrthoProjection)
	{
		renderer.setIsProjPerspective(false);
		renderer.setIsProjOrthographic(true);
	}

	// 3.4 show the surface reflection coefficients of the model
	if (showSurfaceReflection)
	{
		ImGui::Begin("Surface coefficients", &showSurfaceReflection);
		static float Ka = 0.2f, Kd = 0.2f, Ks = 0.2f;
		ImGui::Text("set models and ambient reflection parameters");
		if (ImGui::SliderFloat("Ambient:", (float*)&Ka, 0.0f, 1.0f)) { renderer.setAmbientIntensity(Ka); }
		if (ImGui::SliderFloat("Diffusive:", (float*)&Kd, 0.0f, 1.0f)) { renderer.setDiffusiveIntensity(Kd); }
		if (ImGui::SliderFloat("Specular:", (float*)&Ks, 0.0f, 1.0f)) { renderer.setSpecularIntensity(Ks); }
		ImGui::End();
	}

	// 3.5 show cameras control window
	if (showCameraControlWindow && scene.getCameras().size())
	{
		std::shared_ptr<Camera> camera = scene.getActiveCamera();
		//const viewVolume vv = camera->getViewVolume();
		static float e_x = camera->getEye().x, e_y = camera->getEye().y, e_z = camera->getEye().z;
		static float a_x = camera->getAt().x, a_y = camera->getAt().y, a_z = camera->getAt().z;
		static float u_x = camera->getUp().x, u_y = camera->getUp().y, u_z = camera->getUp().z;
		const glm::vec4 eye = camera->getEye();
		const glm::vec4 at = camera->getAt();
		const glm::vec4 up = camera->getUp();
		static bool table = true;
		static float fov;
		static float ar;
		const int _near = camera->getNear(), _far = camera->getFar(), left = camera->getLeft(), right = camera->getRight(), bottom = camera->getBottom(), top = camera->getTop();
		static int ortho = 0;
		ImGui::Begin("cameras control window", &showCameraControlWindow);

		//ImGui::BeginTable("view volume", headers, widths);
		// display cameras parameters
		ImGui::Text("camera %d", camera->getCameraIndex());
		ImGui::Columns(2);
		// projection
		ImGui::Text("projection");
		if (ImGui::RadioButton("orthgraphic", &ortho, 0)) { camera->setIsortho(true); }
		if (ImGui::RadioButton("perspective", &ortho, 1)) { camera->setIsortho(false); }
		if (ortho == 1)
		{
			if (ImGui::SliderFloat("field of view ", (float*)&fov, 0.0f, 90.0f)) { camera->setFOV(fov); }
			if (ImGui::SliderFloat("aspect ratio ", (float*)&ar, 0.2f, 1.5f)) { camera->setAspectRatio(ar); }
		}
		// view volume
		ImGui::Text("view volume");
		if (ImGui::SliderInt("near", (int*)&_near, -100, 100)) { camera->setNear(_near); }
		if (ImGui::SliderInt("far", (int*)&_far, -100, 100)) { camera->setFar(_far); }
		//ImGui::NextColumn();
		if (ImGui::SliderInt("left", (int*)&left, -100, 100)) { camera->setLeft(left); }
		if (ImGui::SliderInt("right", (int*)&right, -100, 100)) { camera->setRight(right); }
		//ImGui::NextColumn();
		if (ImGui::SliderInt("bottom", (int*)&bottom, -100, 100)) { camera->setBottom(bottom); }
		if (ImGui::SliderInt("top", (int*)&top, -100, 100)) { camera->setTop(top); }
		ImGui::NextColumn();
		//ImGui::Separator();
		ImGui::BeginGroup();
		ImGui::Text("camera look at");
		//ImGui::Separator();

		//ImGui::Columns(3);
		ImGui::Text("Eye:");;
		if (ImGui::SliderFloat("eye x:", (float*)&e_x, -100.0f, 100.0f)) { camera->setEye(glm::vec4(e_x, e_y, e_z, 1.0f)); }
		if (ImGui::SliderFloat("eye y:", (float*)&e_y, -100.0f, 100.0f)) { camera->setEye(glm::vec4(e_x, e_y, e_z, 1.0f)); }
		if (ImGui::SliderFloat("eye z:", (float*)&e_z, -100.0f, 100.0f)) { camera->setEye(glm::vec4(e_x, e_y, e_z, 1.0f)); }

		//ImGui::NextColumn();
		ImGui::Text("at:");
		if (ImGui::SliderFloat("at x:", (float*)&a_x, -100.0f, 100.0f)) { camera->setAt(glm::vec4(a_x, a_y, a_z, 1.0f)); }
		if (ImGui::SliderFloat("at y:", (float*)&a_y, -100.0f, 100.0f)) { camera->setAt(glm::vec4(a_x, a_y, a_z, 1.0f)); }
		if (ImGui::SliderFloat("at z:", (float*)&a_z, -100.0f, 100.0f)) { camera->setAt(glm::vec4(a_x, a_y, a_z, 1.0f)); }

		//ImGui::NextColumn();
		ImGui::Text("up:");
		if (ImGui::SliderFloat("up x:", (float*)&u_x, -1.0f, 1.0f)) { camera->setUp(glm::vec4(u_x, u_y, u_z, 1.0f)); }
		if (ImGui::SliderFloat("up y:", (float*)&u_y, -1.0f, 1.0f)) { camera->setUp(glm::vec4(u_x, u_y, u_z, 1.0f)); }
		if (ImGui::SliderFloat("up z:", (float*)&u_z, -1.0f, 1.0f)) { camera->setUp(glm::vec4(u_x, u_y, u_z, 1.0f)); }

		ImGui::EndGroup();
		ImGui::End();
	}

	// 4. Menu bar 
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoFocusOnAppearing;
		if (ImGui::BeginMainMenuBar())
		{
			//File submenu
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Load Model...", "CTRL+O"))
				{
					nfdchar_t *outPath = NULL;
					nfdresult_t result = NFD_OpenDialog("obj;png,jpg", NULL, &outPath);
					if (result == NFD_OKAY) {
						scene.AddModel(std::make_shared<MeshModel>(Utils::LoadMeshModel(outPath)));
						//set renderer current model to the last model in the scene model list
						//scene.setCurrentModel(scene.getModels().at(scene.GetModelCount() - 1));
						showControlWindow = true;
						showCameraControlWindow = true;
						renderer.setHasModel();
						//renderer.setEyeX(0);
						//renderer.translate(640, 360, 0);
						//renderer.setPerspective(50,1,1,10);

						free(outPath);
					}
					else if (result == NFD_CANCEL) {
					}
					else {
					}

				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Add Primitives"))
			{
				if (ImGui::MenuItem("Add Poly"))
				{
					scene.AddModel(std::make_shared<MeshModel>(MeshModel(0)));
					renderer.setCurrentModel(scene.getModels().at(scene.GetModelCount() - 1));

					renderer.setHasModel();
					renderer.setEyeX(0);
				

				}
				if (ImGui::MenuItem("Add box"))
				{

				}
				ImGui::EndMenu();
			}
			//camera menu
			if (ImGui::BeginMenu("Cameras"))
			{
				if (ImGui::MenuItem("Add camera"))
				{
					Camera c;
					scene.addCamera(c);
				}
				if (ImGui::BeginMenu("Active cameras"))
				{
					int count;
					std::vector<std::shared_ptr<Camera>> cameras = scene.getCameras();
					std::vector<std::shared_ptr<Camera>>::iterator it;
					for (it = cameras.begin(), count = 0; it != cameras.end(); count++, it++)
					{
						std::string name;
						if (count == 0 )
							name = "world";
						
						else
						{
							name = "camera ";
							std::string index(std::to_string((*it)->getCameraIndex()));
							name.append(index);
						}
						if (ImGui::MenuItem(name.c_str()) )
						{
							scene.setActiveCameraIndex((*it)->getCameraIndex());
							showCameraControlWindow = true;
						}
					}
					/*int size = scene.getCameraCount();
					if (size != 0) {
						std::vector<char*> cNames(scene.getcamerasNames());
						float sz = ImGui::GetTextLineHeight();
						for (int i = 0; i < size; i++)
						{
							const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
							ImVec2 p = ImGui::GetCursorScreenPos();
							ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
							ImGui::Dummy(ImVec2(sz, sz));
							ImGui::SameLine();
							if (ImGui::MenuItem(cNames[i]))
							{
								scene.setActiveCameraIndex(i);
							}
						}
					}*/
					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			//projection menu
			if (ImGui::BeginMenu("Projection"))
			{
				if (ImGui::MenuItem("Perspective"))
				{
					renderer.setIsProjPerspective(true);
					renderer.setIsProjOrthographic(false);
				}

				if (ImGui::MenuItem("Orthographic"))
				{
					renderer.setIsProjOrthographic(true);
					renderer.setIsProjPerspective(false);
				}

				if (ImGui::MenuItem("Reset"))
				{
					renderer.setIsProjOrthographic(true);
					renderer.setIsProjPerspective(false);
				}
				ImGui::EndMenu();
			}


			//lighting submenu
			if (ImGui::BeginMenu("Lights"))
			{
				std::vector<Light> lights = scene.getLights();
				std::vector<Light>::iterator light;
				//const char *name;

				if (ImGui::MenuItem("add light"))
				{
					showAddLightWindow = true;
				}

				if (ImGui::MenuItem("lights"))
				{
					showLightWindow = true;
				}

				for (light = lights.begin(); light != lights.end(); light++)
				{
					

					/*if (ImGui::MenuItem(name))
					{
						(*it)->setIsCurrentModel(true);
						std::cout << name << std::endl;
					}*/
				}
				ImGui::EndMenu();
			}

			//model submenu
			if (ImGui::BeginMenu("Model"))
			{
				if (ImGui::MenuItem("model controls"))
				{
					showControlWindow = true;
				}

				if (ImGui::MenuItem("scene models"))
				{
					std::vector<std::shared_ptr<MeshModel>> models = scene.getModels();
					std::vector<std::shared_ptr<MeshModel>>::iterator it;
					const char *name;

					for (it = models.begin(); it != models.end(); it++)
					{
						name = (*it)->getModelName().c_str();
						(*it)->setIsCurrentModel(false);

						if (ImGui::MenuItem(name))
						{
							(*it)->setIsCurrentModel(true);
							std::cout << name << std::endl;
						}
					}
				}

				if (ImGui::MenuItem("Features"))
				{
					showFeaturesWindow = true;
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}	
}