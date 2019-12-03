#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <vector>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#include "Entity.h"
#include "Map.h"
#include "Util.h"
#include "Scene.h"
#include "Menu.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

GLuint fontTextureID;

Mix_Music* music;
Mix_Chunk* jump;

Scene *currentScene;
Scene *sceneList[4];
Menu *menu;
Level1 *level1;
Level2 *level2;
Level3 *level3;
int currLives = 4;

void SwitchToScene(Scene *scene) {
	currLives = currentScene->state.player.lives;
    currentScene = scene;
    currentScene->Initialize(currLives);
}

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Stellar Stella", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
//    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
//    music = Mix_LoadMUS("backgroundmusic.wav");
//    jump = Mix_LoadWAV("jump2.wav");
//    Mix_VolumeChunk(jump, MIX_MAX_VOLUME * 4);
//    Mix_PlayMusic(music, -1);
    
    fontTextureID = Util::LoadTexture("font.png");
    
    sceneList[0] = new Menu();
    sceneList[1] = new Level1();
    sceneList[2] = new Level2();
    sceneList[3] = new Level3();
	currentScene = sceneList[0];
	currentScene->Initialize(currLives);
    
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    program.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glUseProgram(program.programID);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.2f, 0.5f, 0.4f, 1.0f);
}

void ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                gameIsRunning = false;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_RETURN:
						if (currentScene->state.player.lives == 4) {
							currentScene->state.nextLevel = 1;
						}
                }
                break;
        }
    }
    
    currentScene->state.player.velocity.x = 0;
    currentScene->state.player.velocity.y = 0;
    
    // Check for pressed/held keys below
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if (keys[SDL_SCANCODE_A])
    {
		if (currentScene->state.player.position.x > 0.25) {
			currentScene->state.player.velocity.x = -3.0f;
		}
    }
    else if  (keys[SDL_SCANCODE_D])
    {
		if (currentScene->state.player.position.x < 14.75) {
			currentScene->state.player.velocity.x = 3.0f;
		}
    }
    else if  (keys[SDL_SCANCODE_W])
    {
        if (currentScene->state.player.position.y < -0.5) {
            currentScene->state.player.velocity.y = 3.0f;
        }
    }
    else if  (keys[SDL_SCANCODE_S])
    {
        if (currentScene->state.player.position.y > -17) {
            currentScene->state.player.velocity.y = -3.0f;
        }
    }
}

#define FIXED_TIMESTEP 0.0166666f
float lastTicks = 0;
float accumulator = 0.0f;

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    
    deltaTime += accumulator;
    if (deltaTime < FIXED_TIMESTEP) {
        accumulator = deltaTime;
        return;
    }
    
    while (deltaTime >= FIXED_TIMESTEP) {

        currentScene->Update(FIXED_TIMESTEP);
        deltaTime -= FIXED_TIMESTEP;
    }
    
    accumulator = deltaTime;

    viewMatrix = glm::mat4(1.0f);
    if (currentScene->state.player.position.x > 5 && currentScene->state.player.position.x < 10) {
        viewMatrix = glm::translate(viewMatrix,
                                    glm::vec3(-currentScene->state.player.position.x, 3.75, 0));
    } else if (currentScene->state.player.position.x > 10) {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-10, 3.75, 0));
    } else {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-5, 3.75, 0));
    }
    if (currentScene->state.player.position.y > -13.75 && currentScene->state.player.position.y < -3.75) {
        viewMatrix = glm::translate(viewMatrix,
                                    glm::vec3(0, -currentScene->state.player.position.y - 3.75, 0));
    } else if (currentScene->state.player.position.y < -13.75) {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 10, 0));
    }
    else {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(0, 0, 0));
    }
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    program.SetViewMatrix(viewMatrix);
    
    currentScene->Render(&program);
    
//    Util::DrawText(&program, fontTextureID, "Hello!", 1.0f, -0.5f,
//                   glm::vec3(0, 0, 0));
    
    SDL_GL_SwapWindow(displayWindow);
}

void Shutdown() {
//    Mix_FreeMusic(music);
//    Mix_FreeChunk(jump);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();
    
    while (gameIsRunning) {
        if (currentScene->state.nextLevel >= 0) SwitchToScene(sceneList[currentScene->state.nextLevel]);
        ProcessInput();
        Update();
        Render();
    }
    
    Shutdown();
    return 0;
}
