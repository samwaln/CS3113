//
//  Level1.cpp
//  SDLProject
//
//  Created by Samantha Waln on 10/30/19.
//  Copyright © 2019 ctg. All rights reserved.
//

#include "Level1.h"
#define LEVEL1_WIDTH 20
#define LEVEL1_HEIGHT 8
unsigned int level1_data[] =
{
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 2, 1, 0, 0, 3,
	3, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 2, 2, 0, 2, 2, 1, 1, 3,
	3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 3
};

void Level1::Initialize() {
	GLuint mapTextureID = Util::LoadTexture("tileset.png");
	state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);
	state.player.entityType = PLAYER;
	state.player.isStatic = false;
    state.player.lives = 3;
	state.player.width = 0.9f;
	state.player.position = glm::vec3(2, 0, 0);
	state.player.acceleration = glm::vec3(0, -9.81f, 0);
	state.player.textureID = Util::LoadTexture("me.png");
	state.nextLevel = -1;

	state.enemies[0].entityType = ENEMY;
	state.enemies[0].width = 0.9;
	state.enemies[0].textureID = Util::LoadTexture("evil.png");
	state.enemies[0].isStatic = false; //it moves!!
	state.enemies[0].acceleration = glm::vec3(0, -6.4f, 0);
	state.enemies[0].position = glm::vec3(8.0f, -2.25f, 0.0f);
	state.enemies[0].aiType = WALKER;
	state.enemies[0].aiState = IDLE;
}
void Level1::Update(float deltaTime) {
	state.player.Update(deltaTime, state.enemies, ENEMY_COUNT, state.map);

	for (int i = 0; i < ENEMY_COUNT; i++) {
		//update all the AIs!
		state.enemies[i].Update(deltaTime, &state.player, 1, state.map);
	}



	if (state.player.position.x > 18) {
		state.nextLevel = 1;
		state.player.position.y = 20;
	}
}
void Level1::Render(ShaderProgram* program) {
	state.map->Render(program);
	state.player.Render(program);
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		state.enemies[i].Render(program);
	}
    GLuint fontTextureID = Util::LoadTexture("font.png");
	if (state.player.lives == 0) {
		glm::vec3 loc1 = state.player.position;
		glm::vec3 loc2 = state.player.position;
		//needs more work, the game over screen just follows the player
		loc1.x -= 1;
		loc1.y += 2;
		loc2.x -= 1;
		loc2.y += 1;
		Util::DrawText(program, fontTextureID, "Game", 1, -0.2, loc1);
		Util::DrawText(program, fontTextureID, "Over!", 1, -0.2, loc2);
    }
    glm::vec3 loc = glm::vec3(0,0,0);
    if (state.player.position.x > 5) {
        loc = glm::vec3(state.player.position.x-4.75, -0.2, 0);
    } else {
        loc = glm::vec3(0.25, -0.2, 0);
    }
    Util::DrawText(program, fontTextureID, std::to_string(state.player.lives), 1, -0.2, loc);
}
