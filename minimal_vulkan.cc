#include <cstdlib>
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

int main(int argc, char *argv[]) {
	std::cout << argv[0] << std::endl;
	return EXIT_SUCCESS;
}
