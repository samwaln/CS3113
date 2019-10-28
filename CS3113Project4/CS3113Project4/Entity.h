#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

enum  EntityType { PLAYER, PLATFORM, ENEMY };

enum AIState { IDLE, ACTIVE };

enum AIType { WALKER, JUMPER, PATROLLER };

class Entity {
public:

    EntityType entityType;
    AIState aiState;
    AIType aiType;
  
    bool isStatic;
    bool isActive;
    
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    
    float width;
    float height;
    
    float speed;
    
    int playerWon;
    
    GLuint textureID;
    
    Mix_Chunk* jump;
    
    Entity();
    
    bool CheckCollision(Entity* other);
    
    void CheckCollisionsX(Entity *objects, int objectCount);
    void CheckCollisionsY(Entity *objects, int objectCount);
    
    void AIWalker(Entity player);
    void AIJumper(Entity player);
    void AIPatroller(Entity player);
    void AI(Entity player);
    void Update(float deltaTime, Entity player, Entity* objects, int objectCount, Entity* enemies, int enemyCount);
    void DrawSprite(ShaderProgram *program, int spriteNum);
    void Render(ShaderProgram *program, int spriteNum);
    
    void Jump();
    
    bool collidedTop;
    bool collidedBottom;
    bool collidedLeft;
    bool collidedRight;
    
};



