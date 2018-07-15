// Responsible for running threads on main game loop
#include "render.hpp"

// SDL Audio
#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

// GL3W/GLFM OpenGL
#define GL3W_IMPLEMENTATION
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
	void terminate();

	bool handle_events()
	{

	}
	void handle_keypress(GLFWwindow *glfw_window, int input_key, int key_scancode, int key_action, int key_modifiers)
	{
		switch (input_key)
		{
			case GLFW_KEY_UP:
					m_terminate = true;
				break;
			}
	}

	// public members

private:
	struct game_state
	{
		bool state = true;
	};

	// rendering-specific variables
	GLFWwindow* m_window;
	Render render_system;

	// keypress-specific variables
	bool m_terminate;
};
