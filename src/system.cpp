#include "system.hpp"

// stdlib
#include <chrono>

using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(16ms);

int System::init()
{
	// Initialise GLFW
	if ( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* video_mode = glfwGetVideoMode(primary_monitor);

	// set and match GLFW window properties to primary monitors video mode 
	glfwWindowHint(GLFW_RED_BITS, video_mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, video_mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, video_mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, video_mode->refreshRate);

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	m_window = glfwCreateWindow( 1024, 768, "The Game", primary_monitor, NULL);
	if ( m_window == NULL )
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1); // vsync

	// initialize GL3W
	// must be done after glfw window context call
	if (gl3w_init()) 
	{
		fprintf(stderr, "failed to initialize OpenGL\n");
		return -1;
	}

	// ----------------------------------------------
	// setting callbacks to member function
	// first pass window and pointer to data (in this case the IO handler instance) we want glfw to know about
	// glfw documentation: http://www.glfw.org/docs/latest/input_guide.html, http://www.glfw.org/docs/latest/window_guide.html
	glfwSetWindowUserPointer(m_window, this);

	// function signature must match below for glfw keypress callback
	// so, we can use a lambda expression that matches it and redirects keypress callbacks to the IO handler (object) we passed as data (pointer to)
	// lambda documentation: https://msdn.microsoft.com/en-ca/library/dd293608.aspx
	auto redirect_event_keypress = [](GLFWwindow* wnd, int _0, int _1, int _2, int _3) 
	{
		// we grab the data we linked to the window, and cast it back to a pointer to the IO handler
		// and redirect the callback data to the IO handler function responsible for input
		((System*)glfwGetWindowUserPointer(wnd))->handle_keypress(wnd, _0, _1, _2, _3);
	};
	// auto key_redirect = [](GLFWwindow* wnd, int _0, int _1, int _2, int _3) { ((World*)glfwGetWindowUserPointer(wnd))->on_key(wnd, _0, _1, _2, _3); };
	// auto cursor_pos_redirect = [](GLFWwindow* wnd, double _0, double _1) { ((System*)glfwGetWindowUserPointer(wnd))->on_mouse_move(wnd, _0, _1); };
	glfwSetKeyCallback(m_window, redirect_event_keypress);
	// glfwSetCursorPosCallback(m_window, cursor_pos_redirect);

	//-------------------------------------------------------------------------
	// Loading music and sounds
	// if (SDL_Init(SDL_INIT_AUDIO) < 0)
	// {
	// 	fprintf(stderr, "Failed to initialize SDL Audio");
	// 	return false;
	// }

	// if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	// {
	// 	fprintf(stderr, "Failed to open audio device");
	// 	return false;
	// }

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
	m_terminate = false;

	game_state current_state;
	game_state previous_state;

	while(!m_terminate) 
	{
		auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		glfwPollEvents();

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
	}
	return 1;
}

void System::terminate()
{
	// ----------------------------
	// terminating OpenGL 
	glfwDestroyWindow(m_window);
	glfwTerminate();
}