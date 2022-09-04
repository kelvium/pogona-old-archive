#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include <pch.h>
#include <pogona/Renderer/VulkanRendererApi.h>
#include <pogona/logger.h>

typedef struct VulkanGlobals {
	VkInstance instance;
} VulkanGlobals;

static VulkanRendererApiError sVulkanCreateInstance(VulkanRendererApi* self)
{
	u32 apiVersion;
	vkEnumerateInstanceVersion(&apiVersion);
	LOGGER_INFO("supported vulkan version: %d.%d.%d\n",
			VK_API_VERSION_MAJOR(apiVersion), VK_API_VERSION_MINOR(apiVersion),
			VK_API_VERSION_PATCH(apiVersion));

	u32 requiredVersion = VK_API_VERSION_1_1;
	if (apiVersion < requiredVersion) {
		LOGGER_ERROR("required vulkan version is not supported: %d < %d\n",
				apiVersion, requiredVersion);
		return VULKAN_RENDERER_REQUIRED_VULKAN_VERSION_IS_NOT_SUPPORTED;
	}

	char applicationNameBuffer[256] = { 0 };
	windowGetTitle(
			self->window, applicationNameBuffer, sizeof(applicationNameBuffer));

	const VkApplicationInfo applicationInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = applicationNameBuffer,
		.applicationVersion = 1, /* TODO: get the real value from somewhere :) */
		.pEngineName = "pogona",
		.engineVersion = 1, /* TODO: get the real value from somewhere :) */
	};

	const VkInstanceCreateInfo instanceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &applicationInfo,
		.enabledExtensionCount = 0,
		.ppEnabledExtensionNames = NULL,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = NULL,
	};

	VkResult result = vkCreateInstance(
			&instanceCreateInfo, NULL, &self->vulkanGlobals->instance);
	if (result != VK_SUCCESS) {
		LOGGER_ERROR("could not create a vulkan instance: %d\n", result);
		return VULKAN_RENDERER_COULD_NOT_CREATE_INSTANCE;
	}
	return VULKAN_RENDERER_API_OK;
}

VulkanRendererApiError vulkanRendererApiCreate(
		VulkanRendererApi* self, Window* window)
{
	self->window = window;
	self->vulkanGlobals = calloc(1, sizeof(VulkanGlobals));

	volkInitialize();

	VulkanRendererApiError error;
	error = sVulkanCreateInstance(self);
	if (error != VULKAN_RENDERER_API_OK) {
		LOGGER_ERROR("could not create an instance: %d\n", error);
		return error;
	}
	volkLoadInstance(self->vulkanGlobals->instance);
	return VULKAN_RENDERER_API_OK;
}

VulkanRendererApiError vulkanRendererApiDestroy(VulkanRendererApi* self)
{
	vkDestroyInstance(self->vulkanGlobals->instance, NULL);

	free(self->vulkanGlobals);
	return VULKAN_RENDERER_API_OK;
}

#endif
