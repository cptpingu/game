#ifndef OPENGL_HH_
# define OPENGL_HH_

//#define GLEW_STATIC
//#include <GL/glew.h>

# ifdef _WIN32
#  include <windows.h>
#  include <GL/glut.h>
# endif

# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glext.h>

bool initExtensions();

extern PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
extern PFNGLACTIVETEXTUREARBPROC   glActiveTexture;
extern PFNGLMULTITEXCOORD3IPROC    glMultiTexCoord3i;

#endif /* !OPENGL_HH_ */
