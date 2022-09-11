#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include <pogona/renderer/vulkan_renderer_api.h>

VulkanRendererApiError vulkanCreateInstance(VulkanRendererApi* self);

#endif
