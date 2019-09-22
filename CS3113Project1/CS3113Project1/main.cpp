#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program1;
ShaderProgram program2;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

float player_x = 0.0f;
float lastTicks = 0.0f;
float rotate_z = 0.0f;
float rotate_square = 0.0f;
GLboolean move_right = true;
GLboolean swing_right = true;

GLuint playerTextureID1;
GLuint playerTextureID2;

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
  displayWindow = SDL_CreateWindow("Project 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
  SDL_GL_MakeCurrent(displayWindow, context);
  
#ifdef _WINDOWS
  glewInit();
#endif
  
  glViewport(0, 0, 640, 480);
  program1.Load("shaders/vertex.glsl", "shaders/fragment.glsl");
  program2.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
  playerTextureID1 = LoadTexture("/Users/samanthawaln/Documents/CS3113/CS3113Project1/CS3113Project1/littleman.png");
  playerTextureID2 = LoadTexture("/Users/samanthawaln/Documents/CS3113/CS3113Project1/CS3113Project1/pixilsun.png");
  
  viewMatrix = glm::mat4(1.0f);
  modelMatrix = glm::mat4(1.0f);
  projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
  
  program1.SetProjectionMatrix(projectionMatrix);
  program1.SetViewMatrix(viewMatrix);
  program1.SetColor(0.3f, 1.0f, 0.0f, 1.0f);
  
  program2.SetProjectionMatrix(projectionMatrix);
  program2.SetViewMatrix(viewMatrix);
  program2.SetColor(0.3f, 1.0f, 0.0f, 1.0f);
  
  glUseProgram(program1.programID);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void ProcessInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
      gameIsRunning = false;
    }
  }
}

void drawSquareShape() {
  glUseProgram(program1.programID);
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f, 0.8f, 1.0f));
  modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, -2.0f, 0.0f));
  modelMatrix = glm::rotate(modelMatrix,
                            glm::radians(rotate_square),
                            glm::vec3(0.0f, 0.5f, 0.5f));
  
  program1.SetModelMatrix(modelMatrix);

  float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };

  glVertexAttribPointer(program1.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
  glEnableVertexAttribArray(program1.positionAttribute);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  glDisableVertexAttribArray(program1.positionAttribute);

}

void drawMan() {
  glUseProgram(program2.programID);
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::scale(modelMatrix, glm::vec3(3.0f, 3.0f, 3.0f));
  modelMatrix = glm::translate(modelMatrix, glm::vec3(player_x, 0.0f, 0.0f));
  
  program2.SetModelMatrix(modelMatrix);
  
  float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
  float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
  
  glBindTexture(GL_TEXTURE_2D, playerTextureID1);
  
  glVertexAttribPointer(program2.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
  glEnableVertexAttribArray(program2.positionAttribute);
  
  glVertexAttribPointer(program2.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
  glEnableVertexAttribArray(program2.texCoordAttribute);
  
  glDrawArrays(GL_TRIANGLES, 0, 6);
  
  glDisableVertexAttribArray(program2.positionAttribute);
  glDisableVertexAttribArray(program2.texCoordAttribute);
  
}

void drawSun() {
  glUseProgram(program2.programID);
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::scale(modelMatrix, glm::vec3(3.0f, 3.0f, 3.0f));
  modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.0f, 1.0f, 0.0f));
  modelMatrix = glm::rotate(modelMatrix,
                            glm::radians(rotate_z),
                            glm::vec3(0.0f, 0.0f, 1.0f));
  
  program2.SetModelMatrix(modelMatrix);
  
  float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
  float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
  
  glBindTexture(GL_TEXTURE_2D, playerTextureID2);
  
  glVertexAttribPointer(program2.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
  glEnableVertexAttribArray(program2.positionAttribute);
  
  glVertexAttribPointer(program2.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
  glEnableVertexAttribArray(program2.texCoordAttribute);
  
  glDrawArrays(GL_TRIANGLES, 0, 6);
  
  glDisableVertexAttribArray(program2.positionAttribute);
  glDisableVertexAttribArray(program2.texCoordAttribute);
}

void Update() {
  float ticks = (float)SDL_GetTicks() / 1000.0f;
  float deltaTime = ticks - lastTicks;
  lastTicks = ticks;
  
  if (player_x >= 1.0) {
    move_right = false;
  }
  else if (player_x <= -1.0){
    move_right = true;
  }
  if (move_right) {
    player_x += 0.5f * deltaTime;
  }
  else {
    player_x -= 0.5f * deltaTime;
  }
  
  if (rotate_z >= 60.0) {
    swing_right = false;
  }
  else if (rotate_z <= -60.0){
    swing_right = true;
  }
  if (swing_right) {
    rotate_z += 45.0 * deltaTime;
  }
  else {
    rotate_z -= 45.0 * deltaTime;
  }
  
  rotate_square += 90.0 * deltaTime;
  
}

void Render() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  drawMan();
  
  drawSun();
  
  drawSquareShape();
  
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
