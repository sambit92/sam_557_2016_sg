//
//  HW3.cpp
//  ME557 Course
//
//  Sambit Ghadai
//  Major: Mechanical Engineering
//
/*I changed the g_projectionMatrix var in GLObject.cpp file to 
g_projectionMatrix = glm::perspective(0.5f, (float)1366 / (float)720, 0.01f, 100000.f);

-this changes the resolution of the window and the viewing angle.

Please change these values in the GLObject.cpp file or use the file that I havve uploaded to see the correct appearance.*/

#include <iostream>
#include <string>

#include <GL/glew.h>

#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


#include <GLFW/glfw3.h>


#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "Sphere3D.h"
#include "GLAppearance.h"




using namespace std;


GLFWwindow*         window;

GLuint program;

//extern Trackball trackball;



int main(int argc, const char * argv[])
{
    
    
    window = initWindow();
    
    
    initGlew();
    
    

    
    CoordSystem* cs = new CoordSystem(40.0);

    
    GLAppearance* apperance = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	GLAppearance* apperance2 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	GLAppearance* apperance3 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	GLAppearance* apperance4 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");

    
    GLSpotLightSource  light_source1_1;
    light_source1_1._lightPos = glm::vec4(20.0,0.0,0.0, 1.0);
    light_source1_1._ambient_intensity = 0.0;
    light_source1_1._specular_intensity = 8.0;
    light_source1_1._diffuse_intensity = 1.0;
    light_source1_1._attenuation_coeff = 0.02;
    light_source1_1._cone_angle = 12.0; // in degree
    light_source1_1._cone_direction = glm::vec3(-1.0, -1.0, 0.0); 
    
    
    GLDirectLightSource  light_source1_2;
    light_source1_2._lightPos = glm::vec4(20.0,0.0,-15.0, 0.0);
    light_source1_2._ambient_intensity = 0.0;
    light_source1_2._specular_intensity = 1.2;
    light_source1_2._diffuse_intensity = 1.2;
    light_source1_2._attenuation_coeff = 0.02;
   // light_source2._cone_angle = 12.0; // in degree
   // light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.
    
	GLSpotLightSource  light_source2_1;
	light_source2_1._lightPos = glm::vec4(20.0, 0.0, -12.0, 1.0);
	light_source2_1._ambient_intensity = 0.0;
	light_source2_1._specular_intensity = 0.0;
	light_source2_1._diffuse_intensity = 1.0;
	light_source2_1._attenuation_coeff = 0.02;
	//light_source2_1._cone_angle = 12.0; // in degree
	//light_source2_1._cone_direction = glm::vec3(-1.0, -1.0, 0.0); // this must be aligned with the object and light position.


	GLDirectLightSource  light_source2_2;
	light_source2_2._lightPos = glm::vec4(25.0, 0.0, -18.5, 0.0);
	light_source2_2._ambient_intensity = 0.005;
	light_source2_2._specular_intensity = 1.0;
	light_source2_2._diffuse_intensity = 0.5;
	light_source2_2._attenuation_coeff = 0.02;
	// light_source2._cone_angle = 12.0; // in degree
	// light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.

	GLSpotLightSource  light_source3_1;
	light_source3_1._lightPos = glm::vec4(8.6, 6.5, -4.5, 1.0);
	light_source3_1._ambient_intensity = 0.0;
	light_source3_1._specular_intensity = 0.0;
	light_source3_1._diffuse_intensity =200.0;
	light_source3_1._attenuation_coeff = 0.4;
	light_source3_1._cone_angle = 21.8; // in degree
	light_source3_1._cone_direction = glm::vec3(-0.54, -0.39, -0.088); // this must be aligned with the object and light position.


	GLDirectLightSource  light_source3_2;
	light_source3_2._lightPos = glm::vec4(25.0, 0.0, -4.0, 0.0);
	light_source3_2._ambient_intensity = 0.0;
	light_source3_2._specular_intensity = 1.7;
	light_source3_2._diffuse_intensity = 0.0;
	light_source3_2._attenuation_coeff = 0.02;
	// light_source2._cone_angle = 12.0; // in degree
	// light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.
	
	GLSpotLightSource  light_source3_3;
	light_source3_3._lightPos = glm::vec4(0.0, -10.0, 0.0, 1.0);
	light_source3_3._ambient_intensity = 0.0;
	light_source3_3._specular_intensity = 0.0;
	light_source3_3._diffuse_intensity = 0.0;
	light_source3_3._attenuation_coeff = 0.02;
	light_source3_3._cone_angle = 270.0; // in degree
	light_source3_3._cone_direction = glm::vec3(0.0, -1.0, 0.0); // this must be aligned with the object and light position.

	GLSpotLightSource  light_source4_1;
	light_source4_1._lightPos = glm::vec4(10.0, 18.0,-15.0, 1.0);
	light_source4_1._ambient_intensity = 0.0;
	light_source4_1._specular_intensity = 0.0;
	light_source4_1._diffuse_intensity = 1.7;
	light_source4_1._attenuation_coeff = 0.001;
	light_source4_1._cone_angle = 47.0; // in degree
	light_source4_1._cone_direction = glm::vec3(0.1, -0.7, 0.1); // this must be aligned with the object and light position.


	GLDirectLightSource  light_source4_2;
	light_source4_2._lightPos = glm::vec4(10.0, 1.0, -2.0, 0.0);
	light_source4_2._ambient_intensity = 0.0;
	light_source4_2._specular_intensity = 0.2;
	light_source4_2._diffuse_intensity = 0.1;
	light_source4_2._attenuation_coeff = 0.02;
	// light_source2._cone_angle = 12.0; // in degree
	// light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.

	GLDirectLightSource  light_source4_3;
	light_source4_3._lightPos = glm::vec4(10.0, -5.0, 8.0, 0.0);
	light_source4_3._ambient_intensity = 0.0;
	light_source4_3._specular_intensity = 0.2;
	light_source4_3._diffuse_intensity = 0.1;
	light_source4_3._attenuation_coeff = 0.02;
	// light_source2._cone_angle = 12.0; // in degree
	// light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.

	GLDirectLightSource  light_source4_4;
	light_source4_4._lightPos = glm::vec4(12.0, -10.0, 7.0, 0.0);
	light_source4_4._ambient_intensity = 0.0;
	light_source4_4._specular_intensity = 0.0;
	light_source4_4._diffuse_intensity = 0.7;
	light_source4_4._attenuation_coeff = 0.02;
	//light_source4_4._cone_angle = 6.0; // in degree
	//light_source4_4._cone_direction = glm::vec3(-1.0, 1.0, 0.0); // this must be aligned with the object and light position.
    
	// add the spot light to this apperance object
    apperance->addLightSource(light_source1_1);
    apperance->addLightSource(light_source1_2);

	apperance2->addLightSource(light_source2_1);
	apperance2->addLightSource(light_source2_2);

	apperance3->addLightSource(light_source3_1);
	apperance3->addLightSource(light_source3_2);
	//apperance3->addLightSource(light_source3_3);

	apperance4->addLightSource(light_source4_1);
	apperance4->addLightSource(light_source4_2);
	apperance4->addLightSource(light_source4_3);
	apperance4->addLightSource(light_source4_4);

    GLMaterial material;
    material._diffuse_material = glm::vec3(1.0, 0.0, 0.0);
    material._ambient_material = glm::vec3(1.0, 0.0, 0.0);
    material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material._shininess = 62.0;
    
	GLMaterial material2;
	material2._diffuse_material = glm::vec3(0.0, 0.0, 1.0);
	material2._ambient_material = glm::vec3(0.0, 0.0, 1.0);
	material2._specular_material = glm::vec3(0.0, 0.0, 0.3);
	material2._shininess = 2.0;

	GLMaterial material3;
	material3._diffuse_material = glm::vec3(0.0, 1.0, 0.0);
	material3._ambient_material = glm::vec3(0.0, 1.0, 0.0);
	material3._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material3._shininess = 92.0;

	GLMaterial material4;
	material4._diffuse_material = glm::vec3(0.9, 1.0, 0.2);
	material4._ambient_material = glm::vec3(0.94, 0.98, 0.27);
	material4._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material4._shininess = 100.0;

    apperance->setMaterial(material);
    apperance->finalize();
	apperance2->setMaterial(material2);
	apperance2->finalize();
	apperance3->setMaterial(material3);
	apperance3->finalize();
	apperance4->setMaterial(material4);
	apperance4->finalize();

    GLSphere3D* sphere = new GLSphere3D(0.0, 0.0, 18.0, 4.0, 100, 100);
	GLSphere3D* sphere2 = new GLSphere3D(0.0, 0.0, 6.0, 4.0, 90, 50);
	GLSphere3D* sphere3 = new GLSphere3D(0.0, 0.0, -6.0, 4.0, 400, 350);
	GLSphere3D* sphere4 = new GLSphere3D(0.0, 0.0, -18.0, 4.0, 300, 250);

    sphere->setApperance(*apperance);
    sphere->init();
	sphere2->setApperance(*apperance2);
	sphere2->init();
	sphere3->setApperance(*apperance3);
	sphere3->init();
	sphere4->setApperance(*apperance4);
	sphere4->init();

    
    
  // material._diffuse_material = glm::vec3(1.0, 0.0, 0.2);
   //material._ambient_material = glm::vec3(1.0, 0.0, 0.2);
    //apperance->updateMaterial();
    //light_source1_1._diffuse_intensity = 1.0;
    //apperance->updateLightSources();
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    static const GLfloat clear_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
	//Resolution changed in GLObject.cpp
	SetPerspectiveViewFrustum(0.5f, (float)1366 / (float)720, 0.01f, 100000.0f);
	// This sets the camera to a new location
	SetViewAsLookAt(glm::vec3(50.0f, 0.0f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
   // sphere->enableNormalVectorRenderer();
    
    while(!glfwWindowShouldClose(window))
    {
        
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);

    
        cs->draw();
        
        sphere->draw();
		sphere2->draw();
		sphere3->draw();
		sphere4->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    delete cs;


}

