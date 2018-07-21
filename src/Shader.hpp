//
//  Shader.hpp
//  OpenGLMeshLoader
//
//  Created by Rafael Nogueira on 19/07/2018.
//  Copyright © 2018 Rafael Nogueira. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>

class Shader
{
public:
  Shader(void);
  Shader(const char* vertexShaderSrc, const char * fragmentShaderSrc);

  ~Shader(void);

  void Use(void);
  void LoadShader(const char * vertexShaderSrc, const char *fragmentShaderSrc);
private:
  unsigned int ID;
  unsigned int FragmentShader;
  unsigned int VertexShader;
  
};
#endif/* Shader_hpp */
