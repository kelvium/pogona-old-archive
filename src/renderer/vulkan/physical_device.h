#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "../vulkan_renderer_api.h"

VulkanRendererApiError vulkanPickPhysicalDevice(VulkanRendererApi* self);
VulkanRendererApiError vulkanPickQueueFamilyPropertiesIndex(VulkanRendererApi* self, u32* pickedQueueFamilyProperties);

#endif
