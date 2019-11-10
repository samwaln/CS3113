#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#include "Map.h"

enum  EntityType { PLAYER, PLATFORM, COIN, ENEMY };
enum AIState { IDLE, WALKING, PATROLING, JUMPING }; //add AI states
enum AIType { WALKER, PATROL, JUMPER };


class Entity {
public:

	EntityType entityType;
	bool isStatic;
	bool isActive;
    int lives;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	AIState aiState; //to store state of enemy
	AIType aiType;
	EntityType lastCollision;

	void AI(Entity player); //basically Ai update

	void AIWalker(Entity player);

	float width;
	float height;

	float speed;

	GLuint textureID;

	Entity();

	bool CheckCollision(Entity other);

	void CheckCollisionsX(Entity* objects, int objectCount);
	void CheckCollisionsY(Entity* objects, int objectCount);

	void CheckCollisionsX(Map* map);
	void CheckCollisionsY(Map* map);

	void Update(float deltaTime, Entity* objects, int objectCount, Map* map);
	void Render(ShaderProgram* program);

	void Jump();

	bool collidedTop;
	bool collidedBottom;
	bool collidedLeft;
	bool collidedRight;

};
