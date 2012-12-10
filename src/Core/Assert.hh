#ifndef CORE_ASSERT_HH_
#define CORE_ASSERT_HH_

# include <cassert>
# include <iostream>
# include <sstream>
# include <cstdlib>
# include "../Opengl.hh"

# ifdef NDEBUG
#  define ASSERT(X)
#  define ASSERT_MSG(X, MSG)
# else
#  define ASSERT(X)                                                     \
  {                                                                     \
    Core::assertFormat(X, #X, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
  }
#  define ASSERT_MSG(X, MSG)                                            \
  {                                                                     \
    std::ostringstream __assert_msg;                                    \
    __assert_msg << MSG;                                                \
    Core::assertFormat(X, #X, __FILE__, __PRETTY_FUNCTION__,		\
		       __LINE__, __assert_msg.str().c_str());		\
  }
# endif

namespace Core
{
  inline void assertFormat(bool cond,
                           const char* textCond,
                           const char* file,
                           const char* funcname,
                           const int line,
                           const char* msg = 0)
  {
    if (!cond)
    {
      std::ostringstream assertMsg;
      assertMsg << "\nAssertion failed: " << textCond << std::endl
                << "Location: " << file << ":" << line << std::endl
                << "Function: " << funcname << std::endl;
      GLenum errCode = glGetError();
      assertMsg << "Possible OpenGL error code: " << gluErrorString(errCode)
		<< "(" << errCode << ")" << std::endl;
      if (msg)
        assertMsg << "Assert msg: " << msg << std::endl;
      std::cout << assertMsg.str() << std::endl;
      exit(127);
      assert(false);
    }
  }
}

#endif /* ! CORE_ASSERT_HH_*/
