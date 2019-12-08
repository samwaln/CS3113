//
//  Scene.hpp
//  SDLProject
//
//  Created by Samantha Waln on 10/30/19.
//  Copyright © 2019 ctg. All rights reserved.
//

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
#include "Util.h"
#include "Entity.h"
#include "Map.h"
#define ENEMY_COUNT 0
#define COIN_COUNT 2
struct GameState {
	Entity player;
	Map* map;
	int nextLevel;
	Entity enemies[ENEMY_COUNT];
    Entity coins[COIN_COUNT];
    Entity chest;
};
class Scene {
public:
	GameState state;
	virtual void Initialize(int lives) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(ShaderProgram* program) = 0;
};
