#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include <pogona/renderer/vulkan/physical_device.h>
#include <pogona/renderer/vulkan_renderer_api.h>

VulkanRendererApiError vulkanCreateDevice(VulkanRendererApi* self);

#endif
