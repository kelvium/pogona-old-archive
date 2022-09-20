/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan.h"

#include <pogona/types.h>

typedef struct {
	u8* data;
	usize dataSize;
} VulkanShaderData;

i32 vulkanShaderDataRead(VulkanShaderData* shaderData, const char* shaderPath);
i32 vulkanShaderDataDestroy(VulkanShaderData* shaderData);
i32 vulkanCreateShaderModule(VkShaderModule* shaderModule, VulkanShaderData* shaderData);

#endif
