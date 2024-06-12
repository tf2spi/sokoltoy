#include "../impl.h"
#include <sokol/gfx.h>
#include <sokol/app.h>
#include <sokol/glue.h>
#include <sokol/log.h>

extern const char *vshader;
extern const char *fshader;

static sg_pass_action pass_action;
static sg_bindings bind;
static sg_pipeline pipe;

static void init(void) {
	sg_setup(&(sg_desc){
		.environment = sglue_environment(),
		.logger.func = slog_func,
	});
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,
	};
	pass_action = (sg_pass_action){
		.colors[0] = { SG_LOADACTION_CLEAR, .clear_value={0.0f, 0.0f, 0.0f, 1.0f} },
	};
	bind.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc){
		.data = SG_RANGE(vertices),
	});
	pipe = sg_make_pipeline(&(sg_pipeline_desc){
		.shader = sg_make_shader(&(sg_shader_desc){
			.fs.source = fshader,
			.vs.source = vshader,
		}),
		.layout = {
			.attrs = {
				[0].format = SG_VERTEXFORMAT_FLOAT3,
				[1].format = SG_VERTEXFORMAT_FLOAT4,
			}
		},
	});
}

static void frame(void) {
	sg_begin_pass(&(sg_pass){
		.action = pass_action,
		.swapchain = sglue_swapchain(),
	});
	sg_apply_pipeline(pipe);
	sg_apply_bindings(&bind);
	sg_draw(0, 3, 1);
	sg_end_pass();
	sg_commit();
}

static void cleanup(void) {
	sg_shutdown();
}

sapp_desc sokol_main(int argc, char **argv) {
	return (sapp_desc){
		.init_cb = init,
		.frame_cb = frame,
		.cleanup_cb = cleanup,
		.width = 400,
		.height = 300,
		.window_title = "Triangle!",
		.icon.sokol_default = true,
		.logger.func = slog_func,
	};
}

