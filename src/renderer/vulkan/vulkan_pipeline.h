/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan.h"

i32 vulkanCreatePipelineLayout(VkPipelineLayout* pipelineLayout);
i32 vulkanCreateGraphicsPipeline(VkPipeline* pipeline, VkPipelineLayout pipelineLayout, VkPipelineCache pipelineCache,
		VkShaderModule vertexShader, VkShaderModule fragmentShader);

#endif
