
//
//  Display.cpp
//  OpenGLMeshLoader
//
//  Created by Rafael Nogueira on 18/07/2018.
//  Copyright © 2018 Rafael Nogueira. All rights reserved.
//

#include "Game.hpp"


Game::Game(const char *wndTitle, int wndWidth, int wndHeight)
{

  this->wnd_Height = wndHeight;
  this->wnd_Width = wndWidth;
   this->wnd_Title = wndTitle;
}

Game::Game(void)
{
  this->wnd_Height = 600;
  this->wnd_Width = 800;
  this->wnd_Title = ".obj loader Rafael";
    
}

Game::~Game(void) { this->m_Destroy(); }

void Game::Run(int argc, const char **argv){
  if (load_Opengl())    {
    std::cout << "Basic Opengl and Window loaded" << std::endl;
    this->m_Loop();
  }

  
  else{
    std::cout << "Failed to create the basic context" << std::endl;
  }
}


void Game::m_Loop(void)
{
  while (isRunning)
    {
      m_Input();
      m_Update(1.0f);
      m_Renderer();
    }

}

void Game::m_Input(void)
{
  while(SDL_PollEvent(&m_Events))
    {
      switch(m_Events.type)
        {
        case SDL_QUIT:
          isRunning = false;
          break;
        case SDL_KEYDOWN:
          if(m_Events.key.keysym.sym == SDLK_ESCAPE)
            isRunning = false;
          break;
            };
    }
}

void Game::m_Renderer(void)
{
  glClearColor(0.3f,1.0f,1.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER);

  
  
  SDL_GL_SwapWindow(this->m_Window);
}

void Game::m_Update(float delta)
{


}


bool Game::load_Opengl(void)
{
  bool loadStatus = false;

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // Maximum Opengl supported in OSX's is 4.1 in the CORE context.. damm apple.
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  m_Window = SDL_CreateWindow(
                              this->wnd_Title,
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              this->wnd_Width, this->wnd_Height, SDL_WINDOW_OPENGL);

  m_GLContext = SDL_GL_CreateContext(m_Window);
  
  if (m_Window != nullptr && m_GLContext != nullptr)
    {
      glewExperimental = true;
      if (GLEW_OK == glewInit())
        {
          std::cout << "GLEW Initialized" << std::endl;

          glEnable(GL_DEPTH_TEST);

	  glViewport(0, 0, this->wnd_Width, this->wnd_Height);
          loadStatus = true;
          isRunning = true;
        }
      else
        {
	  loadStatus = false;
	}
    }

  return loadStatus;
}

void Game::m_Destroy(void)
{
  SDL_Surface *surface;

  
  

}
