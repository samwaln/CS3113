#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>
#include "SDL_image.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

enum EntityType{PLAYER, TILE, LANDING};

class Entity {
public:
  
  enum EntityType entityType;
  bool isStatic;
  bool isActive;
  
  bool collidedTop;
  bool collidedBottom;
  bool collidedLeft;
  bool collidedRight;
  
  glm::vec3 position;
  glm::vec3 velocity;
  glm::vec3 acceleration;
  glm::vec3 movement;
  float speed;
  float width;
  float height;
  
  GLuint textureID;
  
  Entity();
  
  bool CheckCollision(Entity other);
  void CheckCollisionsX(Entity* objects, int objectCount);
  void CheckCollisionsY(Entity* objects, int objectCount);
  
  void Update(float deltaTime, Entity *objects, int objectCount);
  void Render(ShaderProgram *program);
};
