//
//  main.cpp
//  OpenGL4Test
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


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"

// this line tells the compiler to use the namespace std.
// Each object, command without a namespace is assumed to be part of std. 
using namespace std;




static const string vs_string =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrix;                                    \n"
"uniform mat4 viewMatrix;                                           \n"
"uniform mat4 modelMatrix;                                          \n"
"in vec3 in_Position;                                               \n"
"                                                                   \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
"    pass_Color = in_Color;                                         \n"
"}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string  =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";




/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];

unsigned int vboID[4];

/*!
 ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
unsigned int createTriangleStripModel(void)
{
    // use the vertex array object vaoID[0] for this model representation
	float* vertices = new float[160];
	float *colors = new float[160];
	//Used Degenerate vertices, as multiple GL_DRAW() commands were crashing my Graphics Driver
	vertices[0] = -1; vertices[1] = 2; vertices[2] = 0;
	vertices[3] = -1; vertices[4] = 2; vertices[5] = 1;
	vertices[6] = 0; vertices[7] = 2; vertices[8] = 0;
	vertices[9] = 0; vertices[10] = 2; vertices[11] = 1;
	vertices[12] = 0; vertices[13] = 0; vertices[14] = 0;
	vertices[15] = 0; vertices[16] = 0; vertices[17] = 1;
	vertices[18] = 2; vertices[19] = 0; vertices[20] = 0;
	vertices[21] = 2; vertices[22] = 0; vertices[23] = 1;
	vertices[24] = 2; vertices[25] = -1; vertices[26] = 0;
	vertices[27] = 2; vertices[28] = -1; vertices[29] = 1;
	vertices[30] = -1; vertices[31] = -1; vertices[32] = 0;
	vertices[33] = -1; vertices[34] = -1; vertices[35] = 1;
	vertices[36] = -1; vertices[37] = 2; vertices[38] = 0;
	vertices[39] = -1; vertices[40] = 2; vertices[41] = 1; //sides only
	vertices[42] = -1; vertices[43] = 2; vertices[44] = 1; //Degen
	vertices[45] = 0; vertices[46] = 2; vertices[47] = 1;
	vertices[48] = -1; vertices[49] = 0; vertices[50] = 1; 
	vertices[51] = 0; vertices[52] = 0; vertices[53] = 1; 
	vertices[54] = -1; vertices[55] = 0; vertices[56] = 2;
	vertices[57] = 0; vertices[58] = 0; vertices[59] = 2;
	vertices[60] = -1; vertices[61] = -1; vertices[62] = 2;//21
	vertices[63] = 0; vertices[64] = -1; vertices[65] = 2;
	vertices[66] = 0; vertices[67] = -1; vertices[68] = 1;
	vertices[69] = -1; vertices[70] = -1; vertices[71] = 2;
	vertices[72] = -1; vertices[73] = -1; vertices[74] = 1; //Top surface
	vertices[75] = -1; vertices[76] = 0; vertices[77] = 2;
	vertices[78] = -1; vertices[79] = 0; vertices[80] = 1;//27
	vertices[81] = -1; vertices[82] = 0; vertices[83] = 1;//Degen
	vertices[84] = 0; vertices[85] = 0; vertices[86] = 1;//Degen
	vertices[87] = 0; vertices[88] = 0; vertices[89] = 1;
	vertices[90] = 2; vertices[91] = 0; vertices[92] = 1;
	vertices[93] = 0; vertices[94] = 0; vertices[95] = 2;//32
	vertices[96] = 0; vertices[97] = -1; vertices[98] = 2;
	vertices[99] = 2; vertices[100] = 0; vertices[101] = 1;
	vertices[102] = 2; vertices[103] = -1; vertices[104] = 1;
	vertices[105] = 2; vertices[106] = -1; vertices[107] = 1;//Degen
	vertices[108] = 0; vertices[109] = -1; vertices[110] = 2;
	vertices[111] = 0; vertices[112] = -1; vertices[113] = 1;//38
	vertices[114] = 0; vertices[115] = -1; vertices[116] = 1;//Degen
	vertices[117] = 0; vertices[118] = 2; vertices[119] = 0;//Degen
	vertices[120] = 0; vertices[121] = 2; vertices[122] = 0;
	vertices[123] = -1; vertices[124] = 2; vertices[125] = 0;
	vertices[126] = 0; vertices[127] = 0; vertices[128] = 0;
	vertices[129] = -1; vertices[130] = 0; vertices[131] = 0;//44
	vertices[132] = -1; vertices[133] = 0; vertices[134] = 0;//Degen
	vertices[135] = -1; vertices[136] = -1; vertices[137] = 0;
	vertices[138] = 2; vertices[139] = 0; vertices[140] = 0;
	vertices[141] = 2; vertices[142] = -1; vertices[143] = 0;//vertices End
	
	int i;
	for (i = 2; i < 144; i += 3)
	{
		vertices[i] = -1 * vertices[i];
	}

	colors[0] = 0; colors[1] = 0; colors[2] = 0.5;
	colors[3] = 0; colors[4] = 0.5; colors[5] = 0.5;
	colors[6] = 0.5; colors[7] = 0; colors[8] = 0.5;
	colors[9] = 0.5; colors[10] = 0.3; colors[11] = 0.5;
	colors[12] = 0; colors[13] = 0; colors[14] = 0.5;
	colors[15] = 0; colors[16] = 0.5; colors[17] = 0.5;
	colors[18] = 0.5; colors[19] = 0; colors[20] = 0.5;
	colors[21] = 0.5; colors[22] = 0.3; colors[23] = 0.5;
	colors[24] = 0; colors[25] = 0; colors[26] = 0.5;
	colors[27] = 0; colors[28] = 0.5; colors[29] = 0.5;
	colors[30] = 0.5; colors[31] = 0; colors[32] = 0.5;
	colors[33] = 0.5; colors[34] = 0.3; colors[35] = 0.5;
	colors[36] = 0; colors[37] = 0; colors[38] = 0.5;
	colors[39] = 0; colors[40] = 0.5; colors[41] = 0.5;
	colors[42] = 0; colors[43] = 0.5; colors[44] = 0.5;//
	colors[45] = 0.5; colors[46] = 0; colors[47] = 0.5;
	colors[48] = 0.5; colors[49] = 0.3; colors[50] = 0.5;
	colors[51] = 0; colors[52] = 0; colors[53] = 0.5;
	colors[54] = 0; colors[55] = 0.5; colors[56] = 0.5;
	colors[57] = 0.5; colors[58] = 0; colors[59] = 0.5;
	colors[60] = 0.5; colors[61] = 0.3; colors[62] = 0.5;
	colors[63] = 0; colors[64] = 0; colors[65] = 0.5;
	colors[66] = 0; colors[67] = 0.5; colors[68] = 0.5;
	colors[69] = 0.5; colors[70] = 0; colors[71] = 0.5;
	colors[72] = 0.5; colors[73] = 0.3; colors[74] = 0.5;
	colors[75] = 0; colors[76] = 0; colors[77] = 0.5;
	colors[78] = 0; colors[79] = 0.5; colors[80] = 0.5;
	colors[81] = 0; colors[82] = 0.5; colors[83] = 0.5;//
	colors[84] = 0.5; colors[85] = 0; colors[86] = 0.5;//
	colors[87] = 0.5; colors[88] = 0; colors[89] = 0.5;
	colors[90] = 0.5; colors[91] = 0.3; colors[92] = 0.5;
	colors[93] = 0; colors[94] = 0; colors[95] = 0.5;
	colors[96] = 0; colors[97] = 0.5; colors[98] = 0.5;
	colors[99] = 0.5; colors[100] = 0; colors[101] = 0.5;
	colors[102] = 0.5; colors[103] = 0.3; colors[104] = 0.5;
	colors[105] = 0.5; colors[106] = 0.3; colors[107] = 0.5;//
	colors[108] = 0; colors[109] = 0; colors[110] = 0.5;
	colors[111] = 0; colors[112] = 0.5; colors[113] = 0.5;
	colors[114] = 0; colors[115] = 0.5; colors[116] = 0.5;//
	colors[117] = 0.5; colors[118] = 0; colors[119] = 0.5;//
	colors[120] = 0.5; colors[121] = 0; colors[122] = 0.5;
	colors[123] = 0; colors[124] = 0.3; colors[125] = 0.5;
	colors[126] = 0; colors[127] = 0; colors[128] = 0.5;
	colors[129] = 0.5; colors[130] = 0.5; colors[131] = 0.5;
	colors[132] = 0.5; colors[133] = 0.5; colors[134] = 0.5;//
	colors[135] = 0.5; colors[136] = 0; colors[137] = 0.5;
	colors[138] = 0; colors[139] = 0.3; colors[140] = 0.5;
	colors[141] = 0; colors[142] = 0; colors[143] = 0.5;
	

	glGenVertexArrays(2, &vaoID[0]);
	glBindVertexArray(vaoID[0]);


	glGenBuffers(4, vboID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, 160 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, 160 * sizeof(GLfloat), colors, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


    //TODO:
    vaoID[0];
    
    return 1;
}

/*!
 ADD YOUR CODE TO CREATE A MODEL USING PRIMITIVES OF YOUR CHOISE TO THIS FUNCTION
 */
//Triangle model is created because OpenGL 3.3 doesn't support polygon primitive.
unsigned int createTriangleModel(void)
{
    // use the vertex array object vaoID[1] for this model representation
	int v = 300;
	float* vertices = new float[v];
	float *colors = new float[v];
	
	vertices[0] = -1; vertices[1] = 2; vertices[2] = 1;
	vertices[3] = -1; vertices[4] = 2; vertices[5] = 0;
	vertices[6] = 0; vertices[7] = 2; vertices[8] = 1;
	vertices[9] = 0; vertices[10] = 2; vertices[11] = 1;
	vertices[12] = 0; vertices[13] = 2; vertices[14] = 0;
	vertices[15] = -1; vertices[16] = 2; vertices[17] = 0;
	vertices[18] = 0; vertices[19] = 2; vertices[20] = 1;
	vertices[21] = 0; vertices[22] = 2; vertices[23] = 0;
	vertices[24] = 0; vertices[25] = 0; vertices[26] = 0;
	vertices[27] = 0; vertices[28] = 2; vertices[29] = 1;
	vertices[30] = 0; vertices[31] = 0; vertices[32] = 1;
	vertices[33] = 0; vertices[34] = 0; vertices[35] = 0;
	vertices[36] = 0; vertices[37] = 0; vertices[38] = 0;
	vertices[39] = 0; vertices[40] = 0; vertices[41] = 1;
	vertices[42] = 2; vertices[43] = 0; vertices[44] = 0;
	vertices[45] = 2; vertices[46] = 0; vertices[47] = 0;
	vertices[48] = 2; vertices[49] = 0; vertices[50] = 1;
	vertices[51] = 0; vertices[52] = 0; vertices[53] = 1;
	vertices[54] = 0; vertices[55] = 0; vertices[56] = 1;
	vertices[57] = -1; vertices[58] = 0; vertices[59] = 1;
	vertices[60] = -1; vertices[61] = 0; vertices[62] = 2;
	vertices[63] = -1; vertices[64] = 0; vertices[65] = 2;
	vertices[66] = 0; vertices[67] = 0; vertices[68] = 2;
	vertices[69] = 0; vertices[70] = 0; vertices[71] = 1;//24
	vertices[72] = 0; vertices[73] = 0; vertices[74] = 1;
	vertices[75] = 0; vertices[76] = 2; vertices[77] = 1;
	vertices[78] = -1; vertices[79] = 2; vertices[80] = 1;
	vertices[81] = -1; vertices[82] = 2; vertices[83] = 1;
	vertices[84] = -1; vertices[85] = 0; vertices[86] = 1;
	vertices[87] = 0; vertices[88] = 0; vertices[89] = 1;
	vertices[90] = -1; vertices[91] = 0; vertices[92] = 1;
	vertices[93] = -1; vertices[94] = 2; vertices[95] = 1;
	vertices[96] = -1; vertices[97] = 0; vertices[98] = 0;
	vertices[99] = -1; vertices[100] = 0; vertices[101] = 0;
	vertices[102] = -1; vertices[103] = 2; vertices[104] = 0;
	vertices[105] = -1; vertices[106] = 2; vertices[107] = 1;//36
	vertices[108] = -1; vertices[109] = 2; vertices[110] = 0;
	vertices[111] = 0; vertices[112] = 2; vertices[113] = 0;
	vertices[114] = 0; vertices[115] = 0; vertices[116] = 0;
	vertices[117] = 0; vertices[118] = 0; vertices[119] = 0;
	vertices[120] = -1; vertices[121] = 0; vertices[122] = 0;
	vertices[123] = -1; vertices[124] = 2; vertices[125] = 0;//42
	vertices[126] = 2; vertices[127] = 0; vertices[128] = 0;
	vertices[129] = 2; vertices[130] = 0; vertices[131] = 1;
	vertices[132] = 2; vertices[133] = -1; vertices[134] = 0;
	vertices[135] = 2; vertices[136] = -1; vertices[137] = 0;
	vertices[138] = 2; vertices[139] = -1; vertices[140] = 1;
	vertices[141] = 2; vertices[142] = 0; vertices[143] = 1;//48
	vertices[144] = 2; vertices[145] = -1; vertices[146] = 0;
	vertices[147] = -1; vertices[148] = -1; vertices[149] = 0;
	vertices[150] = -1; vertices[151] = -1; vertices[152] = 1;//51
	vertices[153] = -1; vertices[154] = -1; vertices[155] = 1;
	vertices[156] = 2; vertices[157] = -1; vertices[158] = 1;
	vertices[159] = 2; vertices[160] = -1; vertices[161] = 0;//54
	vertices[162] = -1; vertices[163] = 0; vertices[164] = 0;
	vertices[165] = -1; vertices[166] = 0; vertices[167] = 2;
	vertices[168] = -1; vertices[169] = -1; vertices[170] = 2;
	vertices[171] = -1; vertices[172] = -1; vertices[173] = 2;
	vertices[174] = -1; vertices[175] = -1; vertices[176] = 0;
	vertices[177] = -1; vertices[178] = 0; vertices[179] = 0;//60
	vertices[180] = -1; vertices[181] = 0; vertices[182] = 2;
	vertices[183] = -1; vertices[184] = -1; vertices[185] = 2;
	vertices[186] = 0; vertices[187] = 0; vertices[188] = 2;//63
	vertices[189] = 0; vertices[190] = 0; vertices[191] = 2;
	vertices[192] = 0; vertices[193] = -1; vertices[194] = 2;
	vertices[195] = -1; vertices[196] = -1; vertices[197] = 2;//66
	vertices[198] = 0; vertices[199] = 0; vertices[200] = 2;
	vertices[201] = 2; vertices[202] = 0; vertices[203] = 1;
	vertices[204] = 2; vertices[205] = -1; vertices[206] = 1;
	vertices[207] = 2; vertices[208] = -1; vertices[209] = 1;
	vertices[210] = 0; vertices[211] = -1; vertices[212] = 2;
	vertices[213] = 0; vertices[214] = 0; vertices[215] = 2;//72
	vertices[216] = 0; vertices[217] = 0; vertices[218] = 2;
	vertices[219] = 0; vertices[220] = 0; vertices[221] = 1;
	vertices[222] = 2; vertices[223] = 0; vertices[224] = 1;//75
	vertices[225] = 2; vertices[226] = -1; vertices[227] = 0;
	vertices[228] = 2; vertices[229] = 0; vertices[230] = 0;
	vertices[231] = -1; vertices[232] = 0; vertices[233] = 0;
	vertices[234] = -1; vertices[235] = 0; vertices[236] = 0;
	vertices[237] = -1; vertices[238] = -1; vertices[239] = 0;
	vertices[240] = 2; vertices[241] = -1; vertices[242] = 0;//81
	vertices[243] = 2; vertices[244] = -1; vertices[245] = 1;
	vertices[246] = 0; vertices[247] = -1; vertices[248] = 2;
	vertices[249] = 0; vertices[250] = -1; vertices[251] = 1;//84
	vertices[252] = -1; vertices[253] = -1; vertices[254] = 2;
	vertices[255] = 0; vertices[256] = -1; vertices[257] = 2;
	vertices[258] = -1; vertices[259] = -1; vertices[260] = 1;
	vertices[261] = -1; vertices[262] = -1; vertices[263] = 1;
	vertices[264] = -1; vertices[265] = -1; vertices[266] = 2;
	vertices[267] = 0; vertices[268] = -1; vertices[269] = 2;//90




	int i;
	for (i = 1; i < v; i += 3)
	{
		vertices[i] = (vertices[i] + 4); vertices[i + 1] = -1 * vertices[i + 1];
		colors[i - 1] = .7; colors[i] = .134; colors[i + 1] = .134;
		
	}

	glGenVertexArrays(2, &vaoID[1]);
	glBindVertexArray(vaoID[1]);

	glGenBuffers(4, vboID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, v * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, v * sizeof(GLfloat), colors, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
    //TODO:
    vaoID[1];
    
    return 1;
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderTriangleStripModel(void)
{
	glUseProgram(program);
    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[0]);

    glDrawArrays(GL_TRIANGLE_STRIP, 0 , 48 );
	

    // Unbind our Vertex Array Object
    glBindVertexArray(0);
	glUseProgram(0);
}



/*!
 ADD YOUR CODE TO RENDER THE POLYGON MODEL TO THIS FUNCTION
 */
void renderTriangleModel(void)
{
	glUseProgram(program);
    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[1]);
        

	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY POLYGONS YOU HAVE.
	// COMPLETE THE LINE
    // Draw the triangles
    glDrawArrays(GL_TRIANGLES, 0 , 90);

    // Unbind our Vertex Array Object
    glBindVertexArray(0);
	glUseProgram(0);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!
 This function creates the two models
 */
void setupScene(void) {
    
    createTriangleStripModel();
	createTriangleModel();
}




int main(int argc, const char * argv[])
{
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
	// Prepares some defaults
	CoordSystemRenderer* coordinate_system_renderer = new CoordSystemRenderer(10.0);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// The Shader Program starts here
    
    // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
    // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
    static const string vertex_code = vs_string;
    static const char * vs_source = vertex_code.c_str();
    
    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char * fs_source = fragment_code.c_str();
    
    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();
    
    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    
    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    
    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);
    
    //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    // It controls the virtual camera
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    
    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(4.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
    
    
	 //// The Shader Program ends here
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    


    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");
    

    
    // this creates the scene
    setupScene();
    
    int i=0;

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        // this draws the coordinate system
		coordinate_system_renderer->draw();
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This generate the object
        // Enable the shader program
        glUseProgram(program);
        
        // this changes the camera location
        glm::mat4 rotated_view = viewMatrix * GetRotationMatrix();
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader
        

        // This moves the model to the right
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
		//Changed the transformation matrix so that render is better visible in the window


		// This line renders your triangle strip model
        renderTriangleStripModel();
        

        // This moves the model to the left
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        //Changed the transformation matrix so that render is better visible in the window
		// This line renders your Ppolygon model
        renderTriangleModel();
        
        
		// disable the shader program
        glUseProgram(0);


        //// This generate the object
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
	// delete the coordinate system object
	delete coordinate_system_renderer;

    // Program clean up when the window gets closed.
    glDeleteVertexArrays(2, vaoID);
    glDeleteProgram(program);
}

