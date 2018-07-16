#include "system.hpp"
#include "common_libs.hpp"

// GL3W
// must be defined here to avoid duplicate symbol errors
#define GL3W_IMPLEMENTATION
#include <gl3w.h>

#include <iostream>

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
	// OK
	int status = 0;

	// System = {RenderService, ...}
	System* system = new System();

	// allocate default-size mem block for services
	if (!system->init()) {
		std::cout << "=== SYSTEM STATUS: failed system init ===" << std::endl;
		std::cout << "exiting..." << std::endl;
		return status;
	}

	// begin main game loop, terminate on quit
	status = system->start();

	// report termination status
	std::cout << "=== SYSTEM STATUS: " << status << " ===" << std::endl;
	std::cout << "exiting..." << std::endl;

	return status;
}