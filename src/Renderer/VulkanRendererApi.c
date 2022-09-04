#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include <pch.h>
#include <pogona/Renderer/VulkanRendererApi.h>
#include <pogona/logger.h>

typedef struct VulkanGlobals {
	VkInstance instance;
	VkPhysicalDevice physicalDevice;
	VkDevice device;
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
		return VULKAN_RENDERER_API_REQUIRED_VULKAN_VERSION_IS_NOT_SUPPORTED;
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
		return VULKAN_RENDERER_API_COULD_NOT_CREATE_INSTANCE;
	}
	return VULKAN_RENDERER_API_OK;
}

static VulkanRendererApiError sVulkanPickPhysicalDevice(VulkanRendererApi* self)
{
	VkResult result;

	// get physical device group count
	u32 physicalDeviceGroupsCount = 0;
	result = vkEnumeratePhysicalDeviceGroups(
			self->vulkanGlobals->instance, &physicalDeviceGroupsCount, NULL);
	if (result != VK_SUCCESS) {
		LOGGER_ERROR("could not enumerate physical device groups: %d\n", result);
		return VULKAN_RENDERER_API_COULD_NOT_PICK_PHYSICAL_DEVICE;
	}

	if (physicalDeviceGroupsCount == 0) {
		LOGGER_ERROR("no physical devices groups\n");
		return VULKAN_RENDERER_API_NO_PHYSICAL_DEVICE_GROUPS;
	}

	// get physical device group properties
	VkPhysicalDeviceGroupProperties* physicalDeviceGroupsProperties = calloc(
			physicalDeviceGroupsCount, sizeof(VkPhysicalDeviceGroupProperties));
	result = vkEnumeratePhysicalDeviceGroups(self->vulkanGlobals->instance,
			&physicalDeviceGroupsCount, physicalDeviceGroupsProperties);
	if (result != VK_SUCCESS) {
		LOGGER_ERROR("could not enumerate physical device groups: %d\n", result);
		return VULKAN_RENDERER_API_COULD_NOT_PICK_PHYSICAL_DEVICE;
	}

	VkPhysicalDevice fallbackPhysicalDevice = NULL;
	for (u32 i = 0; i < physicalDeviceGroupsCount; i++) {
		VkPhysicalDeviceGroupProperties physicalDeviceGroupProperties
				= physicalDeviceGroupsProperties[i];

		LOGGER_TRACE("physical device group properties %d:\n", i);
		LOGGER_TRACE(" physical devices count: %d\n",
				physicalDeviceGroupProperties.physicalDeviceCount);
		for (u32 j = 0; j < physicalDeviceGroupProperties.physicalDeviceCount;
				 j++) {
			VkPhysicalDevice physicalDevice
					= physicalDeviceGroupProperties.physicalDevices[j];

			VkPhysicalDeviceProperties physicalDeviceProperties;
			vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

			LOGGER_TRACE(" physical device %d:\n", j);
			LOGGER_TRACE("   deviceName: %s\n", physicalDeviceProperties.deviceName);
			LOGGER_TRACE("   api version: %d.%d.%d\n",
					VK_API_VERSION_MAJOR(physicalDeviceProperties.apiVersion),
					VK_API_VERSION_MINOR(physicalDeviceProperties.apiVersion),
					VK_VERSION_PATCH(physicalDeviceProperties.apiVersion));

			if (physicalDeviceProperties.deviceType
					== VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
				self->vulkanGlobals->physicalDevice = physicalDevice;
				LOGGER_INFO(
						"picked a discrete gpu: %s\n", physicalDeviceProperties.deviceName);
			} else if (!fallbackPhysicalDevice) {
				fallbackPhysicalDevice = physicalDevice;
				LOGGER_INFO("picked %s as the fallback physical device\n",
						physicalDeviceProperties.deviceName);
			}
		}
	}

	if (!self->vulkanGlobals->physicalDevice && fallbackPhysicalDevice) {
		self->vulkanGlobals->physicalDevice = fallbackPhysicalDevice;
		LOGGER_INFO("picked the fallback physical device\n");
	}

	free(physicalDeviceGroupsProperties);
	return VULKAN_RENDERER_API_OK;
}

static VulkanRendererApiError sVulkanPickQueueFamilyPropertiesIndex(
		VulkanRendererApi* self, u32* pickedQueueFamilyPropertiesIndex)
{
	// get queue family property count
	u32 queueFamilyPropertyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(
			self->vulkanGlobals->physicalDevice, &queueFamilyPropertyCount, NULL);

	if (queueFamilyPropertyCount == 0) {
		LOGGER_ERROR("no queue family properties\n");
		return VULKAN_RENDERER_API_NO_QUEUE_FAMILY_PROPERTIES;
	}

	// get queue family properties
	VkQueueFamilyProperties* queueFamilyPropertiesArray
			= calloc(queueFamilyPropertyCount, sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(self->vulkanGlobals->physicalDevice,
			&queueFamilyPropertyCount, queueFamilyPropertiesArray);

	bool picked = false;
	for (u32 i = 0; i < queueFamilyPropertyCount; i++) {
		VkQueueFamilyProperties queueFamilyProperties
				= queueFamilyPropertiesArray[i];

		bool supportsGraphics
				= queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT;

		LOGGER_TRACE("queue family properties %d:\n", i);
		LOGGER_TRACE(" queue count: %d\n", queueFamilyProperties.queueCount);
		LOGGER_TRACE(
				" supports graphics: %s\n", supportsGraphics ? "true" : "false");

		if (supportsGraphics) {
			*pickedQueueFamilyPropertiesIndex = i;
			picked = true;
		}
	}

	free(queueFamilyPropertiesArray);
	if (!picked)
		return VULKAN_RENDERER_API_NO_QUEUE_WITH_GRAPHICS_BIT;
	LOGGER_TRACE("picked queue family properties index %d\n",
			*pickedQueueFamilyPropertiesIndex);
	return VULKAN_RENDERER_API_OK;
}

static VulkanRendererApiError sVulkanCreateDevice(VulkanRendererApi* self)
{
	VulkanRendererApiError error;

	u32 pickedQueueFamilyPropertiesIndex;
	error = sVulkanPickQueueFamilyPropertiesIndex(
			self, &pickedQueueFamilyPropertiesIndex);
	if (error != VULKAN_RENDERER_API_OK) {
		LOGGER_ERROR("could not pick queue family properties: %d\n", error);
		return error;
	}

	float queuePriorities[] = { 1.0 };
	VkDeviceQueueCreateInfo deviceQueueCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.queueCount = 1,
		.queueFamilyIndex = pickedQueueFamilyPropertiesIndex,
		.pQueuePriorities = queuePriorities,
	};

	VkDeviceCreateInfo deviceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pQueueCreateInfos = &deviceQueueCreateInfo,
		.queueCreateInfoCount = 1,
		.enabledExtensionCount = 0,
		.ppEnabledExtensionNames = NULL,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = NULL,
		.pEnabledFeatures = NULL,
	};

	VkResult result;
	result = vkCreateDevice(self->vulkanGlobals->physicalDevice,
			&deviceCreateInfo, NULL, &self->vulkanGlobals->device);
	if (result != VK_SUCCESS) {
		LOGGER_ERROR("could not create device: %d\n", result);
		return VULKAN_RENDERER_API_COULD_NOT_CREATE_DEVICE;
	}
	LOGGER_TRACE("created a device\n");
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

	error = sVulkanPickPhysicalDevice(self);
	if (error != VULKAN_RENDERER_API_OK) {
		LOGGER_ERROR("could not pick a physical device: %d\n", error);
		return error;
	}

	error = sVulkanCreateDevice(self);
	if (error != VULKAN_RENDERER_API_OK) {
		LOGGER_ERROR("could not create a device: %d\n", error);
		return error;
	}
	return VULKAN_RENDERER_API_OK;
}

VulkanRendererApiError vulkanRendererApiDestroy(VulkanRendererApi* self)
{
	vkDestroyDevice(self->vulkanGlobals->device, NULL);
	LOGGER_TRACE("destroyed the device\n");

	vkDestroyInstance(self->vulkanGlobals->instance, NULL);
	LOGGER_TRACE("destroyed the instance\n");

	free(self->vulkanGlobals);
	return VULKAN_RENDERER_API_OK;
}

#endif
