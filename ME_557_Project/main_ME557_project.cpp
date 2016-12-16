//
//  main_spotlight.cpp
//  HCI 557 Spotlight example
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "Sphere3D.h"
#include "Texture.h"
#include "Plane3D.h"
#include "Box3D.h"
#include "GLObjectObj.h"
using namespace std;


// The handle to the window object
GLFWwindow*         window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;
extern int key_up;
extern int key_down;
extern int key_left;
extern int key_right;
extern int key_init;
extern int g_change_texture_blend;
extern int key_select1;
extern int key_select2;
extern int key_select3;
extern int key_select4;
extern int key_select5;
extern int key_select6;
extern int key_select7;
extern int key_select8;


int main(int argc, const char * argv[])
{
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    SetCameraManipulator(CameraTypes::CAMERA_MANIPULATOR);

    

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Create some models
    
    // coordinate system
    CoordSystem* cs = new CoordSystem(40.0);
    
    
    // create an apperance object.
    GLAppearance* apperance_0 = new GLAppearance("../data/shaders/multi_vertex_lights.vs", "../data/shaders/multi_vertex_lights.fs");
	GLAppearance* apperance_01 = new GLAppearance("../data/shaders/multi_vertex_lights.vs", "../data/shaders/multi_vertex_lights.fs");
	GLAppearance* apperance_1 = new GLAppearance("../data/shaders/single_texture.vs", "../data/shaders/single_texture.fs");
	GLAppearance* apperance_2 = new GLAppearance("../data/shaders/single_texture.vs", "../data/shaders/single_texture.fs");
	GLAppearance* apperance_3 = new GLAppearance("../data/shaders/single_texture.vs", "../data/shaders/single_texture.fs");
	GLAppearance* apperance_4 = new GLAppearance("../data/shaders/single_texture.vs", "../data/shaders/single_texture.fs");
	GLAppearance* apperance_5 = new GLAppearance("../data/shaders/single_texture.vs", "../data/shaders/single_texture.fs");
	GLAppearance* apperance_6 = new GLAppearance("../data/shaders/single_texture.vs", "../data/shaders/single_texture.fs");


    GLDirectLightSource  light_source;
    light_source._lightPos = glm::vec4(0.0, 100.0, 100.0, 1.0);
    light_source._ambient_intensity = 1.2;
    light_source._specular_intensity = 5.5;
    light_source._diffuse_intensity = 2.0;
    light_source._attenuation_coeff = 0.0;
	
	GLPointLightSource  light_source1;
	light_source._lightPos = glm::vec4(-20.0, -20.0, 20.0, 1.0);
	light_source._ambient_intensity = 1.2;
	light_source._specular_intensity = 5.5;
	light_source._diffuse_intensity = 2.0;
	light_source._attenuation_coeff = 0.0;

	GLDirectLightSource  light_source_1;
	light_source._lightPos = glm::vec4(50.0, 50.0, 0.0, 0.0);
	light_source._ambient_intensity = 0.2;
	light_source._specular_intensity = 2.5;
	light_source._diffuse_intensity = 1.0;
	light_source._attenuation_coeff = 0.0;

    // add the light to this apperance object
    apperance_0->addLightSource(light_source);
	apperance_01->addLightSource(light_source1);

	apperance_1->addLightSource(light_source_1);

    // Create a material object
    GLMaterial material_0;
    material_0._diffuse_material = glm::vec3(0.0, 0.0, 0.0);
    material_0._ambient_material = glm::vec3(0.0, 0.0, 0.0);
    material_0._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material_0._shininess = 10.0;
    material_0._transparency = 1.0;
    
	GLMaterial material_1;
	material_0._diffuse_material = glm::vec3(0.99, 0.92, 0.18);
	material_0._ambient_material = glm::vec3(0.99, 0.92, 0.18);
	material_0._specular_material = glm::vec3(0.99, 0.92, 0.18);
	material_0._shininess = 1.0;
	material_0._transparency = 1.0;

    // Add the material to the apperance object
    apperance_0->setMaterial(material_0);
	apperance_01->setMaterial(material_0);

	apperance_1->setMaterial(material_1);
	apperance_2->setMaterial(material_1);


    

    // If you want to change appearance parameters after you init the object, call the update function
    apperance_0->updateLightSources();
	apperance_01->updateLightSources();
	apperance_0->finalize();
	apperance_01->finalize();

	// Texture
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	GLTexture* texture = new GLTexture();
	GLTexture* texture2 = new GLTexture();
	GLTexture* texture3 = new GLTexture();
	GLTexture* texture4 = new GLTexture();
	GLTexture* texture5 = new GLTexture();
	GLTexture* texture6 = new GLTexture();

	//int texid = texture->loadAndCreateTextures("../data/textures/texture_isu.bmp", "../data/textures/panda2.bmp", "../data/textures/Front.bmp");
	int texid = texture->loadAndCreateTexture("data/textures/wall1.bmp");
	texture2->loadAndCreateTexture("data/textures/ceiling1.bmp");
	texture3->loadAndCreateTexture("data/textures/floor1.bmp");
	texture4->loadAndCreateTexture("data/textures/wood.bmp");
	texture5->loadAndCreateTexture("data/textures/red.bmp");
	texture6->loadAndCreateTexture("data/textures/menu.bmp");

	apperance_1->setTexture(texture);
	apperance_1->finalize();
	apperance_2->setNewTex(texture2, 2);
	apperance_2->finalize();
	apperance_3->setNewTex(texture3, 3);
	apperance_3->finalize();
	apperance_4->setNewTex(texture4, 4);
	apperance_4->finalize();
	apperance_5->setNewTex(texture3, 5);
	apperance_5->finalize();
	apperance_6->setNewTex(texture6, 6);
	apperance_6->finalize();

	// Object creation
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    GLObjectObj* layer1 = new GLObjectObj("data/Layers/Layer1.obj");
    layer1->setApperance(*apperance_0);
	layer1->init();
	glm::mat4 layer1_init = layer1->getModelMatrix();
    
	GLObjectObj* layer2 = new GLObjectObj("data/Layers/Layer2.obj");
	layer2->setApperance(*apperance_0);
	layer2->init();

	GLObjectObj* layer3 = new GLObjectObj("data/Layers/Layer3.obj");
	layer3->setApperance(*apperance_0);
	layer3->init();

	GLObjectObj* layer4 = new GLObjectObj("data/Layers/Layer4.obj");
	layer4->setApperance(*apperance_0);
	layer4->init();

	GLObjectObj* layer5 = new GLObjectObj("data/Layers/Layer5.obj");
	layer5->setApperance(*apperance_0);
	layer5->init();

	GLObjectObj* layer6 = new GLObjectObj("data/Layers/Layer6.obj");
	layer6->setApperance(*apperance_0);
	layer6->init();

    glm::mat4 tranform = glm::scale(glm::vec3(400.0, 400.0f, 400.0f));
	glm::mat4 tranform2 = glm::translate(glm::vec3(-40.5f, -50.75f, 0.0f));
	glm::mat4 tranform3 = glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 tranform4 = glm::translate(glm::vec3(0.0f, -10.0f, 0.0f));
	glm::mat4 transform_multi = tranform4 * tranform3 * tranform2 * tranform;
	layer1->setMatrix(transform_multi);

	glm::mat4 translate_2 = glm::translate(glm::vec3(-40.5f, -50.75f, -0.25f));
	glm::mat4 transform_multi2 = tranform4 * tranform3 * translate_2 * tranform;
	layer2->setMatrix(transform_multi2);
	glm::mat4 layer2_init = layer2->getModelMatrix();

	glm::mat4 translate_3 = glm::translate(glm::vec3(-40.5f, -50.75f, -0.40f));
	glm::mat4 transform_multi3 = tranform4 * tranform3 * translate_3 * tranform;
	layer3->setMatrix(transform_multi3);
	glm::mat4 layer3_init = layer3->getModelMatrix();

	glm::mat4 translate_4 = glm::translate(glm::vec3(-40.5f, -50.75f, -0.70f));
	glm::mat4 transform_multi4 = tranform4 * tranform3 * translate_4 * tranform;
	layer4->setMatrix(transform_multi4);
	glm::mat4 layer4_init = layer4->getModelMatrix();

	glm::mat4 translate_5 = glm::translate(glm::vec3(-40.5f, -50.75f, -0.90f));
	glm::mat4 transform_multi5 = tranform4 * tranform3 * translate_5 * tranform;
	layer5->setMatrix(transform_multi5);
	glm::mat4 layer5_init = layer5->getModelMatrix();

	glm::mat4 translate_6 = glm::translate(glm::vec3(-40.5f, -50.75f, -1.10f));
	glm::mat4 transform_multi6 = tranform4 * tranform3 * translate_6 * tranform;
	layer6->setMatrix(transform_multi6);
	glm::mat4 layer6_init = layer6->getModelMatrix();

	GLPlane3D* plane_1[16][10]; 
	GLPlane3D* plane_2[16][10];
	GLPlane3D* plane_3[16][10];
	GLPlane3D* plane_4[16][10];
	GLPlane3D* plane_5[16][10];
	GLPlane3D* plane_6[2][10];
	GLPlane3D* plane_7 = new GLPlane3D(0.0, 20.0, -49.0, 60.0, 30.0);
	GLBox3D* box1 = new GLBox3D(0, -11.50 , 0, 30, 2, 50);
	box1->setApperance(*apperance_4);
	box1->init();
	
	plane_7->setApperance(*apperance_6);
	plane_7->init();
	//= new GLPlane3D(0.0, 0.0, -50.0, 100.0, 100, 3.0);
	for (int b = 0; b < 10; b++)
	{

		for (int a = 0; a < 16; a++)
		{
			plane_1[a][b] = new GLPlane3D(-150.0 + (a*20.0), -100.0 + (b*20.0), -50.0, 20.0, 20.0);
			plane_1[a][b]->setApperance(*apperance_1);
			plane_1[a][b]->init();

		}
	}
	for (int b = 0; b < 10; b++)
	{

		for (int a = 0; a < 16; a++)
		{
			plane_2[a][b] = new GLPlane3D(-150.0 + (a*20.0), -100.0 + (b*20.0), -50.0, 20.0, 20.0);
			plane_2[a][b]->setApperance(*apperance_1);
			plane_2[a][b]->init();
			glm::mat4 tranform_wall2 = glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 tranform2_wall2 = glm::translate(glm::vec3(-20.0f, 0.0f, 0.0f));
			glm::mat4 wall2_final = tranform2_wall2 * tranform_wall2;
			plane_2[a][b]->setMatrix(wall2_final);


		}
	}
	for (int b = 0; b < 10; b++)
	{

		for (int a = 0; a < 16; a++)
		{
			plane_3[a][b] = new GLPlane3D(-150.0 + (a*20.0), -100.0 + (b*20.0), -50.0, 20.0, 20.0);
			plane_3[a][b]->setApperance(*apperance_1);
			plane_3[a][b]->init();
			glm::mat4 tranform_wall2 = glm::rotate(-1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 tranform2_wall2 = glm::translate(glm::vec3(20.0f, 0.0f, 0.0f));
			glm::mat4 wall2_final = tranform2_wall2 * tranform_wall2;
			plane_3[a][b]->setMatrix(wall2_final);


		}
	}
	for (int b = 0; b < 10; b++)
	{

		for (int a = 0; a < 16; a++)
		{
			plane_4[a][b] = new GLPlane3D(-150.0 + (a*20.0), -100.0 + (b*20.0), -50.0, 20.0, 20.0);
			plane_4[a][b]->setApperance(*apperance_2);
			plane_4[a][b]->init();
			glm::mat4 tranform_wall2 = glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 tranform2_wall2 = glm::translate(glm::vec3(10.0f, 0.0f, 0.0f));
			glm::mat4 wall2_final = tranform2_wall2 * tranform_wall2;
			plane_4[a][b]->setMatrix(wall2_final);


		}
	}
	for (int b = 0; b < 10; b++)
	{

		for (int a = 0; a < 16; a++)
		{
			plane_5[a][b] = new GLPlane3D(-150.0 + (a*20.0), -100.0 + (b*20.0), -50.0, 20.0, 20.0);
			plane_5[a][b]->setApperance(*apperance_3);
			plane_5[a][b]->init();
			glm::mat4 tranform_wall2 = glm::rotate(-1.57f, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 tranform2_wall2 = glm::translate(glm::vec3(10.0f, 0.0f, 0.0f));
			glm::mat4 wall2_final = tranform2_wall2 * tranform_wall2;
			plane_5[a][b]->setMatrix(wall2_final);


		}
	}
	for (int b = 0; b < 3; b++)
	{

		for (int a = 0; a < 2; a++)
		{
			plane_6[a][b] = new GLPlane3D(-10.0 + (a*20), -10.0 + (b*20.0), -50.0, 20.0, 20.0);
			plane_6[a][b]->setApperance(*apperance_4);
			plane_6[a][b]->init();
			glm::mat4 tranform_wall2 = glm::rotate(-1.57f, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 tranform2_wall2 = glm::translate(glm::vec3(00.0f, 39.75f, 0.0f));
			glm::mat4 wall2_final = tranform2_wall2 * tranform_wall2;
			plane_6[a][b]->setMatrix(wall2_final);


		}
	}


	apperance_1->updateLightSources();
	apperance_2->updateLightSources();
	apperance_3->updateLightSources();
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.5f, 0.3f, 0.7f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector. 
    SetViewAsLookAt(glm::vec3(-30.0f, 30.0f, 30.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    
    
    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Blending
    
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
		float camdist = _get_camdist();
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This renders the objects
		if (camdist < 75)
		{
			SetTrackballLocation(GetCurrentCameraMatrix(), GetCurrentCameraTranslation());
			camdist = 70;
		}
        // Set the trackball locatiom
        
        // draw the objects
        cs->draw();
        
        layer1->draw();
		layer2->draw();
		layer3->draw();
		layer4->draw();
		layer5->draw();
		layer6->draw();

		for (int b = 0; b < 10; b++)
		{
			for (int a = 0; a < 16; a++)
			{
				plane_1[a][b]->draw();
			}
		}
		for (int b = 0; b < 10; b++)
		{
			for (int a = 0; a < 16; a++)
			{
				plane_2[a][b]->draw();
			}
		}
		for (int b = 0; b < 10; b++)
		{
			for (int a = 0; a < 16; a++)
			{
				plane_3[a][b]->draw();
			}
		}
		for (int b = 0; b < 10; b++)
		{
			for (int a = 0; a < 16; a++)
			{
				plane_4[a][b]->draw();
			}
		}
		for (int b = 0; b < 10; b++)
		{
			for (int a = 0; a < 16; a++)
			{
				plane_5[a][b]->draw();
			}
		}
		for (int b = 0; b < 3; b++)
		{
			for (int a = 0; a < 2; a++)
			{
				//plane_6[a][b]->draw();
			}
		}
		box1->draw();
		plane_7->draw();
        //// This renders the objects
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (key_select1 == 0 && key_select2 == 0 && key_select3 == 0 && key_select4 == 0 && key_select5 == 0)
		{
			key_up = 0; key_down = 0; key_left = 0; key_right = 0;
		}
		if (key_select1 == 1)
		{
			

			layer2->keystrokes1(key_up); 		layer3->keystrokes1(key_up);		layer4->keystrokes1(key_up);
			layer2->keystrokes2(key_down);		layer3->keystrokes2(key_down);		layer4->keystrokes2(key_down);
			layer2->keystrokes3(key_left);		layer3->keystrokes3(key_left);		layer4->keystrokes3(key_left);
			layer2->keystrokes4(key_right);		layer3->keystrokes4(key_right);		layer4->keystrokes4(key_right);

			layer5->keystrokes1(key_up); 		layer6->keystrokes1(key_up);		
			layer5->keystrokes2(key_down);		layer6->keystrokes2(key_down);		
			layer5->keystrokes3(key_left);		layer6->keystrokes3(key_left);		
			layer5->keystrokes4(key_right);		layer6->keystrokes4(key_right);		

		}

		if (key_select2 == 1)
		{
			layer3->keystrokes1(key_up);			layer4->keystrokes1(key_up);
			layer3->keystrokes2(key_down);			layer4->keystrokes2(key_down);
			layer3->keystrokes3(key_left);			layer4->keystrokes3(key_left);
			layer3->keystrokes4(key_right);			layer4->keystrokes4(key_right);

			layer5->keystrokes1(key_up); 		layer6->keystrokes1(key_up);
			layer5->keystrokes2(key_down);		layer6->keystrokes2(key_down);
			layer5->keystrokes3(key_left);		layer6->keystrokes3(key_left);
			layer5->keystrokes4(key_right);		layer6->keystrokes4(key_right);

		}

		if (key_select3 == 1)
		{
			layer4->keystrokes1(key_up);
			layer4->keystrokes2(key_down);
			layer4->keystrokes3(key_left);
			layer4->keystrokes4(key_right);

			layer5->keystrokes1(key_up); 		layer6->keystrokes1(key_up);
			layer5->keystrokes2(key_down);		layer6->keystrokes2(key_down);
			layer5->keystrokes3(key_left);		layer6->keystrokes3(key_left);
			layer5->keystrokes4(key_right);		layer6->keystrokes4(key_right);

		}

		if (key_select4 == 1)
		{
			layer5->keystrokes1(key_up); 		layer6->keystrokes1(key_up);
			layer5->keystrokes2(key_down);		layer6->keystrokes2(key_down);
			layer5->keystrokes3(key_left);		layer6->keystrokes3(key_left);
			layer5->keystrokes4(key_right);		layer6->keystrokes4(key_right);

		}
		if (key_select5 == 1)
		{
			layer6->keystrokes1(key_up);
			layer6->keystrokes2(key_down);
			layer6->keystrokes3(key_left);
			layer6->keystrokes4(key_right);
		}


		// initialize models to start position
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool ret = texture->setTextureBlendMode(g_change_texture_blend);
		if (ret)apperance_1->updateTextures();
		
		
		
		//bool ret1 = layer1->keystrokes_init(key_init, layer1_init);
		//if (ret1 == true)
			//key_init--;
		bool ret2 = layer2->keystrokes_init(key_init, layer2_init);
		bool ret3 = layer3->keystrokes_init(key_init, layer3_init);
		bool ret4 = layer4->keystrokes_init(key_init, layer4_init);
		bool ret5 = layer5->keystrokes_init(key_init, layer5_init);
		bool ret6 = layer6->keystrokes_init(key_init, layer6_init);

		if (ret2 == true || ret3 == true || ret4 == true || ret5 == true || ret6 == true)
			key_init--; 
		//layer2->keystrokes_initc(key_init);
		
		// Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    delete cs;


}

