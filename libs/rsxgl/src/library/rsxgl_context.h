//-*-C-*-

#ifndef rsxgl_context_H
#define rsxgl_context_H

#include "rsxgl_assert.h"
#include "gcm.h"
#include "egl_types.h"
#include "rsxgl_object_context.h"
#include "arena.h"
#include "buffer.h"
#include "state.h"
#include "attribs.h"
#include "uniforms.h"
#include "textures.h"
#include "program.h"
#include "compiler_context.h"
#include "framebuffer.h"
#include "sync.h"
#include "query.h"

#include "bit_set.h"

#include "pipe/p_context.h"

#include <stddef.h>

struct rsxgl_context_t {
  rsxegl_context_t base;

private:

  rsxgl_object_context_t * m_object_context;
  pipe_context * m_pctx;
  compiler_context_t * m_compiler_context;

public:

  state_t state;

  memory_arena_t::binding_type arena_binding;
  buffer_t::binding_type buffer_binding;

  union {
    uint8_t all;
    struct {
      uint8_t draw_framebuffer:1, read_framebuffer:1, program:1;
    } parts;
  } invalid;

  bit_set< RSXGL_MAX_VERTEX_ATTRIBS > invalid_attribs;
  attribs_t::binding_type attribs_binding;

  texture_t::binding_type::size_type active_texture;
  texture_t::binding_bitfield_type invalid_textures;
  sampler_t::binding_bitfield_type invalid_samplers;
  texture_t::binding_type texture_binding;
  sampler_t::binding_type sampler_binding;

  renderbuffer_t::binding_type renderbuffer_binding;
  framebuffer_t::binding_type framebuffer_binding;

  query_t::binding_type query_binding;
  rsxgl_query_object_index_type any_samples_passed_query;
  
  program_t::binding_type program_binding;
  program_t::texture_assignments_bitfield_type invalid_texture_assignments;

  // Used by glFinish():
  uint32_t ref;

  rsxgl_sync_object_index_type timestamp_sync;

  // Next timestamp to be given out when draw functions are initiated.
  // Should be initialized to 1:
  uint32_t next_timestamp;

  // The last timestamp that was posted to the command stream:
  uint32_t last_timestamp;

  // Cached copy of the current timestamp on the GPU.
  // Should be initialized to 0:
  uint32_t cached_timestamp;

  rsxgl_context_t(const struct rsxegl_config_t *,gcmContextData *,struct pipe_screen *,struct rsxgl_object_context_t *);
  ~rsxgl_context_t();

  inline
  gcmContextData * gcm_context() {
    rsxgl_assert(base.gcm_context != 0);
    return base.gcm_context;
  }

  inline
  rsxgl_object_context_t * object_context() {
    rsxgl_assert(m_object_context != 0);
    return m_object_context;
  }

  inline
  struct pipe_screen * screen() {
    rsxgl_assert(base.screen != 0);
    return base.screen;
  }

  inline
  struct pipe_context * pctx() {
    rsxgl_assert(m_pctx != 0);
    return m_pctx;
  }

  inline
  compiler_context_t * compiler_context() {
    if(m_compiler_context == 0) {
      m_compiler_context = new compiler_context_t(pctx());
    }
    rsxgl_assert(m_compiler_context != 0);
    return m_compiler_context;
  }

  static void egl_callback(rsxegl_context_t *,const uint8_t);
  static void timestamp_overflow(void *);
};

extern rsxgl_context_t * rsxgl_ctx;

static inline rsxgl_context_t *
current_ctx()
{
  assert(rsxgl_ctx != 0);
  return rsxgl_ctx;
}

static inline rsxgl_object_context_t *
current_object_ctx()
{
  assert(rsxgl_ctx != 0);
  return rsxgl_ctx -> object_context();
}

uint32_t rsxgl_timestamp_create(rsxgl_context_t *,const uint32_t);
void rsxgl_timestamp_wait(rsxgl_context_t *,const uint32_t);
bool rsxgl_timestamp_passed(rsxgl_context_t *,const uint32_t);
void rsxgl_timestamp_post(rsxgl_context_t *,const uint32_t);

#endif
