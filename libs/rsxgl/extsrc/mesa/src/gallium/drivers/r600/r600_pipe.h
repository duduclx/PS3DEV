/*
 * Copyright 2010 Jerome Glisse <glisse@freedesktop.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHOR(S) AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *      Jerome Glisse
 */
#ifndef R600_PIPE_H
#define R600_PIPE_H

#include "../../winsys/radeon/drm/radeon_winsys.h"

#include "pipe/p_state.h"
#include "pipe/p_screen.h"
#include "pipe/p_context.h"
#include "util/u_math.h"
#include "util/u_slab.h"
#include "util/u_vbuf.h"
#include "r600.h"
#include "r600_public.h"
#include "r600_shader.h"
#include "r600_resource.h"

#define R600_MAX_CONST_BUFFERS 2
#define R600_MAX_CONST_BUFFER_SIZE 4096

#ifdef PIPE_ARCH_BIG_ENDIAN
#define R600_BIG_ENDIAN 1
#else
#define R600_BIG_ENDIAN 0
#endif

enum r600_pipe_state_id {
	R600_PIPE_STATE_BLEND = 0,
	R600_PIPE_STATE_BLEND_COLOR,
	R600_PIPE_STATE_CONFIG,
	R600_PIPE_STATE_SEAMLESS_CUBEMAP,
	R600_PIPE_STATE_CLIP,
	R600_PIPE_STATE_SCISSOR,
	R600_PIPE_STATE_VIEWPORT,
	R600_PIPE_STATE_RASTERIZER,
	R600_PIPE_STATE_VGT,
	R600_PIPE_STATE_FRAMEBUFFER,
	R600_PIPE_STATE_DSA,
	R600_PIPE_STATE_STENCIL_REF,
	R600_PIPE_STATE_PS_SHADER,
	R600_PIPE_STATE_VS_SHADER,
	R600_PIPE_STATE_CONSTANT,
	R600_PIPE_STATE_SAMPLER,
	R600_PIPE_STATE_RESOURCE,
	R600_PIPE_STATE_POLYGON_OFFSET,
	R600_PIPE_STATE_FETCH_SHADER,
	R600_PIPE_NSTATES
};

struct r600_pipe_fences {
	struct r600_resource		*bo;
	unsigned			*data;
	unsigned			next_index;
	/* linked list of preallocated blocks */
	struct list_head		blocks;
	/* linked list of freed fences */
	struct list_head		pool;
	pipe_mutex			mutex;
};

struct r600_screen {
	struct pipe_screen		screen;
	struct radeon_winsys		*ws;
	unsigned			family;
	enum chip_class			chip_class;
	struct radeon_info		info;
	struct r600_tiling_info		tiling_info;
	struct util_slab_mempool	pool_buffers;
	struct r600_pipe_fences		fences;

	unsigned			num_contexts;

	/* for thread-safe write accessing to num_contexts */
	pipe_mutex			mutex_num_contexts;
};

struct r600_pipe_sampler_view {
	struct pipe_sampler_view	base;
	struct r600_pipe_resource_state		state;
};

struct r600_pipe_rasterizer {
	struct r600_pipe_state		rstate;
	boolean				clamp_vertex_color;
	boolean				clamp_fragment_color;
	boolean				flatshade;
	boolean				two_side;
	unsigned			sprite_coord_enable;
	unsigned                        clip_plane_enable;
	float				offset_units;
	float				offset_scale;
};

struct r600_pipe_blend {
	struct r600_pipe_state		rstate;
	unsigned			cb_target_mask;
};

struct r600_pipe_dsa {
	struct r600_pipe_state		rstate;
	unsigned			alpha_ref;
};

struct r600_vertex_element
{
	unsigned			count;
	struct pipe_vertex_element	elements[PIPE_MAX_ATTRIBS];
	struct u_vbuf_elements		*vmgr_elements;
	struct r600_resource		*fetch_shader;
	unsigned			fs_size;
	struct r600_pipe_state		rstate;
	/* if offset is to big for fetch instructio we need to alterate
	 * offset of vertex buffer, record here the offset need to add
	 */
	unsigned			vbuffer_need_offset;
	unsigned			vbuffer_offset[PIPE_MAX_ATTRIBS];
};

struct r600_pipe_shader {
	struct r600_shader		shader;
	struct r600_pipe_state		rstate;
	struct r600_resource		*bo;
	struct r600_resource		*bo_fetch;
	struct r600_vertex_element	vertex_elements;
	struct tgsi_token		*tokens;
	unsigned	sprite_coord_enable;
	struct pipe_stream_output_info	so;
	unsigned			so_strides[4];
};

struct r600_pipe_sampler_state {
	struct r600_pipe_state		rstate;
	boolean seamless_cube_map;
};

/* needed for blitter save */
#define NUM_TEX_UNITS 16

struct r600_textures_info {
	struct r600_pipe_sampler_view	*views[NUM_TEX_UNITS];
	struct r600_pipe_sampler_state	*samplers[NUM_TEX_UNITS];
	unsigned			n_views;
	unsigned			n_samplers;
	bool				samplers_dirty;
	bool				is_array_sampler[NUM_TEX_UNITS];
};

struct r600_fence {
	struct pipe_reference		reference;
	unsigned			index; /* in the shared bo */
	struct r600_resource            *sleep_bo;
	struct list_head		head;
};

#define FENCE_BLOCK_SIZE 16

struct r600_fence_block {
	struct r600_fence		fences[FENCE_BLOCK_SIZE];
	struct list_head		head;
};

#define R600_CONSTANT_ARRAY_SIZE 256
#define R600_RESOURCE_ARRAY_SIZE 160

struct r600_pipe_context {
	struct pipe_context		context;
	struct blitter_context		*blitter;
	enum radeon_family		family;
	enum chip_class			chip_class;
	void				*custom_dsa_flush;
	struct r600_screen		*screen;
	struct radeon_winsys		*ws;
	struct r600_pipe_state		*states[R600_PIPE_NSTATES];
	struct r600_context		ctx;
	struct r600_vertex_element	*vertex_elements;
	struct r600_pipe_resource_state	fs_resource[PIPE_MAX_ATTRIBS];
	struct pipe_framebuffer_state	framebuffer;
	unsigned			cb_target_mask;
	/* for saving when using blitter */
	struct pipe_stencil_ref		stencil_ref;
	struct pipe_viewport_state	viewport;
	struct pipe_clip_state		clip;
	struct r600_pipe_state		config;
	struct r600_pipe_shader 	*ps_shader;
	struct r600_pipe_shader 	*vs_shader;
	struct r600_pipe_state		vs_const_buffer;
	struct r600_pipe_resource_state		vs_const_buffer_resource[R600_MAX_CONST_BUFFERS];
	struct r600_pipe_state		ps_const_buffer;
	struct r600_pipe_resource_state		ps_const_buffer_resource[R600_MAX_CONST_BUFFERS];
	struct r600_pipe_rasterizer	*rasterizer;
	struct r600_pipe_state          vgt;
	struct r600_pipe_state          spi;
	struct pipe_query		*current_render_cond;
	unsigned			current_render_cond_mode;
	struct pipe_query		*saved_render_cond;
	unsigned			saved_render_cond_mode;
	/* shader information */
	boolean				clamp_vertex_color;
	boolean				clamp_fragment_color;
	boolean				two_side;
	unsigned			user_clip_plane_enable;
	unsigned			clip_dist_enable;
	unsigned			sprite_coord_enable;
	boolean				export_16bpc;
	unsigned			alpha_ref;
	boolean				alpha_ref_dirty;
	unsigned			nr_cbufs;
	struct r600_textures_info	vs_samplers;
	struct r600_textures_info	ps_samplers;

	struct u_vbuf			*vbuf_mgr;
	struct util_slab_mempool	pool_transfers;
	boolean				have_depth_texture, have_depth_fb;

	unsigned default_ps_gprs, default_vs_gprs;
};

/* evergreen_state.c */
void evergreen_init_state_functions(struct r600_pipe_context *rctx);
void evergreen_init_config(struct r600_pipe_context *rctx);
void evergreen_pipe_shader_ps(struct pipe_context *ctx, struct r600_pipe_shader *shader);
void evergreen_pipe_shader_vs(struct pipe_context *ctx, struct r600_pipe_shader *shader);
void evergreen_fetch_shader(struct pipe_context *ctx, struct r600_vertex_element *ve);
void *evergreen_create_db_flush_dsa(struct r600_pipe_context *rctx);
void evergreen_polygon_offset_update(struct r600_pipe_context *rctx);
void evergreen_pipe_init_buffer_resource(struct r600_pipe_context *rctx,
					 struct r600_pipe_resource_state *rstate);
void evergreen_pipe_mod_buffer_resource(struct r600_pipe_resource_state *rstate,
					struct r600_resource *rbuffer,
					unsigned offset, unsigned stride,
					enum radeon_bo_usage usage);
boolean evergreen_is_format_supported(struct pipe_screen *screen,
				      enum pipe_format format,
				      enum pipe_texture_target target,
				      unsigned sample_count,
				      unsigned usage);

/* r600_blit.c */
void r600_init_blit_functions(struct r600_pipe_context *rctx);
void r600_blit_uncompress_depth(struct pipe_context *ctx, struct r600_resource_texture *texture);
void r600_blit_push_depth(struct pipe_context *ctx, struct r600_resource_texture *texture);
void r600_flush_depth_textures(struct r600_pipe_context *rctx);

/* r600_buffer.c */
bool r600_init_resource(struct r600_screen *rscreen,
			struct r600_resource *res,
			unsigned size, unsigned alignment,
			unsigned bind, unsigned usage);
struct pipe_resource *r600_buffer_create(struct pipe_screen *screen,
					 const struct pipe_resource *templ);
struct pipe_resource *r600_user_buffer_create(struct pipe_screen *screen,
					      void *ptr, unsigned bytes,
					      unsigned bind);
void r600_upload_index_buffer(struct r600_pipe_context *rctx,
			      struct pipe_index_buffer *ib, unsigned count);


/* r600_pipe.c */
void r600_flush(struct pipe_context *ctx, struct pipe_fence_handle **fence,
		unsigned flags);

/* r600_query.c */
void r600_init_query_functions(struct r600_pipe_context *rctx);

/* r600_resource.c */
void r600_init_context_resource_functions(struct r600_pipe_context *r600);

/* r600_shader.c */
int r600_pipe_shader_create(struct pipe_context *ctx, struct r600_pipe_shader *shader);
void r600_pipe_shader_destroy(struct pipe_context *ctx, struct r600_pipe_shader *shader);
int r600_find_vs_semantic_index(struct r600_shader *vs,
				struct r600_shader *ps, int id);

/* r600_state.c */
void r600_update_sampler_states(struct r600_pipe_context *rctx);
void r600_init_state_functions(struct r600_pipe_context *rctx);
void r600_init_config(struct r600_pipe_context *rctx);
void r600_pipe_shader_ps(struct pipe_context *ctx, struct r600_pipe_shader *shader);
void r600_pipe_shader_vs(struct pipe_context *ctx, struct r600_pipe_shader *shader);
void r600_fetch_shader(struct pipe_context *ctx, struct r600_vertex_element *ve);
void *r600_create_db_flush_dsa(struct r600_pipe_context *rctx);
void r600_polygon_offset_update(struct r600_pipe_context *rctx);
void r600_pipe_init_buffer_resource(struct r600_pipe_context *rctx,
				    struct r600_pipe_resource_state *rstate);
void r600_pipe_mod_buffer_resource(struct r600_pipe_resource_state *rstate,
				   struct r600_resource *rbuffer,
				   unsigned offset, unsigned stride,
				   enum radeon_bo_usage usage);
void r600_adjust_gprs(struct r600_pipe_context *rctx);
boolean r600_is_format_supported(struct pipe_screen *screen,
				 enum pipe_format format,
				 enum pipe_texture_target target,
				 unsigned sample_count,
				 unsigned usage);

/* r600_texture.c */
void r600_init_screen_texture_functions(struct pipe_screen *screen);
void r600_init_surface_functions(struct r600_pipe_context *r600);
uint32_t r600_translate_texformat(struct pipe_screen *screen, enum pipe_format format,
				  const unsigned char *swizzle_view,
				  uint32_t *word4_p, uint32_t *yuv_format_p);
unsigned r600_texture_get_offset(struct r600_resource_texture *rtex,
					unsigned level, unsigned layer);

/* r600_translate.c */
void r600_translate_index_buffer(struct r600_pipe_context *r600,
				 struct pipe_index_buffer *ib,
				 unsigned count);

/* r600_state_common.c */
void r600_set_index_buffer(struct pipe_context *ctx,
			   const struct pipe_index_buffer *ib);
void r600_set_vertex_buffers(struct pipe_context *ctx, unsigned count,
			     const struct pipe_vertex_buffer *buffers);
void *r600_create_vertex_elements(struct pipe_context *ctx,
				  unsigned count,
				  const struct pipe_vertex_element *elements);
void r600_delete_vertex_element(struct pipe_context *ctx, void *state);
void r600_bind_blend_state(struct pipe_context *ctx, void *state);
void r600_bind_dsa_state(struct pipe_context *ctx, void *state);
void r600_bind_rs_state(struct pipe_context *ctx, void *state);
void r600_delete_rs_state(struct pipe_context *ctx, void *state);
void r600_sampler_view_destroy(struct pipe_context *ctx,
			       struct pipe_sampler_view *state);
void r600_delete_state(struct pipe_context *ctx, void *state);
void r600_bind_vertex_elements(struct pipe_context *ctx, void *state);
void *r600_create_shader_state(struct pipe_context *ctx,
			       const struct pipe_shader_state *state);
void r600_bind_ps_shader(struct pipe_context *ctx, void *state);
void r600_bind_vs_shader(struct pipe_context *ctx, void *state);
void r600_delete_ps_shader(struct pipe_context *ctx, void *state);
void r600_delete_vs_shader(struct pipe_context *ctx, void *state);
void r600_set_constant_buffer(struct pipe_context *ctx, uint shader, uint index,
			      struct pipe_resource *buffer);
struct pipe_stream_output_target *
r600_create_so_target(struct pipe_context *ctx,
		      struct pipe_resource *buffer,
		      unsigned buffer_offset,
		      unsigned buffer_size);
void r600_so_target_destroy(struct pipe_context *ctx,
			    struct pipe_stream_output_target *target);
void r600_set_so_targets(struct pipe_context *ctx,
			 unsigned num_targets,
			 struct pipe_stream_output_target **targets,
			 unsigned append_bitmask);


void r600_draw_vbo(struct pipe_context *ctx, const struct pipe_draw_info *info);

/*
 * common helpers
 */
static INLINE u32 S_FIXED(float value, u32 frac_bits)
{
	return value * (1 << frac_bits);
}
#define ALIGN_DIVUP(x, y) (((x) + (y) - 1) / (y))

static inline unsigned r600_tex_aniso_filter(unsigned filter)
{
	if (filter <= 1)   return 0;
	if (filter <= 2)   return 1;
	if (filter <= 4)   return 2;
	if (filter <= 8)   return 3;
	 /* else */        return 4;
}

#endif
