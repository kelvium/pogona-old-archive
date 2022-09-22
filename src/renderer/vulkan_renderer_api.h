/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan/vulkan.h"

#include <pogona/window.h>

i32 vulkanRendererApiCreate(Window* window);
i32 vulkanRendererApiDraw();
i32 vulkanRendererApiDestroy();

#endif
