//
//  Display.hpp
//  OpenGLMeshLoader
//
//  Created by Rafael Nogueira on 18/07/2018.
//  COPYRIGHT © 2018 RAFAEL NOGUEIRA. ALL RIGHTS RESERVED.
//

#ifndef GAME_HPP
#define GAME_HPP

#include "Global.hpp"

#include "Shader.hpp"

class Game
{
public:
  Game(void);
  Game(const char* wndTitle,
       int wndWidth, int wndHeight);
  ~Game(void);

  void Run(int argc, const char **argv);

private:
const char *wnd_Title;
  int wnd_Width, wnd_Height;
  bool isRunning;

  SDL_Event m_Events;
  SDL_Window *m_Window ;
  SDL_GLContext m_GLContext;

  void m_Loop(void);
  void m_Input(void);
  void m_Renderer(void);
  void m_Update(float delta);

  //Loading and unloading functions
  bool load_Opengl(void);
  void m_Destroy(void);

};

#endif //Game_hpp
