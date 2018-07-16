#include "system.hpp"

using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(16ms);

int System::init()
{
	// -------------------
	// initialise GLFW
	if ( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	// get the users primary monitor, we want to know its video mode
	GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* video_mode = glfwGetVideoMode(primary_monitor);

	// set and match GLFW window properties to primary monitors video mode 
	// this will help speed things up a bit, avoids repeatedly converting between glfw window and monitor settings with draw()
	glfwWindowHint(GLFW_RED_BITS, video_mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, video_mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, video_mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, video_mode->refreshRate);

	// further settings
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// create a window and its OpenGL context (with the settings above)
	// we specify the resolution, and by further specifying the primary monitor we can make it full screen at that resolution
	m_window = glfwCreateWindow( 1024, 768, "The Game", primary_monitor, NULL);
	if ( m_window == NULL )
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}

	// we want glfw calls to be made in the context of our window
	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1); // vsync

	// ---------------------
	// initialize GL3W
	// must be done after glfw window context call
	if (gl3w_init()) 
	{
		fprintf(stderr, "failed to initialize OpenGL\n");
		return -1;
	}

	// ----------------------------------------------
	// setting callbacks to member functions
	// first pass window and pointer to data (in this case the IO handler instance) that we want glfw to know are coupled
	// now we can access the data by knowing about the window (see below, glfwGetWindowUserPointer())
	// glfw documentation: http://www.glfw.org/docs/latest/input_guide.html, http://www.glfw.org/docs/latest/window_guide.html
	glfwSetWindowUserPointer(m_window, this);

	// function signature must match below for glfw keypress callback
	// so, we can use a lambda expression that matches it and redirects keypress callbacks to the IO handler (object) we passed as data (pointer to)
	// lambda documentation: https://msdn.microsoft.com/en-ca/library/dd293608.aspx
	auto redirect_event_key = [](GLFWwindow* wnd, int _0, int _1, int _2, int _3) 
	{
		// we grab the data we linked to the window, and cast it back to a pointer to the IO handler
		// and redirect the callback data to the IO handler function responsible for input
		((System*)glfwGetWindowUserPointer(wnd))->handle_keypress(wnd, _0, _1, _2, _3);
	};

	// same strategy for mouse events, keeping in mind the function signature glfw requires for mouse events differs from key events
	auto redirect_event_mousemove = [](GLFWwindow* wnd, double _0, double _1) { ((System*)glfwGetWindowUserPointer(wnd))->handle_mousemove(wnd, _0, _1); };
	auto redirect_event_mouse = [](GLFWwindow* wnd, int _0, int _1, int _2) { ((System*)glfwGetWindowUserPointer(wnd))->handle_mouseinput(wnd, _0, _1, _2); };

	glfwSetKeyCallback(m_window, redirect_event_key);
	glfwSetCursorPosCallback(m_window, redirect_event_mousemove);
	glfwSetMouseButtonCallback(m_window, redirect_event_mouse);

	// -------------------------------------
	// setting window input properties
	// hide the cursor when over the window
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//------------------------------
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
		// auto alpha = (float) lag.count() / timestep.count();
		// auto interpolated_state = interpolate(current_state, previous_state, alpha);

		// render(interpolated_state);
	}
	return 1;
}


bool System::handle_events()
{
	return true;
}
void System::handle_keypress(GLFWwindow *glfw_window, int input_key, int key_scancode, int key_action, int key_modifiers)
{
	switch (input_key)
	{
		case GLFW_KEY_UP:
		m_terminate = true;
		break;
	}
}

void System::handle_mousemove(GLFWwindow *glfw_window, double xpos, double ypos)
{

}

void System::handle_mouseinput(GLFWwindow *glfw_window, int input_button, int button_action, int button_mods)
{

}

void System::terminate()
{
	// ----------------------------
	// terminating OpenGL 
	glfwDestroyWindow(m_window);
	glfwTerminate();
}