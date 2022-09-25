/*
 * Copyright (c) 2022, Nikita Romanyuk <kelvium@yahoo.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <config.h>

#ifdef POGONA_VULKAN_SUPPORT

#include "vulkan_core.h"
#include "vulkan_shader.h"

#include <pch.h>

i32 vulkanShaderDataRead(VulkanShaderData* shaderData, const char* shaderPath)
{
	FILE* file = fopen(shaderPath, "rb");
	if (!file) {
		LOGGER_ERROR("could not open shader file `%s`\n", shaderPath);
		return -1;
	}

	fseek(file, 0, SEEK_END);
	shaderData->dataSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	shaderData->data = malloc(shaderData->dataSize);
	/* TODO: on linux: maybe mmap() instead of reading the whole file? */
	/* is it efficient to pass nmemb=1 and size=dataSize ? */
	fread(shaderData->data, shaderData->dataSize, 1, file);
	if (ferror(file) != 0 || feof(file) != 0) {
		LOGGER_ERROR("could not read shader `%s` data\n", shaderPath);
		fclose(file);
		return 1;
	}

	fclose(file);
	return 0;
}

i32 vulkanShaderDataDestroy(VulkanShaderData* shaderData)
{
	free(shaderData->data);
	return 0;
}

i32 vulkanCreateShaderModule(VkShaderModule* shaderModule, VulkanShaderData* shaderData)
{
	assert(shaderData->dataSize % sizeof(u32) == 0);

	VkShaderModuleCreateInfo shaderModuleCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pCode = (const u32*) shaderData->data,
		.codeSize = shaderData->dataSize,
	};
	PVK_VERIFY(vkCreateShaderModule(gVulkanCore.device, &shaderModuleCreateInfo, NULL, shaderModule));
	return 0;
}

#endif
