#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>
#include <vector>
extern "C"
{
#include "GLShaderConverter.h"
#include "core/memory/pool_allocator.h"
}
const char *ConvertShader(const uint32_t *src,size_t filesize)
{
    std::vector<uint32_t> test(src, src + filesize);
	
    // Read SPIR-V from disk or similar.
	spirv_cross::CompilerGLSL glsl(test);

	// The SPIR-V is now parsed, and we can perform reflection on it.
	spirv_cross::ShaderResources resources = glsl.get_shader_resources();
	// Get all sampled images in the shader.
	for (auto &resource : resources.sampled_images)
	{
		unsigned set = glsl.get_decoration(resource.id, spv::DecorationDescriptorSet);
		unsigned binding = glsl.get_decoration(resource.id, spv::DecorationBinding);
		printf("Image %s at set = %u, binding = %u\n", resource.name.c_str(), set, binding);

		// Modify the decoration to prepare it for GLSL.
		glsl.unset_decoration(resource.id, spv::DecorationDescriptorSet);

		// Some arbitrary remapping if we want.
		glsl.set_decoration(resource.id, spv::DecorationBinding, set * 16 + binding);
	}

	// Set some options.
	spirv_cross::CompilerGLSL::Options options;
	options.version = 100;
	options.es = true;
	glsl.set_common_options(options);

	// Compile to GLSL, ready to give to GL driver.
	std::string source = glsl.compile();
	char *buf = (char*)csMalloc(source.length() + 1);
	strcpy(buf,source.c_str());
	return buf;
}