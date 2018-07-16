// Responsible for running threads on main game loop
#include "render.hpp"
#include "common_libs.hpp"

// SDL Audio
#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

// GLM Math
#include <glm.hpp>

// stdlib
#include <chrono>

class System
{
public: 	

	// public functions
	System() {}
	int init();
	int start();
	void terminate();

	bool handle_events();
	void handle_keypress(GLFWwindow *glfw_window, int input_key, int key_scancode, int key_action, int key_modifiers);
	void handle_mousemove(GLFWwindow *glfw_window, double xpos, double ypos);
	void handle_mouseinput(GLFWwindow *glfw_window, int input_button, int button_action, int button_mods);

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
