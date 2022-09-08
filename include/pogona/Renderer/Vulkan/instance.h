#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include <pogona/Renderer/VulkanRendererApi.h>

VulkanRendererApiError vulkanCreateInstance(VulkanRendererApi* self);

#endif
