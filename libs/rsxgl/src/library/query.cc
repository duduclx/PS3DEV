//-*-C++-*-
// RSXGL - Graphics library for the PS3 GPU.
//
// Copyright (c) 2011 Alexander Betts (alex.betts@gmail.com)
//
// query.cc - OpenGL query objects.

#include "rsxgl_context.h"
#include "query.h"
#include "timestamp.h"

#include <GL3/gl3.h>
#include "error.h"

#if defined(GLAPI)
#undef GLAPI
#endif
#define GLAPI extern "C"

// Manage the RSX report objects:
typedef name_space< RSXGL_MAX_QUERY_OBJECTS, true > rsxgl_query_object_name_space_type;

static rsxgl_query_object_name_space_type &
rsxgl_query_object_name_space()
{
  static rsxgl_query_object_name_space_type name_space;
  return name_space;
}

rsxgl_query_object_index_type
rsxgl_query_object_allocate()
{
  std::pair< rsxgl_query_object_name_space_type::name_type, bool > tmp = rsxgl_query_object_name_space().create_name();
  if(tmp.second) {
    return tmp.first;
  }
  else {
    return RSXGL_MAX_QUERY_OBJECTS;
  }
}

void
rsxgl_query_object_free(const rsxgl_query_object_index_type index)
{
  if(index < RSXGL_MAX_QUERY_OBJECTS) {
    rsxgl_query_object_name_space().destroy_name(index);
  }
}

//
query_t::storage_type & query_t::storage()
{
  return current_object_ctx() -> query_storage();
}

query_t::~query_t()
{
  if(type != RSXGL_MAX_QUERY_TARGETS) {
    
  }
}

static inline void
rsxgl_free_query_object(const GLuint id)
{
  query_t & query = query_t::storage().at(id);

  for(unsigned int i = 0;i < 2;++i) {
    if(query.indices[i] != RSXGL_MAX_QUERY_OBJECTS) {
      rsxgl_query_object_free(query.indices[i]);
      query.indices[i] = RSXGL_MAX_QUERY_OBJECTS;
    }
  }
}

GLAPI void APIENTRY
glGenQueries (GLsizei n, GLuint *ids)
{
  GLsizei count = query_t::storage().create_names(n,ids);

  if(count != n) {
    RSXGL_ERROR_(GL_OUT_OF_MEMORY);
  }

  RSXGL_NOERROR_();
}

GLAPI void APIENTRY
glDeleteQueries (GLsizei n, const GLuint *ids)
{
  struct rsxgl_context_t * ctx = current_ctx();

  for(GLsizei i = 0;i < n;++i,++ids) {
    const GLuint query_name = *ids;

    if(query_name == 0) continue;

    // Free resources used by this object:
    if(query_t::storage().is_object(query_name)) {
      // Block for something?
      query_t & query = query_t::storage().at(query_name);
      if(query.type != RSXGL_MAX_QUERY_TARGETS) {
      }

      // Destroy it:
      query_t::storage().destroy(query_name);
    }
    // It was just a name:
    else if(query_t::storage().is_name(query_name)) {
      query_t::storage().destroy(query_name);
    }
  }

  RSXGL_NOERROR_();
}

GLAPI GLboolean APIENTRY
glIsQuery (GLuint id)
{
  return query_t::storage().is_object(id);
}

static inline uint8_t
rsxgl_query_target(const GLenum target)
{
  switch(target) {
  case GL_SAMPLES_PASSED:
    return RSXGL_QUERY_SAMPLES_PASSED;
  case GL_ANY_SAMPLES_PASSED:
    return RSXGL_QUERY_ANY_SAMPLES_PASSED;
  case GL_PRIMITIVES_GENERATED:
    return RSXGL_QUERY_PRIMITIVES_GENERATED;
  case GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN:
    return RSXGL_QUERY_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN;
  case GL_TIME_ELAPSED:
    return RSXGL_QUERY_TIME_ELAPSED;
  default:
    return RSXGL_MAX_QUERY_TARGETS;
  }
}

GLAPI void APIENTRY
glBeginQuery (GLenum target, GLuint id)
{
  const uint8_t rsx_target = rsxgl_query_target(target);
  if(rsx_target == RSXGL_MAX_QUERY_TARGETS) {
    RSXGL_ERROR_(GL_INVALID_ENUM);
  }

  rsxgl_context_t * ctx = current_ctx();

  if(ctx -> query_binding.is_anything_bound(rsx_target)) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  if(id == 0 || !query_t::storage().is_name(id)) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }
  else if(!query_t::storage().is_object(id)) {
    query_t::storage().create_object(id);
  }
  else {
    rsxgl_free_query_object(id);
  }

  query_t & query = query_t::storage().at(id);

  if(query.type == RSXGL_MAX_QUERY_TARGETS) {
    query.type = rsx_target;
  }
  else if(query.type != rsx_target) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }
  else if(query.status == RSXGL_QUERY_STATUS_ACTIVE) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }
  
  ctx -> query_binding.bind(rsx_target,id);

  query.value = 0;
  query.status = RSXGL_QUERY_STATUS_ACTIVE;
  query.timestamps[0] = rsxgl_timestamp_create(ctx,1);

  //
  gcmContextData * context = ctx -> gcm_context();

  if(query.type == RSXGL_QUERY_SAMPLES_PASSED || query.type == RSXGL_QUERY_ANY_SAMPLES_PASSED) {
    query.indices[0] = rsxgl_query_object_allocate();
    rsxgl_assert(query.indices[0] != RSXGL_MAX_QUERY_OBJECTS);

    rsxgl_query_enable_samples(context,true);
    rsxgl_query_reset_samples(context);

    // this tells glMultiDraw* and glDrawInstanced* functions which report to update as each primitive is drawn:
    if(query.type == RSXGL_QUERY_ANY_SAMPLES_PASSED) {
      ctx -> any_samples_passed_query = query.indices[0];
    }

    rsxgl_query_object_set(context,query.indices[0]);
  }
  else if(query.type == RSXGL_QUERY_TIME_ELAPSED) {
    query.indices[0] = rsxgl_query_object_allocate();
    query.indices[1] = rsxgl_query_object_allocate();
    rsxgl_assert(query.indices[0] != RSXGL_MAX_QUERY_OBJECTS && query.indices[1] != RSXGL_MAX_QUERY_OBJECTS);

    rsxgl_query_object_set(context,query.indices[0]);
  }
  else {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  rsxgl_timestamp_post(ctx,query.timestamps[0]);

  RSXGL_NOERROR_();
}

GLAPI void APIENTRY
glEndQuery (GLenum target)
{
  const uint8_t rsx_target = rsxgl_query_target(target);
  if(rsx_target == RSXGL_MAX_QUERY_TARGETS) {
    RSXGL_ERROR_(GL_INVALID_ENUM);
  }

  rsxgl_context_t * ctx = current_ctx();

  if(!ctx -> query_binding.is_anything_bound(rsx_target)) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  query_t & query = ctx -> query_binding[rsx_target];

  if(query.status != RSXGL_QUERY_STATUS_ACTIVE) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  query.status = RSXGL_QUERY_STATUS_PENDING;
  rsxgl_assert(query.indices[0] != RSXGL_MAX_QUERY_OBJECTS);
  query.timestamps[1] = rsxgl_timestamp_create(ctx,1);

  //
  gcmContextData * context = ctx -> gcm_context();

  if(query.type == RSXGL_QUERY_SAMPLES_PASSED || query.type == RSXGL_QUERY_ANY_SAMPLES_PASSED) {
    rsxgl_query_enable_samples(context,false);

    if(query.type == RSXGL_QUERY_ANY_SAMPLES_PASSED) {
      ctx -> any_samples_passed_query = RSXGL_MAX_QUERY_OBJECTS;
    }

    rsxgl_query_object_set(context,query.indices[0]);
  }
  else if(query.type == RSXGL_QUERY_TIME_ELAPSED) {
    rsxgl_query_object_set(context,query.indices[1]);
  }
  else {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  rsxgl_timestamp_post(ctx,query.timestamps[1]);

  ctx -> query_binding.bind(rsx_target,0);

  RSXGL_NOERROR_();
}

GLAPI void APIENTRY
glQueryCounter (GLuint id, GLenum target)
{
  if(target != GL_TIMESTAMP) {
    RSXGL_ERROR_(GL_INVALID_ENUM);    
  }
  const uint8_t rsx_target = RSXGL_QUERY_TIMESTAMP;

  if(id == 0 || !query_t::storage().is_name(id)) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }
  else if(!query_t::storage().is_object(id)) {
    query_t::storage().create_object(id);
  }
  else {
    rsxgl_free_query_object(id);
  }

  rsxgl_context_t * ctx = current_ctx();

  query_t & query = query_t::storage().at(id);

  if(query.type == RSXGL_MAX_QUERY_TARGETS) {
    query.type = rsx_target;
  }
  else if(query.type != rsx_target) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  query.status = RSXGL_QUERY_STATUS_PENDING;
  query.indices[0] = rsxgl_query_object_allocate();
  rsxgl_assert(query.indices[0] != RSXGL_MAX_QUERY_OBJECTS);
  query.timestamps[0] = rsxgl_timestamp_create(ctx,1);
  rsxgl_timestamp_post(ctx,query.timestamps[0]);

  gcmContextData * context = ctx -> gcm_context();

  rsxgl_query_object_set(context,query.indices[0]);

  RSXGL_NOERROR_();
}

GLAPI void APIENTRY
glGetQueryiv (GLenum target, GLenum pname, GLint *params)
{
  const uint8_t rsx_target = rsxgl_query_target(target);
  if(rsx_target == RSXGL_MAX_QUERY_TARGETS) {
    RSXGL_ERROR_(GL_INVALID_ENUM);
  }

  rsxgl_context_t * ctx = current_ctx();

  if(!ctx -> query_binding.is_anything_bound(rsx_target)) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  // TODO - finish this

  RSXGL_NOERROR_();
}

template< typename Type >
static inline Type
rsxgl_get_query_object_value(rsxgl_context_t * ctx,query_t & query)
{
  rsxgl_assert(query.status == RSXGL_QUERY_STATUS_PENDING || query.status == RSXGL_QUERY_STATUS_CACHED);

  if(query.status == RSXGL_QUERY_STATUS_PENDING) {
    if(query.type == RSXGL_QUERY_SAMPLES_PASSED) {
      rsxgl_assert(query.indices[0] != RSXGL_MAX_QUERY_OBJECTS);

      rsxgl_timestamp_wait(ctx,query.timestamps[1]);
      query.value = rsxgl_query_object_get_value(query.indices[0]);

      rsxgl_query_object_free(query.indices[0]);
      query.indices[0] = RSXGL_MAX_QUERY_OBJECTS;
    }
    else if(query.type == RSXGL_QUERY_ANY_SAMPLES_PASSED) {
      rsxgl_assert(query.indices[0] != RSXGL_MAX_QUERY_OBJECTS);

      uint32_t samples = 0;
      const uint32_t last_timestamp = query.timestamps[1];
      for(uint32_t timestamp = query.timestamps[0];(timestamp <= last_timestamp) && (samples == 0);++timestamp) {
	rsxgl_timestamp_wait(ctx,timestamp);
	samples += rsxgl_query_object_get_value(query.indices[0]);
      }
      query.value = (samples > 0);

      rsxgl_query_object_free(query.indices[0]);
      query.indices[0] = RSXGL_MAX_QUERY_OBJECTS;
    }
    else if(query.type == RSXGL_QUERY_TIME_ELAPSED) {
      rsxgl_assert(query.indices[0] != RSXGL_MAX_QUERY_OBJECTS && query.indices[1] != RSXGL_MAX_QUERY_OBJECTS);      

      rsxgl_timestamp_wait(ctx,query.timestamps[1]);
      query.value = rsxgl_query_object_get_timestamp(query.indices[1]) - rsxgl_query_object_get_timestamp(query.indices[0]);

      rsxgl_query_object_free(query.indices[0]);
      rsxgl_query_object_free(query.indices[1]);
      query.indices[0] = RSXGL_MAX_QUERY_OBJECTS;
      query.indices[1] = RSXGL_MAX_QUERY_OBJECTS;
    }
    else if(query.type == RSXGL_QUERY_TIMESTAMP) {
      rsxgl_timestamp_wait(ctx,query.timestamps[0]);
      query.value = rsxgl_query_object_get_timestamp(query.indices[0]);

      rsxgl_query_object_free(query.indices[0]);
      query.indices[0] = RSXGL_MAX_QUERY_OBJECTS;
    }
    
    query.status = RSXGL_QUERY_STATUS_CACHED;
  }

  return query.value;
}

template< typename Type >
static inline void
rsxgl_get_query_object(const GLuint id, const GLenum pname, Type * params)
{
  if(!query_t::storage().is_object(id)) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  rsxgl_context_t * ctx = current_ctx();

  query_t & query = query_t::storage().at(id);

  if(!(query.status == RSXGL_QUERY_STATUS_PENDING || query.status == RSXGL_QUERY_STATUS_CACHED)) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  if(pname == GL_QUERY_RESULT_AVAILABLE) {
    *params = (query.status == RSXGL_QUERY_STATUS_CACHED) || (rsxgl_timestamp_passed(ctx,query.timestamps[1]));
  }
  else if(pname == GL_QUERY_RESULT) {
    *params = rsxgl_get_query_object_value< Type >(ctx,query);
  }

  RSXGL_NOERROR_();
}

GLAPI void APIENTRY
glGetQueryObjectiv (GLuint id, GLenum pname, GLint *params)
{
  rsxgl_get_query_object(id,pname,params);
}

GLAPI void APIENTRY
glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params)
{
  rsxgl_get_query_object(id,pname,params);
}

GLAPI void APIENTRY
glGetQueryObjecti64v (GLuint id, GLenum pname, GLint64 *params)
{
  rsxgl_get_query_object(id,pname,params);
}

GLAPI void APIENTRY
glGetQueryObjectui64v (GLuint id, GLenum pname, GLuint64 *params)
{
  rsxgl_get_query_object(id,pname,params);
}

#define NV40_CONDITIONAL_RENDER 0x00001e98

GLAPI void APIENTRY
glBeginConditionalRender (GLuint id, GLenum mode)
{
  if(!query_t::storage().is_object(id)) {
    RSXGL_ERROR_(GL_INVALID_VALUE);
  }

  if(!(mode == GL_QUERY_WAIT || mode == GL_QUERY_NO_WAIT || mode == GL_QUERY_BY_REGION_WAIT || mode == GL_QUERY_BY_REGION_NO_WAIT)) {
    RSXGL_ERROR_(GL_INVALID_ENUM);
  }

  rsxgl_context_t * ctx = current_ctx();

  if(ctx -> state.enable.conditional_render_status != RSXGL_CONDITIONAL_RENDER_INACTIVE) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  query_t & query = query_t::storage().at(id);

  if(!(query.type == RSXGL_QUERY_SAMPLES_PASSED || query.type == RSXGL_QUERY_ANY_SAMPLES_PASSED)) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  if(!(query.status == RSXGL_QUERY_STATUS_PENDING || query.status == RSXGL_QUERY_STATUS_CACHED)) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  // 
  if(query.status == RSXGL_QUERY_STATUS_CACHED || mode == GL_QUERY_WAIT || mode == GL_QUERY_BY_REGION_WAIT) {
    ctx -> state.enable.conditional_render_status = rsxgl_get_query_object_value< uint32_t >(ctx,query) != 0 ? RSXGL_CONDITIONAL_RENDER_ACTIVE_WAIT_PASS : RSXGL_CONDITIONAL_RENDER_ACTIVE_WAIT_FAIL;
  }
  else if(mode == GL_QUERY_NO_WAIT || mode == GL_QUERY_BY_REGION_NO_WAIT) {
    ctx -> state.enable.conditional_render_status = RSXGL_CONDITIONAL_RENDER_ACTIVE_NO_WAIT;

    //
    gcmContextData * context = ctx -> gcm_context();

    uint32_t * buffer = gcm_reserve(context,4);

    gcm_emit_wait_for_idle_at(buffer,0,1);
    gcm_emit_at(buffer,1,0);
    
    gcm_emit_method_at(buffer,2,NV40_CONDITIONAL_RENDER,1);
    gcm_emit_at(buffer,3,(2 << 24) | (query.indices[0] << 4));
    
    gcm_finish_n_commands(context,4);
  }

  RSXGL_NOERROR_();
}

GLAPI void APIENTRY
glEndConditionalRender (void)
{
  rsxgl_context_t * ctx = current_ctx();

  if(ctx -> state.enable.conditional_render_status == RSXGL_CONDITIONAL_RENDER_INACTIVE) {
    RSXGL_ERROR_(GL_INVALID_OPERATION);
  }

  if(ctx -> state.enable.conditional_render_status == RSXGL_CONDITIONAL_RENDER_ACTIVE_NO_WAIT) {
    //
    gcmContextData * context = ctx -> gcm_context();

    uint32_t * buffer = gcm_reserve(context,2);
    
    gcm_emit_method_at(buffer,0,NV40_CONDITIONAL_RENDER,1);
    gcm_emit_at(buffer,1,(1 << 24) | (0));

    gcm_finish_n_commands(context,2);
  }

  ctx -> state.enable.conditional_render_status = RSXGL_CONDITIONAL_RENDER_INACTIVE;

  RSXGL_NOERROR_();
}
