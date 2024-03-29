#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <vector>
#include <SDL.h>
#include "SDL_opengl.h"
#include "SDL_image.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Entity.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

#define PLATFORM_COUNT 16

struct GameState {
  Entity player;
  Entity* platforms = new Entity[PLATFORM_COUNT];
};

GameState state;

GLuint fontTextureID;
int cols = 16;
int rows = 16;

GLuint LoadTexture(const char* filePath) {
  int w, h, n;
  unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);
  
  if (image == NULL) {
    std::cout << "Unable to load image. Make sure the path is correct\n";
    assert(false);
  }
  
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  stbi_image_free(image);
  return textureID;
}

void Initialize() {
  SDL_Init(SDL_INIT_VIDEO);
  displayWindow = SDL_CreateWindow("Lunar Lander", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
  SDL_GL_MakeCurrent(displayWindow, context);
  
#ifdef _WINDOWS
  glewInit();
#endif
  
  glViewport(0, 0, 640, 480);
  
  program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
  
  state.player.entityType = PLAYER;
  state.player.isStatic = false;
  state.player.position = glm::vec3(0,3,0);
  state.player.acceleration = glm::vec3(0.0,-0.2,0.0);
  state.player.textureID = LoadTexture("lunarmodule.png");
  
  fontTextureID = LoadTexture("font1.png");
  
  GLuint tileTextureID1 = LoadTexture("moontile1.png");
  GLuint tileTextureID2 = LoadTexture("moontile2.png");
  
  state.platforms[0].textureID = tileTextureID1;
  state.platforms[0].position = glm::vec3(2.5,-3.25,0);
  state.platforms[0].entityType = LANDING;
  
  state.platforms[1].textureID = tileTextureID1;
  state.platforms[1].position = glm::vec3(1.5,-3.25,0);
  state.platforms[1].entityType = LANDING;
  
  state.platforms[2].textureID = tileTextureID1;
  state.platforms[2].position = glm::vec3(0.5,-3.25,0);
  state.platforms[2].entityType = LANDING;
  
  state.platforms[3].textureID = tileTextureID2;
  state.platforms[3].position = glm::vec3(-4.5,1.25,0);
  
  state.platforms[4].textureID = tileTextureID2;
  state.platforms[4].position = glm::vec3(-3.5,1.25,0);
  
  state.platforms[5].textureID = tileTextureID2;
  state.platforms[5].position = glm::vec3(-4.5,1.25,0);
  
  state.platforms[6].textureID = tileTextureID2;
  state.platforms[6].position = glm::vec3(4.5,2.25,0);
  
  state.platforms[7].textureID = tileTextureID2;
  state.platforms[7].position = glm::vec3(4.5,3.25,0);
  
  state.platforms[8].textureID = tileTextureID2;
  state.platforms[8].position = glm::vec3(4.5,1.25,0);
  
  state.platforms[9].textureID = tileTextureID2;
  state.platforms[9].position = glm::vec3(3.5,1.25,0);
  
  state.platforms[10].textureID = tileTextureID2;
  state.platforms[10].position = glm::vec3(2.5,1.25,0);
  
  state.platforms[11].textureID = tileTextureID2;
  state.platforms[11].position = glm::vec3(1.5,1.25,0);
  
  state.platforms[12].textureID = tileTextureID2;
  state.platforms[12].position = glm::vec3(1.5,0.25,0);
  
  state.platforms[13].textureID = tileTextureID2;
  state.platforms[13].position = glm::vec3(0.5,0.25,0);
  
  state.platforms[14].textureID = tileTextureID2;
  state.platforms[14].position = glm::vec3(-4.5,0.25,0);
  
  state.platforms[15].textureID = tileTextureID2;
  state.platforms[15].position = glm::vec3(-3.5,0.25,0);
  
  state.platforms[16].textureID = tileTextureID2;
  state.platforms[16].position = glm::vec3(-3.5,0.25,0);
  
  state.platforms[17].textureID = tileTextureID2;
  state.platforms[17].position = glm::vec3(-2.5,0.25,0);
  
  viewMatrix = glm::mat4(1.0f);
  modelMatrix = glm::mat4(1.0f);
  projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
  
  program.SetProjectionMatrix(projectionMatrix);
  program.SetViewMatrix(viewMatrix);
  program.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
  
  glUseProgram(program.programID);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void ProcessInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
      case SDL_WINDOWEVENT_CLOSE:
        gameIsRunning = false;
        break;
    }
  }
  
//  state.player.acceleration.x = 0;
  
  const Uint8 *keys = SDL_GetKeyboardState(NULL);
  
  if (keys[SDL_SCANCODE_LEFT])
  {
    state.player.acceleration.x -= 0.02;
  }
  else if  (keys[SDL_SCANCODE_RIGHT])
  {
    state.player.acceleration.x += 0.02;
  }
  
}

void drawLetter(int index, float position) {
  float u = (float)(index % cols) / (float)cols;
  float v = (float)(index / cols) / (float)rows;
  
  float width = 1.0f / (float)cols;
  float height = 1.0f / (float)rows;
  
  float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
    u, v + height, u + width, v, u, v};
  
  float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
  
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.0 + position / 2,0.0,0.0));
  program.SetModelMatrix(modelMatrix);
  
  glBindTexture(GL_TEXTURE_2D, fontTextureID);
  
  glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
  glEnableVertexAttribArray(program.positionAttribute);
  
  glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
  glEnableVertexAttribArray(program.texCoordAttribute);
  
  glDrawArrays(GL_TRIANGLES, 0, 6);
  
  glDisableVertexAttribArray(program.positionAttribute);
  glDisableVertexAttribArray(program.texCoordAttribute);
  
}

void drawWon() {
  drawLetter(77,-3);
  drawLetter(73,-2);
  drawLetter(83,-1);
  drawLetter(83,0);
  drawLetter(73,1);
  drawLetter(79,2);
  drawLetter(78,3);
  
  drawLetter(32,4);
  drawLetter(32,5);
  
  drawLetter(83,6);
  drawLetter(85,7);
  drawLetter(67,8);
  drawLetter(67,9);
  drawLetter(69,10);
  drawLetter(83,11);
  drawLetter(83,12);
  drawLetter(70,13);
  drawLetter(85,14);
  drawLetter(76,15);
  
}

void drawLost() {
  drawLetter(77,-1);
  drawLetter(73,0);
  drawLetter(83,1);
  drawLetter(83,2);
  drawLetter(73,3);
  drawLetter(79,4);
  drawLetter(78,5);
  
  drawLetter(32,6);
  drawLetter(32,7);
  
  drawLetter(70,8);
  drawLetter(65,9);
  drawLetter(73,10);
  drawLetter(76,11);
  drawLetter(69,12);
  drawLetter(68,13);
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
    // Update. Notice it's FIXED_TIMESTEP. Not deltaTime
    state.player.Update(FIXED_TIMESTEP, state.platforms, PLATFORM_COUNT);
    
    deltaTime -= FIXED_TIMESTEP;
  }
  
  accumulator = deltaTime;
  
}


void Render() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  state.player.Render(&program);
  
  for (int i = 0; i < PLATFORM_COUNT; i++) {
    state.platforms[i].Render(&program);
  }
  
  if (state.player.isActive == false) {
    if (state.player.collidedType == LANDING) {
      drawWon();
    }
    else {
      drawLost();
    }
  }
  
  SDL_GL_SwapWindow(displayWindow);
}

void Shutdown() {
  SDL_Quit();
}

int main(int argc, char* argv[]) {
  Initialize();
  
  while (gameIsRunning) {
    ProcessInput();
    Update();
    Render();
  }
  
  Shutdown();
  return 0;
}
