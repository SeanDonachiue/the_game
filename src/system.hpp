// Responsible for running threads on main game loop
#include "render.hpp"

// SDL Audio
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

// GL3W/GLFM OpenGL
#include <gl3w.h>
#include <GLFW/glfw3.h>

// GLM Math
#include <glm.hpp>

class System
{
public: 	

	// public functions
	System() {}
	int init();
	int start();
	void processing();
	void rendering();

	// public members

private:
	struct game_state
	{
		bool state = true;
	};

	// Window handle
	GLFWwindow* m_window;
};
