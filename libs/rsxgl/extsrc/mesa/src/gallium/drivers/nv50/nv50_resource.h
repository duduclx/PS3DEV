
#ifndef __NV50_RESOURCE_H__
#define __NV50_RESOURCE_H__

#include "util/u_transfer.h"
#include "util/u_double_list.h"
#define NOUVEAU_NVC0
#include "nouveau/nouveau_winsys.h"
#include "nouveau/nouveau_buffer.h"
#undef NOUVEAU_NVC0

#ifndef __NVC0_RESOURCE_H__ /* make sure we don't use these in nvc0: */

void
nv50_init_resource_functions(struct pipe_context *pcontext);

void
nv50_screen_init_resource_functions(struct pipe_screen *pscreen);


#define NV50_TILE_SHIFT_X(m) 6
#define NV50_TILE_SHIFT_Y(m) ((((m) >> 0) & 0xf) + 2)
#define NV50_TILE_SHIFT_Z(m) ((((m) >> 4) & 0xf) + 0)

#define NV50_TILE_SIZE_X(m) 64
#define NV50_TILE_SIZE_Y(m) ( 4 << (((m) >> 0) & 0xf))
#define NV50_TILE_SIZE_Z(m) ( 1 << (((m) >> 4) & 0xf))

#define NV50_TILE_SIZE_2D(m) (NV50_TILE_SIZE_X(m) << NV50_TILE_SHIFT_Y(m))

#define NV50_TILE_SIZE(m) (NV50_TILE_SIZE_2D(m) << NV50_TILE_SHIFT_Z(m))

#endif /* __NVC0_RESOURCE_H__ */

uint32_t
nvc0_tex_choose_tile_dims(unsigned nx, unsigned ny, unsigned nz);


struct nv50_miptree_level {
   uint32_t offset;
   uint32_t pitch;
   uint32_t tile_mode;
};

#define NV50_MAX_TEXTURE_LEVELS 16

struct nv50_miptree {
   struct nv04_resource base;
   struct nv50_miptree_level level[NV50_MAX_TEXTURE_LEVELS];
   uint32_t total_size;
   uint32_t layer_stride;
   boolean layout_3d; /* TRUE if layer count varies with mip level */
   uint8_t ms_x;      /* log2 of number of samples in x/y dimension */
   uint8_t ms_y;
   uint8_t ms_mode;
};

static INLINE struct nv50_miptree *
nv50_miptree(struct pipe_resource *pt)
{
   return (struct nv50_miptree *)pt;
}

/* Internal functions:
 */
boolean
nv50_miptree_init_layout_linear(struct nv50_miptree *mt);

struct pipe_resource *
nv50_miptree_create(struct pipe_screen *pscreen,
                    const struct pipe_resource *tmp);

void
nv50_miptree_destroy(struct pipe_screen *pscreen, struct pipe_resource *pt);

struct pipe_resource *
nv50_miptree_from_handle(struct pipe_screen *pscreen,
                         const struct pipe_resource *template,
                         struct winsys_handle *whandle);

boolean
nv50_miptree_get_handle(struct pipe_screen *pscreen,
                        struct pipe_resource *pt,
                        struct winsys_handle *whandle);

struct nv50_surface {
   struct pipe_surface base;
   uint32_t offset;
   uint32_t width;
   uint16_t height;
   uint16_t depth;
};

static INLINE struct nv50_surface *
nv50_surface(struct pipe_surface *ps)
{
   return (struct nv50_surface *)ps;
}

#ifndef __NVC0_RESOURCE_H__

unsigned
nv50_mt_zslice_offset(const struct nv50_miptree *mt, unsigned l, unsigned z);

struct pipe_surface *
nv50_miptree_surface_new(struct pipe_context *,
                         struct pipe_resource *,
                         const struct pipe_surface *templ);

struct pipe_transfer *
nv50_miptree_transfer_new(struct pipe_context *pcontext,
                          struct pipe_resource *pt,
                          unsigned level,
                          unsigned usage,
                          const struct pipe_box *box);
void
nv50_miptree_transfer_del(struct pipe_context *pcontext,
                          struct pipe_transfer *ptx);
void *
nv50_miptree_transfer_map(struct pipe_context *pcontext,
                          struct pipe_transfer *ptx);
void
nv50_miptree_transfer_unmap(struct pipe_context *pcontext,
                            struct pipe_transfer *ptx);

#endif /* __NVC0_RESOURCE_H__ */

struct nv50_surface *
nv50_surface_from_miptree(struct nv50_miptree *mt,
                          const struct pipe_surface *templ);

struct pipe_surface *
nv50_surface_from_buffer(struct pipe_context *pipe,
                         struct pipe_resource *pt,
                         const struct pipe_surface *templ);

void
nv50_surface_destroy(struct pipe_context *, struct pipe_surface *);

#endif /* __NV50_RESOURCE_H__ */
