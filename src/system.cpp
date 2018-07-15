#include "system.hpp"

// stdlib
#include <chrono>

using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(16ms);

int System::init()
{
	//-------------------------------------------------------------------------
	// GLFW / OGL Initialization
	// Core Opengl 3.
	glfwSetErrorCallback(glfw_err_cb);
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, 0);
	m_window = glfwCreateWindow(500, 500, "The Game", nullptr, nullptr);
	if (m_window == nullptr)
		return false;

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1); // vsync

	// Load OpenGL function pointers
	gl3w_init();

	// Setting callbacks to member functions (that's why the redirect is needed)
	// Input is handled using GLFW, for more info see
	// http://www.glfw.org/docs/latest/input_guide.html
	glfwSetWindowUserPointer(m_window, this);
	auto key_redirect = [](GLFWwindow* wnd, int _0, int _1, int _2, int _3) { ((System*)glfwGetWindowUserPointer(wnd))->on_key(wnd, _0, _1, _2, _3); };
	auto cursor_pos_redirect = [](GLFWwindow* wnd, double _0, double _1) { ((System*)glfwGetWindowUserPointer(wnd))->on_mouse_move(wnd, _0, _1); };
	glfwSetKeyCallback(m_window, key_redirect);
	glfwSetCursorPosCallback(m_window, cursor_pos_redirect);

	//-------------------------------------------------------------------------
	// Loading music and sounds
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		fprintf(stderr, "Failed to initialize SDL Audio");
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		fprintf(stderr, "Failed to open audio device");
		return false;
	}

	// m_background_music = Mix_LoadMUS(audio_path("music.wav"));
	// m_salmon_dead_sound = Mix_LoadWAV(audio_path("salmon_dead.wav"));
	// m_salmon_eat_sound = Mix_LoadWAV(audio_path("salmon_eat.wav"));

	// if (m_background_music == nullptr || m_salmon_dead_sound == nullptr || m_salmon_eat_sound == nullptr)
	// {
	// 	fprintf(stderr, "Failed to load sounds, make sure the data directory is present");
	// 	return false;
	// }

	// Playing background music undefinitely
	// Mix_PlayMusic(m_background_music, -1);
	
	// fprintf(stderr, "Loaded music");

	// m_current_speed = 1.f;

	// return m_salmon.init();
	return true;
}

int System::start()
{
	using clock = std::chrono::high_resolution_clock;
	std::chrono::nanoseconds lag(0ns);
	auto time_start = clock::now();
	bool terminate = false;

	game_state current_state;
	game_state previous_state;

	while(!terminate) 
	{
		auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		// terminate = handle_events();

		// update game logic as lag permits
		while(lag >= timestep) 
		{
			lag -= timestep;
			previous_state = current_state;
	  		// update(&current_state); // update at a fixed rate each time
		}

		// calculate how close or far we are from the next timestep
		auto alpha = (float) lag.count() / timestep.count();
		// auto interpolated_state = interpolate(current_state, previous_state, alpha);

		// render(interpolated_state);
		return 1;
	}
}