#include "Entity.h"

Entity::Entity()
{
    entityType = PLATFORM;
    isStatic = true;
    isActive = true;
    position = glm::vec3(0);
    width = 1;
    height = 1;
    playerWon = -1;
}

bool Entity::CheckCollision(Entity* other)
{
    
    if (isActive == false || other->isActive == false)
    {
        return false;
    }
    
    float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);

    if (xdist < 0 && ydist < 0)
    {
        return true;
    }
    
    return false;
}

void Entity::CheckCollisionsY(Entity *objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity* object = objects + i;
        
        if (CheckCollision(object))
        {
            if (object->entityType == ENEMY && entityType == PLAYER)
            {
                if (object->velocity.y < 0 || velocity.y > 0) {
                    playerWon = 0;
                }
                else if (velocity.y < 0){
                    Mix_PlayChannel(-1, jump, 0);
                    object->isActive = false;
                }
            }
            float ydist = fabs(position.y - object->position.y);
            float penetrationY = fabs(ydist - (height / 2) - (object->height / 2));
            if (velocity.y > 0) {
                position.y -= penetrationY;
                velocity.y = 0;
                collidedTop = true;
            }
            else if (velocity.y < 0) {
//                if (entityType == PLAYER && object->entityType == ENEMY) {
//                    object->isActive = false;
//                    return;
//                }
                position.y += penetrationY;
                velocity.y = 0;
                collidedBottom = true;
            }
        }
    }
}

void Entity::CheckCollisionsX(Entity *objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity* object = objects + i;
        
        if (CheckCollision(object))
        {
            float xdist = fabs(position.x - object->position.x);
            float penetrationX = fabs(xdist - (width / 2) - (object->width / 2));
            if (velocity.x > 0) {
                position.x -= penetrationX;
                velocity.x = 0;
                collidedRight = true;
            }
            else if (velocity.x < 0) {
                position.x += penetrationX;
                velocity.x = 0;
                collidedLeft = true;
            }

            if (object->entityType == ENEMY && entityType == PLAYER)
            {
                if (object->isActive)
                    playerWon = 0;
            }
        }
    }
}


void Entity::Jump()
{
    if (collidedBottom)
    {
        if (entityType == PLAYER)
            velocity.y = 8.0f;
        else
            velocity.y = 4.0f;
    }
}

void Entity::AIJumper(Entity player)
{
    switch(aiState) {
        case IDLE:
            break;
        case ACTIVE:
            Jump();
    }
}

void Entity::AIWalker(Entity player)
{
    switch(aiState) {
        case IDLE:
            if (player.playerWon == -1) {
                if (glm::distance(position, player.position) < 3.0f) {
                    aiState = ACTIVE;
                }
            }
            break;
        case ACTIVE:
            if (position.x > player.position.x)
                velocity.x = -0.5f;
            else if (position.x < player.position.x - 1)
                velocity.x = 0.5f;
            break;
    }
}

void Entity::AIPatroller(Entity player)
{
    switch(aiState) {
        case IDLE:
            break;
        case ACTIVE:
            if (velocity.x > 0 && position.x > 4.0f)
            {
                velocity.x = -1.0f;
            }
            else if (velocity.x < 0 && position.x < 2.0f)
            {
                velocity.x = 1.0f;
            }
            break;
    }
}

void Entity::AI(Entity player)
{
    switch(aiType) {
        case WALKER:
            AIWalker(player);
            break;
        case JUMPER:
            AIJumper(player);
            break;
        case PATROLLER:
            AIPatroller(player);
            break;
    }
}

void Entity::Update(float deltaTime, Entity player, Entity* objects, int objectCount, Entity* enemies, int enemyCount)
{
    collidedTop = false;
    collidedBottom = false;
    collidedLeft = false;
    collidedRight = false;
    
    velocity += acceleration * deltaTime;
    
    position.y += velocity.y * deltaTime;        // Move on Y
    CheckCollisionsY(objects, objectCount);    // Fix if needed
    
    if (entityType == PLAYER)
    {
        CheckCollisionsY(enemies, enemyCount);
        CheckCollisionsX(enemies, enemyCount);
    }
    
    position.x += velocity.x * deltaTime;        // Move on X
    CheckCollisionsX(objects, objectCount);    // Fix if needed

    
    if (entityType == ENEMY)
    {
        AI(player);
    }
}

void Entity::DrawSprite(ShaderProgram *program, int spriteNum) {
    int cols = 4;
    int rows = 4;
    
    float u = (float)(spriteNum % cols) / (float)cols;
    float v = (float)(spriteNum / cols) / (float)rows;
    
    float width = 1.0f / (float)cols;
    float height = 1.0f / (float)rows;
    
    float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
        u, v + height, u + width, v, u, v};
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    program->SetModelMatrix(modelMatrix);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

void Entity::Render(ShaderProgram *program, int spriteNum) {
    if (spriteNum == -1) {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        program->SetModelMatrix(modelMatrix);
        
        float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
        float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
        glEnableVertexAttribArray(program->positionAttribute);
        
        glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
        glEnableVertexAttribArray(program->texCoordAttribute);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glDisableVertexAttribArray(program->positionAttribute);
        glDisableVertexAttribArray(program->texCoordAttribute);
    }
    else {
        DrawSprite(program, spriteNum);
    }
}

