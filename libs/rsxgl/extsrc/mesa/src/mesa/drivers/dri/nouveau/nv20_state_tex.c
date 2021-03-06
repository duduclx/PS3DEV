/*
 * Copyright (C) 2009 Francisco Jerez.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "nouveau_driver.h"
#include "nouveau_context.h"
#include "nouveau_gldefs.h"
#include "nouveau_texture.h"
#include "nv20_3d.xml.h"
#include "nouveau_util.h"
#include "nv20_driver.h"

void
nv20_emit_tex_gen(struct gl_context *ctx, int emit)
{
	const int i = emit - NOUVEAU_STATE_TEX_GEN0;
	struct nouveau_context *nctx = to_nouveau_context(ctx);
	struct nouveau_channel *chan = context_chan(ctx);
	struct nouveau_grobj *kelvin = context_eng3d(ctx);
	struct gl_texture_unit *unit = &ctx->Texture.Unit[i];
	int j;

	for (j = 0; j < 4; j++) {
		if (nctx->fallback == HWTNL && (unit->TexGenEnabled & 1 << j)) {
			struct gl_texgen *coord = get_texgen_coord(unit, j);
			float *k = get_texgen_coeff(coord);

			if (k) {
				BEGIN_RING(chan, kelvin,
					   NV20_3D_TEX_GEN_COEFF(i, j), 4);
				OUT_RINGp(chan, k, 4);
			}

			BEGIN_RING(chan, kelvin, NV20_3D_TEX_GEN_MODE(i, j), 1);
			OUT_RING(chan, nvgl_texgen_mode(coord->Mode));

		} else {
			BEGIN_RING(chan, kelvin, NV20_3D_TEX_GEN_MODE(i, j), 1);
			OUT_RING(chan, 0);
		}
	}
}

void
nv20_emit_tex_mat(struct gl_context *ctx, int emit)
{
	const int i = emit - NOUVEAU_STATE_TEX_MAT0;
	struct nouveau_context *nctx = to_nouveau_context(ctx);
	struct nouveau_channel *chan = context_chan(ctx);
	struct nouveau_grobj *kelvin = context_eng3d(ctx);

	if (nctx->fallback == HWTNL &&
	    (ctx->Texture._TexMatEnabled & 1 << i)) {
		BEGIN_RING(chan, kelvin, NV20_3D_TEX_MATRIX_ENABLE(i), 1);
		OUT_RING(chan, 1);

		BEGIN_RING(chan, kelvin, NV20_3D_TEX_MATRIX(i,0), 16);
		OUT_RINGm(chan, ctx->TextureMatrixStack[i].Top->m);

	} else {
		BEGIN_RING(chan, kelvin, NV20_3D_TEX_MATRIX_ENABLE(i), 1);
		OUT_RING(chan, 0);
	}
}

static uint32_t
get_tex_format_pot(struct gl_texture_image *ti)
{
	switch (ti->TexFormat) {
	case MESA_FORMAT_ARGB8888:
		return NV20_3D_TEX_FORMAT_FORMAT_A8R8G8B8;

	case MESA_FORMAT_ARGB1555:
		return NV20_3D_TEX_FORMAT_FORMAT_A1R5G5B5;

	case MESA_FORMAT_ARGB4444:
		return NV20_3D_TEX_FORMAT_FORMAT_A4R4G4B4;

	case MESA_FORMAT_XRGB8888:
		return NV20_3D_TEX_FORMAT_FORMAT_X8R8G8B8;

	case MESA_FORMAT_RGB565:
		return NV20_3D_TEX_FORMAT_FORMAT_R5G6B5;

	case MESA_FORMAT_A8:
	case MESA_FORMAT_I8:
		return NV20_3D_TEX_FORMAT_FORMAT_I8;

	case MESA_FORMAT_L8:
		return NV20_3D_TEX_FORMAT_FORMAT_L8;

	default:
		assert(0);
	}
}

static uint32_t
get_tex_format_rect(struct gl_texture_image *ti)
{
	switch (ti->TexFormat) {
	case MESA_FORMAT_ARGB8888:
		return NV20_3D_TEX_FORMAT_FORMAT_A8R8G8B8_RECT;

	case MESA_FORMAT_ARGB1555:
		return NV20_3D_TEX_FORMAT_FORMAT_A1R5G5B5_RECT;

	case MESA_FORMAT_ARGB4444:
		return NV20_3D_TEX_FORMAT_FORMAT_A4R4G4B4_RECT;

	case MESA_FORMAT_XRGB8888:
		return NV20_3D_TEX_FORMAT_FORMAT_R8G8B8_RECT;

	case MESA_FORMAT_RGB565:
		return NV20_3D_TEX_FORMAT_FORMAT_R5G6B5_RECT;

	case MESA_FORMAT_L8:
		return NV20_3D_TEX_FORMAT_FORMAT_L8_RECT;

	case MESA_FORMAT_A8:
	case MESA_FORMAT_I8:
		return NV20_3D_TEX_FORMAT_FORMAT_I8_RECT;

	default:
		assert(0);
	}
}

void
nv20_emit_tex_obj(struct gl_context *ctx, int emit)
{
	const int i = emit - NOUVEAU_STATE_TEX_OBJ0;
	struct nouveau_channel *chan = context_chan(ctx);
	struct nouveau_grobj *kelvin = context_eng3d(ctx);
	struct nouveau_bo_context *bctx = context_bctx_i(ctx, TEXTURE, i);
	const int bo_flags = NOUVEAU_BO_RD | NOUVEAU_BO_GART | NOUVEAU_BO_VRAM;
	struct gl_texture_object *t;
	struct nouveau_surface *s;
	struct gl_texture_image *ti;
	uint32_t tx_format, tx_filter, tx_wrap, tx_enable;

	if (!ctx->Texture.Unit[i]._ReallyEnabled) {
		BEGIN_RING(chan, kelvin, NV20_3D_TEX_ENABLE(i), 1);
		OUT_RING(chan, 0);

		context_dirty(ctx, TEX_SHADER);
		return;
	}

	t = ctx->Texture.Unit[i]._Current;
	s = &to_nouveau_texture(t)->surfaces[t->BaseLevel];
	ti = t->Image[0][t->BaseLevel];

	if (!nouveau_texture_validate(ctx, t))
		return;

	/* Recompute the texturing registers. */
	tx_format = ti->DepthLog2 << 28
		| ti->HeightLog2 << 24
		| ti->WidthLog2 << 20
		| NV20_3D_TEX_FORMAT_DIMS_2D
		| NV20_3D_TEX_FORMAT_NO_BORDER
		| 1 << 16;

	tx_wrap = nvgl_wrap_mode(t->Sampler.WrapR) << 16
		| nvgl_wrap_mode(t->Sampler.WrapT) << 8
		| nvgl_wrap_mode(t->Sampler.WrapS) << 0;

	tx_filter = nvgl_filter_mode(t->Sampler.MagFilter) << 24
		| nvgl_filter_mode(t->Sampler.MinFilter) << 16
		| 2 << 12;

	tx_enable = NV20_3D_TEX_ENABLE_ENABLE
		| log2i(t->Sampler.MaxAnisotropy) << 4;

	if (t->Target == GL_TEXTURE_RECTANGLE) {
		BEGIN_RING(chan, kelvin, NV20_3D_TEX_NPOT_PITCH(i), 1);
		OUT_RING(chan, s->pitch << 16);
		BEGIN_RING(chan, kelvin, NV20_3D_TEX_NPOT_SIZE(i), 1);
		OUT_RING(chan, s->width << 16 | s->height);

		tx_format |= get_tex_format_rect(ti);
	} else {
		tx_format |= get_tex_format_pot(ti);
	}

	if (t->Sampler.MinFilter != GL_NEAREST &&
	    t->Sampler.MinFilter != GL_LINEAR) {
		int lod_min = t->Sampler.MinLod;
		int lod_max = MIN2(t->Sampler.MaxLod, t->_MaxLambda);
		int lod_bias = t->Sampler.LodBias
			+ ctx->Texture.Unit[i].LodBias;

		lod_max = CLAMP(lod_max, 0, 15);
		lod_min = CLAMP(lod_min, 0, 15);
		lod_bias = CLAMP(lod_bias, 0, 15);

		tx_format |= NV20_3D_TEX_FORMAT_MIPMAP;
		tx_filter |= lod_bias << 8;
		tx_enable |= lod_min << 26
			| lod_max << 14;
	}

	/* Write it to the hardware. */
	nouveau_bo_mark(bctx, kelvin, NV20_3D_TEX_FORMAT(i),
			s->bo, tx_format, 0,
			NV20_3D_TEX_FORMAT_DMA0,
			NV20_3D_TEX_FORMAT_DMA1,
			bo_flags | NOUVEAU_BO_OR);

	nouveau_bo_markl(bctx, kelvin, NV20_3D_TEX_OFFSET(i),
			 s->bo, s->offset, bo_flags);

	BEGIN_RING(chan, kelvin, NV20_3D_TEX_WRAP(i), 1);
	OUT_RING(chan, tx_wrap);

	BEGIN_RING(chan, kelvin, NV20_3D_TEX_FILTER(i), 1);
	OUT_RING(chan, tx_filter);

	BEGIN_RING(chan, kelvin, NV20_3D_TEX_ENABLE(i), 1);
	OUT_RING(chan, tx_enable);

	context_dirty(ctx, TEX_SHADER);
}

void
nv20_emit_tex_shader(struct gl_context *ctx, int emit)
{
	struct nouveau_channel *chan = context_chan(ctx);
	struct nouveau_grobj *kelvin = context_eng3d(ctx);
	uint32_t tx_shader_op = 0;
	int i;

	for (i = 0; i < NV20_TEXTURE_UNITS; i++) {
		if (!ctx->Texture.Unit[i]._ReallyEnabled)
			continue;

		tx_shader_op |= NV20_3D_TEX_SHADER_OP_TX0_TEXTURE_2D << 5 * i;
	}

	BEGIN_RING(chan, kelvin, NV20_3D_TEX_SHADER_OP, 1);
	OUT_RING(chan, tx_shader_op);
}
