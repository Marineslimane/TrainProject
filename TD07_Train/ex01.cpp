#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "draw_scene.hpp"
#include "tools/shaders.hpp"
#include "json.hpp" // to read json file
#include <iostream>

using namespace glbasimac;
using namespace STP3D;

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1200;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "Thomas the train";
static float aspectRatio = 1.0f;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

void onWindowResized(GLFWwindow* /*window*/, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	std::cerr<<"Setting 3D projection"<<std::endl;
	
	myEngine.set3DProjection(90.0, aspectRatio, Z_NEAR, Z_FAR);
}

void onKey(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
	
	int is_pressed = (action == GLFW_PRESS); 

	switch(key) 
	{
		case GLFW_KEY_ESCAPE :
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;

		// View modes
		case GLFW_KEY_L:
			if (is_pressed) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			break;
		case GLFW_KEY_P:
			if (is_pressed) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

		// Camera 
		case GLFW_KEY_UP :
			angle_phy -= 1.0;
			if (angle_phy < 1.0f) angle_phy = 1.0f; // issue when close to 0 degrees
			break;
		case GLFW_KEY_DOWN :
			angle_phy += 1.0;
			if (angle_phy > 179.0f) angle_phy = 179.0f; // issue when close to 180 degrees
			break;
		case GLFW_KEY_LEFT :
			angle_theta += 1.0;
			break;
		case GLFW_KEY_RIGHT :
			angle_theta -= 1.0;
			break;
		case GLFW_KEY_R : // zoom in
			dist_zoom = dist_zoom * 0.9;
			break;
		case GLFW_KEY_T : // zoom out 
			dist_zoom = dist_zoom * 1.1;
			break;
		default: std::cerr<<"Key isn't defined"<<key<<std::endl;
	}
}

void onMouseButton(GLFWwindow* window, int button, int action, int /*mods*/)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout<<"Pressed in "<<xpos<<" "<<ypos<<std::endl;
	}
}

int main(int /*argc*/, char** /*argv*/)
{
	/* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	std::cout<<"Loading GL extension"<<std::endl;
	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, onMouseButton);

	std::cout<<"Engine init"<<std::endl;
	myEngine.mode2D = false; // deactivating 2D so 3D mode can be used
	myEngine.initGL();
	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);
	CHECK_GL;

	initScene();
	double elapsedTime{0.0};

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render begins here */
		glClearColor(0.67f,0.84f,0.9f,0.0f); // color of the background, currently  : light blue

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // reinitializes scene 
		glEnable(GL_DEPTH_TEST); // z-buffer activated (depth)

		/* Fix camera position */
		myEngine.mvMatrixStack.loadIdentity();
		
		// spherical coordinates : 
		Vector3D pos_camera =
			Vector3D(dist_zoom * cos(deg2rad(angle_theta)) * sin(deg2rad(angle_phy)),
					dist_zoom * sin(deg2rad(angle_theta)) * sin(deg2rad(angle_phy)),
					dist_zoom * cos(deg2rad(angle_phy)));

		Vector3D viewed_point = Vector3D(0.0,0.0,0.0);
		Vector3D up_vector = Vector3D(0.0,0.0,1.0);
		Matrix4D viewMatrix = Matrix4D::lookAt(pos_camera,viewed_point,up_vector);
		myEngine.setViewMatrix(viewMatrix);
		myEngine.updateMvMatrix();

		drawScene(); // draws objects 
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		while(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
			elapsedTime = glfwGetTime() - startTime;
		}
	}

	glfwTerminate();
	return 0;
}