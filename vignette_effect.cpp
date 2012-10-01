#define GL_GLEXT_PROTOTYPES 1

#include <math.h>
#include <GL/gl.h>
#include <GL/glext.h>

#include "vignette_effect.h"
#include "util.h"

VignetteEffect::VignetteEffect()
	: center(0.5f, 0.5f),
	  radius(0.3f),
	  inner_radius(0.3f)
{
	register_vec2("center", (float *)&center);
	register_float("radius", (float *)&radius);
	register_float("inner_radius", (float *)&inner_radius);
}

std::string VignetteEffect::output_glsl()
{
	return read_file("vignette_effect.glsl");
}

void VignetteEffect::set_uniforms(GLhandleARB glsl_program_num, const std::string &prefix)
{
	Effect::set_uniforms(glsl_program_num, prefix);

	set_uniform_float(glsl_program_num, prefix, "inv_radius", 1.0f / radius);

	Point2D aspect(16.0f / 9.0f, 1.0f);  // FIXME
	set_uniform_vec2(glsl_program_num, prefix, "aspect_correction", (float *)&aspect);
}
