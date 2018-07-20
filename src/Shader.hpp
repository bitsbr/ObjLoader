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
  Shader(const char* vertexShaderFile, const char * fragmentShaderFile);
  ~Shader(void);

  void Use(void);
private:

};
#endif/* Shader_hpp */
