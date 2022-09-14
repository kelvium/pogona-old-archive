/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "../vulkan_renderer_api.h"
#include "physical_device.h"

i32 vulkanCreateDevice(VulkanRendererApi* self);

#endif
