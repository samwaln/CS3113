//
//  Level3.cpp
//  SDLProject
//
//  Created by Samantha Waln on 10/30/19.
//  Copyright © 2019 ctg. All rights reserved.
//

#include "Level3.h"
#define LEVEL3_WIDTH 14
#define LEVEL3_HEIGHT 8
unsigned int level3_data[] =
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

void Level3::Initialize() {
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 4, 1);
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
void Level3::Update(float deltaTime) {
    state.player.Update(deltaTime, NULL, 0, state.map);
}
void Level3::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player.Render(program);
    if (state.player.position.x > 15) {
        GLuint fontTextureID = Util::LoadTexture("font.png");
        if (state.player.lives == 0) {
            state.player.isActive = false;
            glm::vec3 loc1 = state.player.position;
            glm::vec3 loc2 = state.player.position;
            loc1.x -= 1;
            loc1.y += 2;
            loc2.x -= 1;
            loc2.y += 1;
            Util::DrawText(program, fontTextureID, "You", 1, -0.2, loc1);
            Util::DrawText(program, fontTextureID, "Won!", 1, -0.2, loc2);
        }
    }
}

