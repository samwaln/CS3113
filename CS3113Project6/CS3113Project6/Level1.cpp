//
//  Level1.cpp
//  SDLProject
//
//  Created by Samantha Waln on 10/30/19.
//  Copyright © 2019 ctg. All rights reserved.
//

#include "Level1.h"
#define LEVEL1_WIDTH 29
#define LEVEL1_HEIGHT 32
unsigned int level1_data[] =
{
	7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	7,7,1,7,7,1,7,7,7,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,1,1,
	7,7,1,7,7,1,7,7,7,7,7,7,7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	7,7,1,7,7,1,7,7,7,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,1,1,
	7,7,1,7,7,1,1,1,1,1,1,1,7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	7,7,1,7,7,7,7,7,7,7,7,7,7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	7,7,1,7,7,7,7,7,7,7,7,7,7,7,1,7,7,7,7,7,1,7,7,7,7,7,7,1,1,
	7,7,1,7,7,7,7,7,7,7,7,7,7,7,1,7,7,7,7,7,1,7,7,7,7,7,7,1,1,
	7,7,1,7,7,1,1,1,1,1,1,1,1,1,1,7,7,7,7,7,1,7,7,7,7,7,7,1,1,
	7,7,1,7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,7,7,1,1,1,1,1,1,
	7,7,1,7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,7,7,7,7,7,7,1,1,
	7,7,1,7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,7,7,7,7,7,7,1,1,
	7,7,1,7,7,1,1,1,1,1,1,1,1,1,1,1,1,7,7,7,1,7,7,7,7,7,7,1,1,
	7,7,1,7,7,1,7,7,7,7,7,7,7,7,7,7,1,7,7,7,1,7,7,7,7,7,7,1,1,
	7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,1,7,7,7,1,1,7,7,1,1,1,1,1,
	7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,7,7,7,1,7,7,1,1,
	7,7,1,7,7,1,7,7,7,7,7,7,7,1,7,7,7,7,7,7,1,7,7,7,1,7,7,1,1,
	7,7,1,7,7,1,7,7,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,1,7,7,1,1,
	7,7,1,7,7,1,7,7,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,1,1,1,7,1,1,
	7,7,1,7,7,1,1,1,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,7,1,7,1,1,
	7,7,1,7,7,7,7,1,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,7,1,7,1,1,
	7,7,1,7,7,7,7,1,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,7,1,7,1,1,
	7,7,1,7,1,1,1,1,7,7,7,7,1,1,1,1,1,1,1,1,1,1,1,7,7,1,7,1,1,
	7,7,1,7,7,7,7,1,7,7,7,7,7,1,7,7,7,7,7,7,7,7,1,7,7,1,7,1,1,
	7,7,1,7,7,7,7,1,7,7,7,7,7,1,7,7,7,7,7,7,7,7,1,7,7,1,7,1,1,
	7,7,1,7,7,7,7,7,7,7,7,7,7,1,7,7,7,7,7,7,7,7,1,7,7,1,1,1,1,
	7,7,1,7,7,7,7,1,7,7,7,7,7,1,7,7,7,7,7,7,7,7,1,7,7,7,7,7,7,
	7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,7,
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

void Level1::Initialize(int lives) {
	GLuint mapTextureID = Util::LoadTexture("brick_tiles_1.png");
	state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 6, 1);
	state.player.entityType = PLAYER;
	state.player.isStatic = false;
	state.player.lives = 3;
	state.player.width = 0.7f;
	state.player.height = 0.8f;
	state.player.position = glm::vec3(4, -2.5, 0);
	state.player.acceleration = glm::vec3(0, 0, 0);
	state.player.textureID = Util::LoadTexture("Guy.png");
	state.player.cols = 4;
	state.player.rows = 4;
	state.player.animIndices.push_back(0);
	state.player.animIndices.push_back(1);
	state.player.animIndices.push_back(2);
	state.player.animIndices.push_back(3);
	state.player.animIndices.push_back(4);
	state.player.animIndices.push_back(5);
	state.player.animIndices.push_back(6);
	state.player.animIndices.push_back(7);
	state.player.animIndices.push_back(8);
	state.player.animIndices.push_back(9);
	state.player.animIndices.push_back(10);
	state.player.animIndices.push_back(11);
	state.player.animIndices.push_back(12);
	state.player.animIndices.push_back(13);
	state.player.animIndices.push_back(14);
	state.player.animIndices.push_back(15);
	state.player.animFrames = 16;
	state.player.lives = 1;
	state.nextLevel = -1;

	state.coins[0].position = glm::vec3(6, -2, 0);
	state.coins[0].textureID = Util::LoadTexture("Vegies.png");
	state.coins[0].entityType = COIN;
	state.coins[0].animIndices.push_back(12);
	state.coins[0].animFrames = 1;
	state.coins[0].cols = 16;
	state.coins[0].rows = 8;

	state.coins[1].position = glm::vec3(4, -4, 0);
	state.coins[1].textureID = Util::LoadTexture("Vegies.png");
	state.coins[1].entityType = COIN;
	state.coins[1].animIndices.push_back(1);
	state.coins[1].animFrames = 1;
	state.coins[1].cols = 16;
	state.coins[1].rows = 8;

	state.coins[2].position = glm::vec3(18, -29.5, 0);
	state.coins[2].textureID = Util::LoadTexture("Vegies.png");
	state.coins[2].entityType = COIN;
	state.coins[2].animIndices.push_back(2);
	state.coins[2].animFrames = 1;
	state.coins[2].cols = 16;
	state.coins[2].rows = 8;

	state.coins[3].position = glm::vec3(6, -10, 0);
	state.coins[3].textureID = Util::LoadTexture("Vegies.png");
	state.coins[3].entityType = COIN;
	state.coins[3].animIndices.push_back(3);
	state.coins[3].animFrames = 1;
	state.coins[3].cols = 16;
	state.coins[3].rows = 8;

	state.coins[4].position = glm::vec3(25, -8, 0);
	state.coins[4].textureID = Util::LoadTexture("Vegies.png");
	state.coins[4].entityType = COIN;
	state.coins[4].animIndices.push_back(3);
	state.coins[4].animFrames = 1;
	state.coins[4].cols = 16;
	state.coins[4].rows = 8;

	state.coins[5].position = glm::vec3(4, -26.5, 0);
	state.coins[5].textureID = Util::LoadTexture("Vegies.png");
	state.coins[5].entityType = COIN;
	state.coins[5].animIndices.push_back(3);
	state.coins[5].animFrames = 1;
	state.coins[5].cols = 16;
	state.coins[5].rows = 8;

	state.enemies[0].position = glm::vec3(3, -4.5, 0);
	state.enemies[0].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[0].entityType = ENEMY;
	state.enemies[0].aiType = HORIZONTAL;
	state.enemies[0].aiState = PATROLING;
	state.enemies[0].animIndices.push_back(4);
	state.enemies[0].animFrames = 1;
	state.enemies[0].cols = 6;
	state.enemies[0].rows = 1;

	state.enemies[1].position = glm::vec3(10, -4, 0);
	state.enemies[1].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[1].entityType = ENEMY;
	state.enemies[1].aiType = JABBER;
	state.enemies[1].aiState = LUNGEDOWN;
	state.enemies[1].animIndices.push_back(0);
	state.enemies[1].animFrames = 1;
	state.enemies[1].cols = 6;
	state.enemies[1].rows = 1;


	state.enemies[2].position = glm::vec3(6, -21, 0);
	state.enemies[2].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[2].entityType = ENEMY;
	state.enemies[2].aiType = CIRCLER;
	state.enemies[2].aiState = START;
	state.enemies[2].animIndices.push_back(3);
	state.enemies[2].animFrames = 1;
	state.enemies[2].cols = 6;
	state.enemies[2].rows = 1;

	state.enemies[3].position = glm::vec3(8, -2, 0);
	state.enemies[3].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[3].entityType = ENEMY;
	state.enemies[3].aiType = JABBER;
	state.enemies[3].aiState = LUNGEDOWN;
	state.enemies[3].animIndices.push_back(4);
	state.enemies[3].animFrames = 1;
	state.enemies[3].cols = 6;
	state.enemies[3].rows = 1;

	state.enemies[4].position = glm::vec3(9, -14, 0);
	state.enemies[4].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[4].entityType = ENEMY;
	state.enemies[4].aiType = CIRCLER;
	state.enemies[4].aiState = START;
	state.enemies[4].animIndices.push_back(2);
	state.enemies[4].animFrames = 1;
	state.enemies[4].cols = 6;
	state.enemies[4].rows = 1;

	state.enemies[5].position = glm::vec3(9, -18, 0);
	state.enemies[5].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[5].entityType = ENEMY;
	state.enemies[5].aiType = CIRCLER;
	state.enemies[5].aiState = START;
	state.enemies[5].animIndices.push_back(4);
	state.enemies[5].animFrames = 1;
	state.enemies[5].cols = 6;
	state.enemies[5].rows = 1;

	state.enemies[6].position = glm::vec3(9, -21, 0);
	state.enemies[6].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[6].entityType = ENEMY;
	state.enemies[6].aiType = CIRCLER;
	state.enemies[6].aiState = START;
	state.enemies[6].animIndices.push_back(0);
	state.enemies[6].animFrames = 1;
	state.enemies[6].cols = 6;
	state.enemies[6].rows = 1;

	state.enemies[7].position = glm::vec3(19, -8, 0);
	state.enemies[7].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[7].entityType = ENEMY;
	state.enemies[7].aiType = CIRCLER;
	state.enemies[7].aiState = START;
	state.enemies[7].animIndices.push_back(3);
	state.enemies[7].animFrames = 1;
	state.enemies[7].cols = 6;
	state.enemies[7].rows = 1;

	state.enemies[8].position = glm::vec3(12, -10, 0);
	state.enemies[8].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[8].entityType = ENEMY;
	state.enemies[8].aiType = VERTICAL;
	state.enemies[8].aiState = PATROLING;
	state.enemies[8].animIndices.push_back(0);
	state.enemies[8].animFrames = 1;
	state.enemies[8].cols = 6;
	state.enemies[8].rows = 1;

	state.enemies[9].position = glm::vec3(10, -10, 0);
	state.enemies[9].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[9].entityType = ENEMY;
	state.enemies[9].aiType = VERTICAL;
	state.enemies[9].aiState = PATROLING;
	state.enemies[9].animIndices.push_back(3);
	state.enemies[9].animFrames = 1;
	state.enemies[9].cols = 6;
	state.enemies[9].rows = 1;

	state.enemies[10].position = glm::vec3(8, -10, 0);
	state.enemies[10].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[10].entityType = ENEMY;
	state.enemies[10].aiType = VERTICAL;
	state.enemies[10].aiState = PATROLING;
	state.enemies[10].animIndices.push_back(2);
	state.enemies[10].animFrames = 1;
	state.enemies[10].cols = 6;
	state.enemies[10].rows = 1;

	state.enemies[11].position = glm::vec3(23, -7, 0);
	state.enemies[11].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[11].entityType = ENEMY;
	state.enemies[11].aiType = VERTICAL;
	state.enemies[11].aiState = PATROLING;
	state.enemies[11].animIndices.push_back(4);
	state.enemies[11].animFrames = 1;
	state.enemies[11].cols = 6;
	state.enemies[11].rows = 1;

	state.enemies[12].position = glm::vec3(13, -14, 0);
	state.enemies[12].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[12].entityType = ENEMY;
	state.enemies[12].aiType = VERTICAL;
	state.enemies[12].aiState = PATROLING;
	state.enemies[12].animIndices.push_back(5);
	state.enemies[12].animFrames = 1;
	state.enemies[12].cols = 6;
	state.enemies[12].rows = 1;

	state.enemies[13].position = glm::vec3(25, -12, 0);
	state.enemies[13].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[13].entityType = ENEMY;
	state.enemies[13].aiType = CIRCLER;
	state.enemies[13].aiState = START;
	state.enemies[13].animIndices.push_back(2);
	state.enemies[13].animFrames = 1;
	state.enemies[13].cols = 6;
	state.enemies[13].rows = 1;


	state.enemies[14].position = glm::vec3(7, -29, 0);
	state.enemies[14].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[14].entityType = ENEMY;
	state.enemies[14].aiType = VERTICAL;
	state.enemies[14].aiState = PATROLING;
	state.enemies[14].animIndices.push_back(1);
	state.enemies[14].animFrames = 1;
	state.enemies[14].cols = 6;
	state.enemies[14].rows = 1;

	state.enemies[15].position = glm::vec3(9, -28, 0);
	state.enemies[15].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[15].entityType = ENEMY;
	state.enemies[15].aiType = VERTICAL;
	state.enemies[15].aiState = PATROLING;
	state.enemies[15].animIndices.push_back(0);
	state.enemies[15].animFrames = 1;
	state.enemies[15].cols = 6;
	state.enemies[15].rows = 1;

	state.enemies[16].position = glm::vec3(11, -29, 0);
	state.enemies[16].textureID = Util::LoadTexture("PirateCaptain.png");
	state.enemies[16].entityType = ENEMY;
	state.enemies[16].aiType = VERTICAL;
	state.enemies[16].aiState = PATROLING;
	state.enemies[16].animIndices.push_back(4);
	state.enemies[16].animFrames = 1;
	state.enemies[16].cols = 6;
	state.enemies[16].rows = 1;

	state.chest.position = glm::vec3(0.75, -0.5, 0);
	state.chest.textureID = Util::LoadTexture("chest.png");
	state.chest.entityType = CHEST;
	state.chest.animIndices.push_back(0);
	state.chest.animFrames = 1;
	state.chest.cols = 1;
	state.chest.rows = 1;
}


void Level1::Update(float deltaTime) {
	state.player.Update(deltaTime, state.coins, COIN_COUNT, state.map);
	state.player.Update(deltaTime, state.enemies, ENEMY_COUNT, state.map);


	for (int i = 0; i < ENEMY_COUNT; i++) {
		//update all the AIs!
		state.enemies[i].Update(deltaTime, &state.player, 1, state.map);
	}

	for (int i = 0; i < COIN_COUNT; i++) {
		state.coins[i].Update(deltaTime, &state.player, 1, state.map);
	}

}

void Level1::Render(ShaderProgram* program) {
	state.map->Render(program);
	state.chest.Render(program);
	state.player.Render(program);
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		state.enemies[i].Render(program);
	}
	for (int i = 0; i < COIN_COUNT; i++)
	{
		state.coins[i].Render(program);
	}
	GLuint fontTextureID = Util::LoadTexture("font.png");
	if (state.player.lives == 0) {
		state.player.isActive = false;
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
	}
	if (state.player.position.x < 1.5 && state.player.position.y > -1) {
        state.player.won = true;
		Util::DrawText(program, fontTextureID, "You", 1, -0.2, glm::vec3(4, -3, 0));
		Util::DrawText(program, fontTextureID, "Won!", 1, -0.2, glm::vec3(4, -4, 0));
	}
}
