#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "../vulkan_renderer_api.h"
#include "physical_device.h"

VulkanRendererApiError vulkanCreateDevice(VulkanRendererApi* self);

#endif
