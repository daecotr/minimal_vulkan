#include <cstdlib>
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <glm/glm.hpp>

namespace minvk {

class Exception : public std::exception {
protected:
  std::string message;

public:
  explicit Exception(const std::string &message) : message{message} {}
  const char *what() const noexcept override { return message.c_str(); }
};

} // namespace minvk

int main(int argc, char *argv[]) {
  try {
		glm::mat4 matrix; // For GLM test

		// Init GLFW, handle errors
    if (!glfwInit())
      throw minvk::Exception{"Failed to initialize GLFW"};

    glfwSetErrorCallback([](int error, const char *description) {
      throw minvk::Exception{description};
    });
	
		// Set GLFW window params
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		
		// Create window
    GLFWwindow *window = glfwCreateWindow(512, 512, "", nullptr, nullptr);
    if (!window) {
      throw minvk::Exception{"Failed to create window"};
    }

		// Get available Vulkan layers
		std::cout << "Available layers" << std::endl;
    std::vector<vk::LayerProperties> availableLayers =
        vk::enumerateInstanceLayerProperties();
    for (const auto &layerProperties : availableLayers) {
      std::cout << "- " << layerProperties.layerName << std::endl;
    }

		// Create Vulkan instance
    vk::ApplicationInfo applicationInfo("", 1, "", 1, VK_API_VERSION_1_3);
    vk::InstanceCreateInfo instanceCreateInfo({}, &applicationInfo);
    auto extensions = glfwGetRequiredInstanceExtensions(
        &instanceCreateInfo.enabledExtensionCount);
    instanceCreateInfo.ppEnabledExtensionNames = extensions;
    vk::Instance instance = vk::createInstance(instanceCreateInfo);

		// Create Vulkan surface for GLFW window
    vk::SurfaceKHR surface{};
    auto glfw_surface = VkSurfaceKHR{surface};
    if (glfwCreateWindowSurface(VkInstance{instance}, window, nullptr,
                                &glfw_surface) != VK_SUCCESS)
      throw minvk::Exception{"Failed to create Vulkan surface"};

		// Window cycle
    for (size_t i = 0; (i < 128) && !glfwWindowShouldClose(window); ++i) {
      glfwPollEvents();
    }

		// Close window & terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

		// Destroy Vulkan instance
    instance.destroy();
    
		std::cout << "Okay" << std::endl;
  } catch (minvk::Exception err) {
    std::cout << "Exception: " << err.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
