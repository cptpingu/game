#ifndef OPENGL_HH_
# define OPENGL_HH_

# ifdef _WIN32
#  include <windows.h>
#  include <GL/glut.h>
# endif

# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glext.h>

bool initExtensions();

# ifdef WIN32
extern PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
extern PFNGLACTIVETEXTUREARBPROC   glActiveTexture;
extern PFNGLMULTITEXCOORD3IPROC    glMultiTexCoord3i;
# endif

#endif /* !OPENGL_HH_ */
