//http://homepage.ntlworld.com/neal.tringham/OpenGLGameDev/download.html#mipmap2d
//alternative to gluBuild2DMipmaps

#include <iostream>
#include <algorithm>
using namespace std;

/*======================================================================
=====*/
/*  This function is a special version of the GLU function. This
version of  */
/* the function uses the graphic adapters filtering to generate the
different*/
/* levels.  This should make for better quality mipmaps and might even
be    */
/* faster, although speed isn't the point.                             
     */
/*  The function works the same except for a couple of things. First
the call*/
/* will trash your back buffer so this function shouldn't be used
during a   */
/* frame.  Also it is unsure as to how a alpha texture will work out
since   */
/* most drivers still don't do destination alpha.                      
 */
/* So caller beware...                                                 
      
*/
/*======================================================================
=====*/
/* RETURN: 0 is success, non-zero is a GL error type.                  
   
*/
/*======================================================================
=====*/
GLint Build2DMipMapsGL( GLenum target,
                           GLint component,
                           GLsizei width,                          
                           GLsizei height,
                           GLenum format,                          
                           GLenum type,
                           const void *data )
{
  GLint         maxsize,
                viewport[4],
                w, h,
                level, 
                error;
  GLuint        pow2;
  void          *image;

  /* Sanity check. */
  if ( width < 1 || height < 1 )        
    return GLU_INVALID_VALUE;

  /* Round the width to the next lower pow2 if not already a pow2. */
  for( pow2 = 1; pow2 < width; pow2 = pow2 << 1 );
  w = (pow2 == width) ? width : (pow2 << 1);

  /* Round the height to the next lower pow2 if not already a pow2. */
  for( pow2 = 1; pow2 < height; pow2 = pow2 << 1 );
  h = (pow2 == height) ? height : (pow2 << 1);

  /* Clamp to the largest texture size the driver supports. */
  glGetIntegerv( GL_MAX_TEXTURE_SIZE, &maxsize );
  w = min( w, maxsize );
  h = min( h, maxsize );

 
/*======================================================================
========*/
  /* If the original image doesn't have pow2 dimensions then we need to
scale it. */
 
/*======================================================================
========*/
  if ( w != width || h != height ) 
  {
    /*  Allocate memory for the new scaled image. Note that I allocate
the worst*/
    /* case size just to be simple.  This routine shouldn't be used to
scale    */
    /* textures really... I also could have allocated a larger texture
and then */
    /* modify the (s,t) and use this texture to generate the others. 
People    */
    /* should be scaling to pow2 long before run-time.                 
        */
    image = malloc( (w+4) * h * (sizeof(GLfloat)*4) );
    if ( image == NULL ) 
      return GLU_OUT_OF_MEMORY;

    /* Use the OpenGL API to scale it. */
    error = gluScaleImage( format, width, height, type, data, w, h,
type, image );
    if ( error ) 
      return error;
  }
  else 
  {
    /* Use the supplied data. */
    image = (void *)data;
  }

  /*===============================================================*/
  /* Save the current OpenGL state machine to be restored on exit. */
  /*===============================================================*/
  glPushAttrib( GL_ALL_ATTRIB_BITS );

  /* Save the both matrix before we modify. */
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glMatrixMode( GL_PROJECTION );
  glPushMatrix();

  /* Make sure the texture gets drawn without effects. */
  glDisable( GL_ALPHA_TEST );
  glDisable( GL_BLEND );
  glDisable( GL_CULL_FACE );
  glDisable( GL_DEPTH_TEST );
  glDisable( GL_FOG );
  glDisable( GL_LIGHTING );

  glEnable( GL_TEXTURE_2D );
  glReadBuffer( GL_BACK );

 
/*======================================================================
=*/
  /*  Create a texture using the valid image. This texture is used to
draw */
  /* all the other texture levels.                                     
   */
 
/*======================================================================
=*/
  glTexImage2D( target, 0, component, w, h, 0, format, type, image );

  /* Set the texture to do linear filtering. */
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

  /*  If we had to scale the original image then we need to free */
  /* the memory that we allocated to hold it.                    */
  if ( image != data ) 
    free( image );

	//GLboolean v=0;
  GLint* v;

  /* Setup the transformation pipeline for 2D. */
  glLoadIdentity();
  glGetIntegerv( GL_VIEWPORT, v );
  glOrtho( (float)viewport[0], (float)viewport[2], 
           (float)viewport[1], (float)viewport[3], 
           0.0, 1.0 );

 
/**=====================================================================
=======*/
  /* Continue to create a new mipmap level until both of the dimensions
equal 1. */
 
/**=====================================================================
=======*/
  for( level = 1; (w != 1) && (h != 1 ); level++ )
  {
    /* Shift the dimensions to the next level. */
    w = w >> 1;
    h = h >> 1;

    /*  As mipmap filtering is off... we can use the level 0 texture to
*/
    /* draw this level for us so that the cards filtering gets used.   
*/
    glBegin( GL_QUADS );
      glTexCoord2f( 0.0, 0.0 );
      glVertex2i( 0, 0 );

      glTexCoord2f( 1.0, 0.0 );
      glVertex2i( w, 0 );

      glTexCoord2f( 1.0, 1.0 );
      glVertex2i( w, h );

      glTexCoord2f( 0.0, 1.0 );
      glVertex2i( 0, h );
    glEnd();

    /* Read the pixels back into this texture level. */
    glCopyTexImage2D( target, level, component, 0, 0, w, h, 0 );
  }

  /*===================================*/
  /* Restore the OpenGL state machine. */
  /*===================================*/
  glMatrixMode( GL_PROJECTION );
  glPopMatrix();

  glMatrixMode( GL_MODELVIEW );
  glPopMatrix();

  glPopAttrib();

  return 0;
}
