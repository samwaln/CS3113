//
//  Level3.cpp
//  SDLProject
//
//  Created by Samantha Waln on 10/30/19.
//  Copyright © 2019 ctg. All rights reserved.
//

#include "Level3.h"
#define LEVEL3_WIDTH 23
#define LEVEL3_HEIGHT 8
unsigned int level3_data[] =
{
	6, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 6,
	6, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 6,
	6, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 62, 6,
	6, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 17, 6,
	6, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 24, 25, 6,
	6, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 50, 12, 12, 12, 12, 12, 12, 31, 32, 33, 6,
	6, 0 , 1 , 1 , 1 , 2 , 12, 34, 41, 34, 12, 0 , 1 , 1 , 2 , 12, 0 , 1 , 1 , 1 , 1 , 2 , 6,
	6, 7 , 8 , 8 , 8 , 9 , 12, 12, 12, 12, 12, 7 , 8 , 8 , 9 , 12, 7 , 8 , 8 , 8 , 8 , 9 , 6
};

void Level3::Initialize(int lives) {
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 7, 11);
	state.player.entityType = PLAYER;
	state.player.isStatic = false;
	state.player.lives = 3;
	state.player.width = 0.9f;
	state.player.position = glm::vec3(2, -1, 0);
	state.player.acceleration = glm::vec3(0, -9.81f, 0);
	state.player.textureID = Util::LoadTexture("me.png");
	state.nextLevel = -1;

	state.enemies[0].entityType = ENEMY;
	state.enemies[0].width = 0.9;
	state.enemies[0].textureID = Util::LoadTexture("evil.png");
	state.enemies[0].isStatic = false; //it moves!!
	state.enemies[0].acceleration = glm::vec3(0, -6.4f, 0);
	state.enemies[0].position = glm::vec3(8.0f, -3.25f, 0.0f);
	state.enemies[0].aiType = JUMPER;
	state.enemies[0].aiState = PATROLING;

	state.enemies[1].entityType = ENEMY;
	state.enemies[1].width = 0.9;
	state.enemies[1].textureID = Util::LoadTexture("evil.png");
	state.enemies[1].isStatic = false; //it moves!!
	state.enemies[1].acceleration = glm::vec3(0, -6.4f, 0);
	state.enemies[1].position = glm::vec3(16.0f, -2.25f, 0.0f);
	state.enemies[1].aiType = JUMPER;
	state.enemies[1].aiState = PATROLING;
}
void Level3::Update(float deltaTime) {
	state.player.Update(deltaTime, state.enemies, ENEMY_COUNT, state.map);

	for (int i = 0; i < ENEMY_COUNT; i++) {
		//update all the AIs!
		state.enemies[i].Update(deltaTime, &state.player, 1, state.map);
	}


}
void Level3::Render(ShaderProgram *program) {
	state.map->Render(program);
	state.player.Render(program);
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		state.enemies[i].Render(program);
	}
	GLuint fontTextureID = Util::LoadTexture("font.png");
	if (state.player.lives == 0) {
		glm::vec3 loc1 = glm::vec3(0, 0, 0);
		glm::vec3 loc2 = glm::vec3(0, 0, 0);
		if (state.player.position.x > 5) {
			loc1 = glm::vec3(state.player.position.x - 1.5, -2.2, 0);
			loc2 = glm::vec3(state.player.position.x - 1.5, -3.2, 0);
		}
		else {
			loc1 = glm::vec3(3.50, -2.2, 0);
			loc2 = glm::vec3(3.50, -3.2, 0);
		}
		Util::DrawText(program, fontTextureID, "Game", 1, -0.2, loc1);
		Util::DrawText(program, fontTextureID, "Over!", 1, -0.2, loc2);
		//glm::vec3 loc1 = state.player.position;
		//glm::vec3 loc2 = state.player.position;
		////needs more work, the game over screen just follows the player
		//loc1.x -= 1;
		//loc1.y += 2;
		//loc2.x -= 1;
		//loc2.y += 1;
		//Util::DrawText(program, fontTextureID, "Game", 1, -0.2, loc1);
		//Util::DrawText(program, fontTextureID, "Over!", 1, -0.2, loc2);
	}
	glm::vec3 loc = glm::vec3(0, 0, 0);

	if (state.player.position.x >= 21 || state.nextLevel == -2) {
		glm::vec3 loc1 = glm::vec3(0, 0, 0);
		glm::vec3 loc2 = glm::vec3(0, 0, 0);
		if (state.player.position.x > 5) {
			loc1 = glm::vec3(state.player.position.x - 1.5, -2.2, 0);
			loc2 = glm::vec3(state.player.position.x - 1.5, -3.2, 0);
		}
		else {
			loc1 = glm::vec3(3.50, -2.2, 0);
			loc2 = glm::vec3(3.50, -3.2, 0);
		}
		Util::DrawText(program, fontTextureID, "You", 1, -0.2, loc1);
		Util::DrawText(program, fontTextureID, "Win!", 1, -0.2, loc2);
		state.nextLevel = -2;
	}

	if (state.player.position.x > 5) {
		loc = glm::vec3(state.player.position.x - 4.75, -0.2, 0);
	}
	else {
		loc = glm::vec3(0.25, -0.2, 0);
	}
	Util::DrawText(program, fontTextureID, std::to_string(state.player.lives), 1, -0.2, loc);
}

