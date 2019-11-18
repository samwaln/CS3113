//
//  Level2.cpp
//  SDLProject
//
//  Created by Samantha Waln on 10/30/19.
//  Copyright © 2019 ctg. All rights reserved.
//

#include "Level2.h"
#define LEVEL2_WIDTH 14
#define LEVEL2_HEIGHT 8
unsigned int level2_data[] =
{
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 3, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1,
    3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
    3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

void Level2::Initialize() {
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, level2_data, mapTextureID, 1.0f, 4, 1);
    state.player.entityType = PLAYER;
    state.player.isStatic = false;
    state.player.lives = 3;
    state.player.width = 0.9f;
    state.player.position = glm::vec3(2, 0, 0);
    state.player.acceleration = glm::vec3(0, -9.81f, 0);
    state.player.textureID = Util::LoadTexture("stella_walk.png");
    state.player.cols  = 4;
    state.player.rows = 8;
    state.player.animIndices.push_back(16);
    state.player.animIndices.push_back(17);
    state.player.animIndices.push_back(18);
    state.player.animIndices.push_back(19);
    state.player.animIndices.push_back(20);
    state.player.animIndices.push_back(21);
    state.player.animIndices.push_back(22);
    state.player.animIndices.push_back(23);
    state.player.animFrames = 8;
    state.nextLevel = -1;
}
void Level2::Update(float deltaTime) {
    if (state.player.position.x > 15) {
        state.nextLevel = 3;
        state.player.position.y = 20;
    }
    state.player.Update(deltaTime, NULL, 0, state.map);
}
void Level2::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player.Render(program);
}
