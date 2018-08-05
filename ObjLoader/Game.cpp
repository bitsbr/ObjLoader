
//
//  Display.cpp
//  OpenGLMeshLoader
//
//  Created by Rafael Nogueira on 18/07/2018.
//  Copyright � 2018 Rafael Nogueira. All rights reserved.
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

void Game::Run(void)
{
	if (load_Opengl())
	{

		const char *fragmentPath = "/Users/rafael/Dev/ObjLoader/content/shaders/fragmentShader.glsl";
		const char *vertexPath = "/Users/rafael/Dev/ObjLoader/content/shaders/vertexShader.glsl";

        float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
        };
        
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };
        
		shader = new Shader();
		shader->LoadShader(vertexPath, fragmentPath);

		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,  GL_STATIC_DRAW);
        
        
        
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE , 8 * sizeof(float), (void *) (3 * sizeof(float) ) );
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE , 8 * sizeof(float), (void *) (6 * sizeof(float) ) );
        glEnableVertexAttribArray(2);
        
        
        glBindVertexArray(0);
        
        //Load Test texture ;
		
    
        glGenTextures(1, &testTexture);
        glBindTexture(GL_TEXTURE_2D, testTexture);
    
        int width, height , channels;
        
        stbi_set_flip_vertically_on_load(true);
        unsigned char * data = stbi_load("/Users/rafael/Dev/ObjLoader/content/textures/awesomeface.png", &width, &height, &channels, STBI_rgb);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        
        
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        
        stbi_image_free(data);
        

		this->m_Loop();
	}else{
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
	while (SDL_PollEvent(&m_Events))
	{
		switch (m_Events.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (m_Events.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;
			break;
		};
	}
}

void Game::m_Renderer(void)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    shader->Use();
    
    glBindTexture(GL_TEXTURE_2D, testTexture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
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
		this->wnd_Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		this->wnd_Width, this->wnd_Height, SDL_WINDOW_OPENGL);

	m_GLContext = SDL_GL_CreateContext(m_Window);
	glewExperimental = true;
	if (GLEW_OK == glewInit())
	{
		std::cout << "GLEW Initialized" << std::endl;
	}

	if (m_Window != nullptr && m_GLContext != nullptr)
	{
		glViewport(0, 0, this->wnd_Width, this->wnd_Height);
		loadStatus = true;
		isRunning = true;
	}

	return loadStatus;
}

void Game::m_Destroy(void)
{
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_Window);

}
