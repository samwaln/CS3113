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

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

float lastTicks = 0.0f;
float paddle1_y = 0.0f;
float paddle2_y = 0.0f;
float ball_x = 0.0f;
float ball_y = 0.0f;
bool ballMoving = true;
int winner = 0;
glm::vec3 ballDir = glm::vec3(0.5f,0.2f,0.0f);

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
  displayWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
  SDL_GL_MakeCurrent(displayWindow, context);
  
#ifdef _WINDOWS
  glewInit();
#endif
  
  glViewport(0, 0, 640, 480);
  program.Load("shaders/vertex.glsl", "shaders/fragment.glsl");
  
  viewMatrix = glm::mat4(1.0f);
  modelMatrix = glm::mat4(1.0f);
  projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
  
  program.SetProjectionMatrix(projectionMatrix);
  program.SetViewMatrix(viewMatrix);
  program.SetColor(1.0f, 0.8f, 0.8f, 1.0f);
  
  glUseProgram(program.programID);
  
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
  
  // new game
  switch (event.key.keysym.sym) {
    case SDLK_SPACE:
      if (ballMoving == false) {
        ball_x = 0.0f;
        ball_y = 0.0f;
        ballDir = glm::vec3(0.5f,0.2f,1.0f);
        winner = 0;
        ballMoving = true;
      }
      break;
  }
  
  const Uint8 *keys = SDL_GetKeyboardState(NULL);
  
  if (keys[SDL_SCANCODE_W])
  {
    if (paddle1_y < 5.0)
      paddle1_y += 0.1f;
  }
  else if  (keys[SDL_SCANCODE_S])
  {
    if (paddle1_y > -5.0)
    paddle1_y -= 0.1f;
  }
  
  if (keys[SDL_SCANCODE_UP])
  {
    if (paddle2_y < 5.0)
      paddle2_y += 0.1f;
  }
  else if  (keys[SDL_SCANCODE_DOWN])
  {
    if (paddle2_y > -5.0)
      paddle2_y -= 0.1f;
  }
  
}

void drawPaddle1() {
  glUseProgram(program.programID);
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 1.0f));
  modelMatrix = glm::translate(modelMatrix, glm::vec3(-9.5f, paddle1_y, 0.0f));
  
  program.SetModelMatrix(modelMatrix);

  float vertices[]  = { -0.5, -2.5, 0.5, -2.5, 0.5, 2.5, -0.5, -2.5, 0.5, 2.5, -0.5, 2.5 };

  glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
  glEnableVertexAttribArray(program.positionAttribute);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  glDisableVertexAttribArray(program.positionAttribute);

}

void drawPaddle2() {
  glUseProgram(program.programID);
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 1.0f));
  modelMatrix = glm::translate(modelMatrix, glm::vec3(9.5f, paddle2_y, 0.0f));
  
  program.SetModelMatrix(modelMatrix);
  
  float vertices[]  = { -0.5, -2.5, 0.5, -2.5, 0.5, 2.5, -0.5, -2.5, 0.5, 2.5, -0.5, 2.5 };
  
  glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
  glEnableVertexAttribArray(program.positionAttribute);
  
  glDrawArrays(GL_TRIANGLES, 0, 6);
  
  glDisableVertexAttribArray(program.positionAttribute);
  
}

void drawBall() {
  program.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
  glUseProgram(program.programID);
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 1.0f));
  modelMatrix = glm::translate(modelMatrix, glm::vec3(ball_x, ball_y, 0.0f));
  
  program.SetModelMatrix(modelMatrix);
  
  float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
  
  glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
  glEnableVertexAttribArray(program.positionAttribute);
  
  glDrawArrays(GL_TRIANGLES, 0, 6);
  
  glDisableVertexAttribArray(program.positionAttribute);
  program.SetColor(1.0f, 0.8f, 0.8f, 1.0f);
}

void drawWinner(int player) {
  program.SetColor(1.0f, 1.0f, 0.0f, 1.0f);
  glUseProgram(program.programID);
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.3f, 1.0f));

  if (player == 1) {
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-9.3f, 11.7f, 0.0f));
  }
  else if (player == 2) {
    modelMatrix = glm::translate(modelMatrix, glm::vec3(9.3f, 11.7f, 0.0f));
  }
  
  program.SetModelMatrix(modelMatrix);

  float vertices[] = {-0.5, -0.5, -0.5, 0.5, 0.0, -0.5,
                      0.0, 0.5, -0.5, -0.5, 0.5, -0.5,
                      0.5, -0.5, 0.5, 0.5, 0.0, -0.5};

  glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
  glEnableVertexAttribArray(program.positionAttribute);

  glDrawArrays(GL_TRIANGLES, 0, 9);

  glDisableVertexAttribArray(program.positionAttribute);
  program.SetColor(1.0f, 0.8f, 0.8f, 1.0f);
}

int detectCollision() {
  // hits right or left edge of window (win)
  // paddle1 wins
  if (ball_x >= 9.5) {
    ball_x = 9.5;
    return 1;
  }
  // paddle2 wins
  if (ball_x <= -9.5) {
    ball_x = -9.5;
    return 2;
  }
  
  // hits paddle
  // left
  if (ball_x < -8.5 && ball_y < paddle1_y + 2.5 && ball_y > paddle1_y - 2.5) {
    ball_x = -8.5;
    ballDir = glm::vec3(-1 * ballDir.x, ballDir.y, 0.0);
  }
  // right
  if (ball_x > 8.5 && ball_y < paddle2_y + 2.5 && ball_y > paddle2_y - 2.5) {
    ball_x = 8.5;
    ballDir = glm::vec3(-1 * ballDir.x, ballDir.y, 0.0);
  }
  
  // hits top
  if (ball_y + 0.5 > 7.5) {
    ball_y = 7.0;
    ballDir = glm::vec3(ballDir.x, -1 * ballDir.y, 0.0);
  }
  //hits bottom
  if (ball_y -  0.5 < -7.5) {
    ball_y = -7.0;
    ballDir = glm::vec3(ballDir.x, -1 * ballDir.y, 0.0);
  }
  return -1;
}

void Update() {
  float ticks = (float)SDL_GetTicks() / 1000.0f;
  float deltaTime = ticks - lastTicks;
  lastTicks = ticks;
  int collision = detectCollision();
  if (ballMoving && collision == -1) {
    ball_x += (deltaTime * 30.0 * (ballDir.x)/ballDir.length());
    ball_y += (deltaTime * 30.0 * (ballDir.y)/ballDir.length());
  }
  else if (collision == 1) {
    ballMoving = false;
    winner = 1;
  }
  else if (collision == 2) {
    ballMoving = false;
    winner = 2;
  }
}

void Render() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  drawPaddle1();
  drawPaddle2();
  drawBall();
  if (winner > 0)
    drawWinner(winner);
  
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
