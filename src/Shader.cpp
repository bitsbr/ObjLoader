
//
//  Shader.cpp
//  OpenGLMeshLoader
//
//  Created by Rafael Nogueira on 19/07/2018.
//  Copyright © 2018 Rafael Nogueira. All rights reserved.
//

#include "Shader.hpp"

Shader::Shader(void)
{
}

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath)
{

  this->LoadShader(vertexShaderPath, fragmentShaderPath);
}

Shader::~Shader(void)
{
}

void Shader::Use()
{
}

void Shader::LoadShader(const char *vertexShaderPath, const char *fragmentShaderPath)
{
  std::string line;

  const char *vertexShaderSrc;
  const char *fragmentShaderSrc;

  std::ifstream vertexFile(vertexShaderPath);
  std::ifstream fragmentFile(fragmentShaderPath);

  std::string vertexReadBuff;
  std::string fragmentReadBuff;

  while (std::getline(vertexFile, line))
  {
    vertexReadBuff += line + "\n";
  }

  vertexShaderSrc = vertexReadBuff.c_str();

  while (std::getline(fragmentFile, line))
  {
    fragmentReadBuff += line + "\n";
  }
  fragmentShaderSrc = fragmentReadBuff.c_str();

  if (fragmentShaderSrc != nullptr)
  {
    std::cout << " Fragment Shader load error << std::endl;
  }
  if (vertexShaderSrc == nullptr)
  {
    std::cout << "Vertex Shader Load error" << std::endl;
  }

  GLuint vertexShader, fragmentShader;

  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
  glCompileShader(vertexShader);

  GLint compile_stats;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compile_stats);
  if (compile_stats != GL_TRUE)
  {
    GLint bufferSize = 1024;
    GLsizei log_length;
    char log[bufferSize];
    glGetShaderInfoLog(vertexShader, bufferSize, &log_length, log);
    std::cout << " vertexLog: " << log << std::endl;
  }

  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compile_stats);
  if (compile_stats != GL_TRUE)  {
    GLint bufferSize = 1024;
    GLsizei log_length;
    char log[bufferSize];
    glGetShaderInfoLog(fragmentShader, bufferSize, &log_length, log);
    std::cout << " FragmentLog: " << log << std::endl;
  }

  this->IDProgram = glCreateProgram();

  glAttachShader(this->IDProgram,  vertexShader);
  glAttachShader(this->IDProgram,  vertexShader);
  glLinkProgram(this->IDProgram);

GLint programLinkStats;

glGetProgramiv(this->IDProgram, GL_LINK_STATUS, &programLinkStats);
if (programLinkStats != GL_TRUE)
{
    GLsizei log_length;
    GLint bufferSize = 1024;
    GLchar log[bufferSize];
    glGetProgramInfoLog(this->IDProgram, bufferSize, &log_length, log);
  
  std::cout << " ShaderProgramLog" << log << std::endl;

}

}
