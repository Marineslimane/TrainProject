#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "draw_scene.hpp"
#include "tools/shaders.hpp"
#include "json.hpp" // to read json file
#include <iostream>
#include <fstream>
using namespace glbasimac;
using namespace STP3D;

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1200;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "Thomas the train";
static float aspectRatio = 1.0f;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

const float CAM_SPEED {2.0f};
const float CAM_ROT_SPEED {5.0f};

/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

void onWindowResized(GLFWwindow* /*window*/, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	
	myEngine.set3DProjection(90.0, aspectRatio, Z_NEAR, Z_FAR);
}

void onKey(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
    //Quitter
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    //Toggle éclairage
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
        lightingEnabled = !lightingEnabled;
	
	//fps
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        float rad = deg2rad(cam_angle);
        float fx = cos(rad);
        float fy = sin(rad);

	switch(key) 
	{
 		case GLFW_KEY_W:
            cam_x += fx * CAM_SPEED;
            cam_y += fy * CAM_SPEED;
            break;
        case GLFW_KEY_S:
            cam_x -= fx * CAM_SPEED;
            cam_y -= fy * CAM_SPEED;
        	break;
        case GLFW_KEY_A:
            cam_angle += CAM_ROT_SPEED;
            break;
        case GLFW_KEY_D:
            cam_angle -= CAM_ROT_SPEED;
            break;
        case GLFW_KEY_SPACE:
            cam_z += CAM_SPEED;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            cam_z -= CAM_SPEED;
            break;
        default:
            break;
	}
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

int main(int argc, char** argv)
{
	//JSON
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <circuit.json>" << std::endl;
    return -1;
    }

    std::string jsonFile = argv[1];
    std::ifstream f(jsonFile);
    if (!f.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir " << jsonFile << std::endl;
        return -1;
    }
    nlohmann::json circuit = nlohmann::json::parse(f);
    std::cerr << "JSON chargé : " << jsonFile << std::endl;

	/* Callback to a function if an error is rised by GLFW */
    GLFWwindow* window;
    if (!glfwInit()) return -1;

    glfwSetErrorCallback(onError);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	
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
        float rad = deg2rad(cam_angle);
        Vector3D pos_camera(cam_x, cam_y, cam_z);
        Vector3D viewed_point(cam_x + cos(rad),cam_y + sin(rad),cam_z );
        Vector3D up_vector(0.0f, 0.0f, 1.0f);
        Matrix4D viewMatrix = Matrix4D::lookAt(pos_camera, viewed_point, up_vector);
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
