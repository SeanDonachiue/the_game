#include "render.hpp"

// // stlib
// #include <string.h>
// #include <cassert>
// #include <sstream>

// // Same as static in c, local to compilation unit
// namespace
// {
//     namespace
//     {
//         void glfw_err_cb(int error, const char* desc)
//         {
//             fprintf(stderr, "%d: %s", error, desc);
//         }
//     }
// }

// World::World() 
// {
//     // This was previously used in the initialization list of member variables
//     // for the world, which were points and salmon and fish timings. 
//     // Seeding rng with random device
//     // m_rng = std::default_random_engine(std::random_device()());
// }

// World::~World()
// {

// }

// // World initialization
// bool World::init(vec2 screen)
// {
//     //-------------------------------------------------------------------------
//     // GLFW / OGL Initialization
//     // Core Opengl 3.
//     glfwSetErrorCallback(glfw_err_cb);
//     if (!glfwInit())
//     {
//         fprintf(stderr, "Failed to initialize GLFW");
//         return false;
//     }

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
// #if __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif
//     glfwWindowHint(GLFW_RESIZABLE, 0);
//     m_window = glfwCreateWindow((int)screen.x, (int)screen.y, "DungeonJanitor", nullptr, nullptr);
//     if (m_window == nullptr)
//         return false;

//     glfwMakeContextCurrent(m_window);
//     glfwSwapInterval(1); // vsync

//                          // Load OpenGL function pointers
//     gl3w_init();

//     // Setting callbacks to member functions (that's why the redirect is needed)
//     // Input is handled using GLFW, for more info see
//     // http://www.glfw.org/docs/latest/input_guide.html
//     glfwSetWindowUserPointer(m_window, this);
//     auto key_redirect = [](GLFWwindow* wnd, int _0, int _1, int _2, int _3) { ((World*)glfwGetWindowUserPointer(wnd))->on_key(wnd, _0, _1, _2, _3); };
//     auto cursor_pos_redirect = [](GLFWwindow* wnd, double _0, double _1) { ((World*)glfwGetWindowUserPointer(wnd))->on_mouse_move(wnd, _0, _1); };
//     glfwSetKeyCallback(m_window, key_redirect);
//     glfwSetCursorPosCallback(m_window, cursor_pos_redirect);

//     //-------------------------------------------------------------------------
//     // Loading music and sounds

//     /* No need for music at the moment
//     if (SDL_Init(SDL_INIT_AUDIO) < 0)
//     {
//         fprintf(stderr, "Failed to initialize SDL Audio");
//         return false;
//     }

//     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
//     {
//         fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
//         //fprintf(stderr, "Failed to open audio device");
//         return false;
//     }

//     m_background_music = Mix_LoadMUS(audio_path("music.wav"));

//     //test all sound effects for nullptr
//     if (m_background_music == nullptr)
//     {
//         fprintf(stderr, "Failed to load sounds, make sure the data directory is present");
//         return false;
//     }

//     // Playing background music indefinitely
//     Mix_PlayMusic(m_background_music, -1);

//     fprintf(stderr, "Loaded music");
//     */

//     //actually put something like return m_janitor.init();
// }
