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
#include "Util.h"

enum  EntityType { PLATFORM, PLAYER, COIN, ENEMY };
enum AIState { IDLE, WALKING, PATROLING };
enum AIType { WALKER, PATROL };

class Entity {
public:
    
	EntityType entityType;
	bool isStatic;
	bool isActive;
    int lives;
	glm::vec3 enemyVel;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	int cols;
	int rows;
	std::vector<int> animIndices;
	int animFrames;
	int animIndex;
	float animTime;



	AIState aiState; //to store state of enemy
	AIType aiType;
	EntityType lastCollision;

	void AI(Entity player); //basically Ai update

	void AIWalker(Entity player);
	void AIPatrol(Entity player);

	float width;
	float height;

	float speed;
	void DrawSpriteFromTextureAtlas(ShaderProgram* program, int index);
    void DrawLives(ShaderProgram* program, int lifeNumber);
	GLuint textureID;

	Entity();
	void CheckSensors(Map* map);

	bool CheckCollision(Entity other);

	void CheckCollisionsX(Entity* objects, int objectCount);
	void CheckCollisionsY(Entity* objects, int objectCount);

	void CheckCollisionsX(Map* map);
	void CheckCollisionsY(Map* map);

	void Update(float deltaTime, Entity* objects, int objectCount, Map* map);
	void Render(ShaderProgram* program);

	bool collidedTop;
	bool collidedBottom;
	bool collidedLeft;
	bool collidedRight;
	glm::vec3 sensorRight;
	glm::vec3 sensorLeft;
	bool sensorR;
	bool sensorL;
};
