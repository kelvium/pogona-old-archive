#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include <pogona/Renderer/VulkanRendererApi.h>

VulkanRendererApiError vulkanPickPhysicalDevice(VulkanRendererApi* self);
VulkanRendererApiError vulkanPickQueueFamilyPropertiesIndex(VulkanRendererApi* self, u32* pickedQueueFamilyProperties);

#endif
