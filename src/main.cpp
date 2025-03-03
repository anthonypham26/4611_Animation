#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include "shaderClass.h"
#include "Texture.h"

#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

#include <iostream>

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	-1.0f, -1.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	-1.0f,  1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	 1.0f,  1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 	 1.0f, -1.0f  // Lower right corner//     COORDINATES     /        COLORS      /   TexCoord  //
	//-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	//-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	// 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	// 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};



int main()
{
	try 
	{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "Texture Mapping- Step 1", NULL, NULL);
	
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 1000, 1000);

	// Generates Shader object using shaders default.vert and default.frag
	shaderClass shaderProgram("../shaders/default.vert", "../shaders/default.frag");
	if (shaderProgram.ID == 0)
	{
		std::cout << "Failed to initialize shader program" << std::endl;
		glfwTerminate();
		return -1;
	}

	//to add animation to the texture from glsl fragment shader 
	GLuint timeLoc = glGetUniformLocation(shaderProgram.ID, "u_time");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//std::string parentDir = (fs::current_path().fs::path::parent_path()).string(); //relative path thing in order to centralize all the resources
	std::string texPath = "../include/texture/AnthonyMackie.png";

	// Texture
	Texture myPhoto((texPath).c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	myPhoto.texUnit(shaderProgram, "tex0", 0);


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//update the time unifor
		float timeValue = glfwGetTime(); // Gets the current time
		glUniform1f(timeLoc, timeValue);


		// Specify the color of the background
		glClearColor(0.75f, 0.07f, 0.12f, 0.1f);

		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);  // passing the time to the fragment shader 

		// Binds texture so that is appears in rendering
		myPhoto.Bind();

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	myPhoto.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);

	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;

	} catch (int e) {
		std::cerr << "Caught exception: " << e << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Caught std::exception: " << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Caught unknown exception" << std::endl;
	}
}