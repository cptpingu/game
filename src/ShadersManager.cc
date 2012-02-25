#include "ShadersManager.hh"

#include <iostream>
#include <cassert>
#include <cstdio>

namespace
{
  const char* loadSource(const char* filename)
  {
    FILE* fp = fopen(filename,"rb");
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buff = new char[len + 1];
    fread(buff, len, 1, fp);
    buff[len] = 0;
    fclose(fp);

    return buff;
  }

  GLuint loadShader(GLenum type, const char* filename)
  {
    GLuint shader = glCreateShader(type);
    if (shader == 0)
      return 0;

    const char* src = loadSource(filename);
    if (!src)
    {
      glDeleteShader(shader);
      return 0;
    }

    glShaderSource(shader, 1, static_cast<const GLchar**>(&src), 0);
    glCompileShader(shader);
    delete[] src;

    GLint compile_status = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE)
    {
      GLsizei logsize = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);

      char* log = new char[logsize + 1];
      glGetShaderInfoLog(shader, logsize, &logsize, log);
      std::cerr << "Unable to compile shader '" << filename << "' :\n" << log;

      delete[] log;
      glDeleteShader(shader);
      return 0;
    }

    return shader;
  }
} // namespace

ShadersManager::ShadersManager()
{
}

ShadersManager::~ShadersManager()
{
  clear();
}

void
ShadersManager::load(const std::string& name,
                     const std::string& vertexShader,
                     const std::string& fragmentShader)
{
  GLuint vert = loadShader(GL_VERTEX_SHADER, vertexShader.c_str());
  if (!vert)
    return;
  GLuint frag = loadShader(GL_FRAGMENT_SHADER, fragmentShader.c_str());
  if (!frag)
    return;

  GLuint prog = glCreateProgram();
  glAttachShader(prog, vert);
  glAttachShader(prog, frag);
  glLinkProgram(prog);

  _programs[name] = prog;
}

void
ShadersManager::enable(const std::string& name) const
{
  auto found = _programs.find(name);
  assert(found != _programs.cend() && "Shaders not found !");
  glUseProgram(found->second);
}

void
ShadersManager::disable() const
{
  glUseProgram(0);
}

void
ShadersManager::clear()
{
  auto end = _programs.cend();
  for (auto it = _programs.cbegin(); it != end; ++it)
    glDeleteProgram(it->second);
  _programs.clear();
}
