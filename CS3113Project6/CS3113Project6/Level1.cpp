//
//  Level1.cpp
//  SDLProject
//
//  Created by Samantha Waln on 10/30/19.
//  Copyright © 2019 ctg. All rights reserved.
//

#include "Level1.h"
#define LEVEL1_WIDTH 29
#define LEVEL1_HEIGHT 31
unsigned int level1_data[] =
{
    7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    7,7,1,7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,1,
    7,7,1,7,7,1,7,7,7,7,7,7,7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    7,7,1,7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,1,
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
    7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,1,7,7,7,1,7,7,7,1,1,1,1,1,
    7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,7,7,7,1,7,7,1,1,
    7,7,1,7,7,1,7,7,7,7,7,7,7,1,7,7,7,7,7,7,1,7,7,7,1,7,7,1,1,
    7,7,1,7,7,1,7,7,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,1,7,7,1,1,
    7,7,1,7,7,1,7,7,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,1,1,1,7,1,1,
    7,7,1,7,7,1,1,1,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,7,1,7,1,1,
    7,7,1,7,7,7,7,1,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,7,1,7,1,1,
    7,7,1,7,7,7,7,1,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,7,1,7,1,1,
    7,7,1,7,7,7,7,1,7,7,7,7,7,1,1,1,1,1,1,1,1,1,1,7,7,1,7,1,1,
    7,7,1,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,7,7,1,7,1,1,
    7,7,1,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,7,7,1,7,1,1,
    7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,7,7,1,1,1,1,
    7,7,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,7,7,7,7,7,7,
    7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
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
    state.player.cols  = 4;
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
	state.nextLevel = -1;
    
    state.coins[0].position = glm::vec3(8, -2.5, 0);
    state.coins[0].textureID = Util::LoadTexture("Vegies.png");
    state.coins[0].entityType = COIN;
    state.coins[0].animIndices.push_back(0);
    state.coins[0].animFrames = 1;
    state.coins[0].cols  = 16;
    state.coins[0].rows = 8;
    
    state.coins[1].position = glm::vec3(4, -4.5, 0);
    state.coins[1].textureID = Util::LoadTexture("Vegies.png");
    state.coins[1].entityType = COIN;
    state.coins[1].animIndices.push_back(1);
    state.coins[1].animFrames = 1;
    state.coins[1].cols  = 16;
    state.coins[1].rows = 8;
    
    state.chest.position = glm::vec3(0.75,-0.5,0);
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
        Util::DrawText(program, fontTextureID, "You", 1, -0.2, glm::vec3(4,-3,0));
        Util::DrawText(program, fontTextureID, "Won!", 1, -0.2, glm::vec3(4,-4,0));
    }
    glm::vec3 loc = glm::vec3(0,0,0);
    if (state.player.position.x > 5) {
        if (state.player.position.y > -3.75) {
            loc = glm::vec3(state.player.position.x - 4.75, state.player.position.y + 3.55, 0);
        }
        else {
            loc = glm::vec3(state.player.position.x - 4.75, -0.2, 0);
        }
    } else {
        if (state.player.position.y > -3.75) {
            loc = glm::vec3(0.25, state.player.position.y + 3.55, 0);
        }
        else {
            loc = glm::vec3(0.25, -0.2, 0);
        }
    }
//    Util::DrawText(program, fontTextureID, std::to_string(state.player.lives), 1, -0.2, loc);
}
