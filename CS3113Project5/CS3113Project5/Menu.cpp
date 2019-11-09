//
//  Menu.cpp
//  CS3113Project5
//
//  Created by Samantha Waln on 11/8/19.
//  Copyright © 2019 ctg. All rights reserved.
//

#include "Menu.h"

#define MENU_WIDTH 14
#define MENU_HEIGHT 8
unsigned int menu_data[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 87, 69, 76, 67, 79, 77, 69, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 80, 82, 69, 83, 83, 0, 69, 78, 84, 69, 82, 0, 0,
    0, 84, 79, 0, 67, 79, 78, 84, 73, 78, 85, 69, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void Menu::Initialize() {
    GLuint mapTextureID = Util::LoadTexture("font.png");
    state.map = new Map(MENU_WIDTH, MENU_HEIGHT, menu_data, mapTextureID, 0.83f, 16, 16);
    state.player.entityType = PLAYER;
    state.player.isStatic = false;
    state.player.width = 1.0f;
    state.player.position = glm::vec3(5, 5, 0);
    state.player.acceleration = glm::vec3(0, 0, 0);
//    state.player.textureID = Util::LoadTexture("me.png");
    state.nextLevel = -1;
}
void Menu::Update(float deltaTime) {
    state.player.Update(deltaTime, NULL, 0, state.map);
}
void Menu::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player.Render(program);
}
