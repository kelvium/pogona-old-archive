#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include <pogona/Renderer/Vulkan/physicalDevice.h>
#include <pogona/Renderer/VulkanRendererApi.h>

VulkanRendererApiError vulkanCreateDevice(VulkanRendererApi* self);

#endif
