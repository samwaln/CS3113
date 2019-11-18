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
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12
};

void Menu::Initialize(int lives) {
    GLuint mapTextureID = Util::LoadTexture("font.png");
    state.map = new Map(MENU_WIDTH, MENU_HEIGHT, menu_data, mapTextureID, 0.83f, 16, 16);
    state.player.position = glm::vec3(5, 5, 0);
	state.player.lives = lives;
    state.nextLevel = -1;
}
void Menu::Update(float deltaTime) {
    state.player.Update(deltaTime, NULL, 0, state.map);
	state.player.position = glm::vec3(5, 5, 0);
}
void Menu::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player.Render(program);
    GLuint fontTextureID = Util::LoadTexture("font.png");
    glm::vec3 loc1 = glm::vec3(3.5,-3,0);
    glm::vec3 loc2 = glm::vec3(1.2,-3.75,0);
    Util::DrawText(program, fontTextureID, "WELCOME", 1, -0.45, loc1);
    Util::DrawText(program, fontTextureID, "Press Enter To Start", 0.5, -0.1, loc2);
}
