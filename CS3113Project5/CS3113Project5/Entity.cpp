#include "Entity.h"

Entity::Entity()
{
	entityType = PLATFORM;
	isStatic = true;
	isActive = true;
	position = glm::vec3(0);
	speed = 0;
	width = 1;
	height = 1;
    lives = 1;
    cols = 1;
    rows = 1;
    animFrames = 1;
    animIndex = 0;
    animTime = 0.0f;
}


bool Entity::CheckCollision(Entity other)
{
	if (isStatic == true) return false;
	if (isActive == false || other.isActive == false) return false;

	float xdist = fabs(position.x - other.position.x) - ((width + other.width) / 2.0f);
	float ydist = fabs(position.y - other.position.y) - ((height + other.height) / 2.0f);

	if (xdist < 0 && ydist < 0)
	{
		lastCollision = other.entityType;
		std::cout << lastCollision;
		return true;
	}

	return false;
}




void Entity::CheckCollisionsY(Entity* objects, int objectCount)
{
	for (int i = 0; i < objectCount; i++)
	{
		Entity object = objects[i];

		if (CheckCollision(object))
		{
			float ydist = fabs(position.y - object.position.y);
			float penetrationY = fabs(ydist - (height / 2) - (object.height / 2));
			if (velocity.y > 0) {
				position.y -= penetrationY;
				velocity.y = 0;
				collidedTop = true;
			}
			else if (velocity.y < 0) {
				position.y += penetrationY;
				velocity.y = 0;
				collidedBottom = true;
			}
		}
	}
}

void Entity::CheckCollisionsX(Entity* objects, int objectCount)
{
	for (int i = 0; i < objectCount; i++)
	{
		Entity object = objects[i];

		if (CheckCollision(object))
		{
			float xdist = fabs(position.x - object.position.x);
			float penetrationX = fabs(xdist - (width / 2) - (object.width / 2));
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
		}
	}
}

void Entity::CheckCollisionsY(Map* map)
{
	// Probes for tiles
	glm::vec3 top = glm::vec3(position.x, position.y + (height / 2), position.z);
	glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
	glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);

	glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
	glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
	glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);

	float penetration_x = 0;
	float penetration_y = 0;
	if (map->IsSolid(top, &penetration_x, &penetration_y) && velocity.y > 0) {
		position.y -= penetration_y;
		velocity.y = 0;
		collidedTop = true;
	}
	else if (map->IsSolid(top_left, &penetration_x, &penetration_y) && velocity.y > 0) {
		position.y -= penetration_y;
		velocity.y = 0;
		collidedTop = true;
	}
	else if (map->IsSolid(top_right, &penetration_x, &penetration_y) && velocity.y > 0) {
		position.y -= penetration_y;
		velocity.y = 0;
		collidedTop = true;
	}
	if (map->IsSolid(bottom, &penetration_x, &penetration_y) && velocity.y < 0) {
		position.y += penetration_y;
		velocity.y = 0;
		collidedBottom = true;
	}
	else if (map->IsSolid(bottom_left, &penetration_x, &penetration_y) && velocity.y < 0) {
		position.y += penetration_y;
		velocity.y = 0;
		collidedBottom = true;
	}
	else if (map->IsSolid(bottom_right, &penetration_x, &penetration_y) && velocity.y < 0) {
		position.y += penetration_y;
		velocity.y = 0;
		collidedBottom = true;
	}
}

void Entity::CheckCollisionsX(Map* map)
{
	// Probes for tiles
	glm::vec3 left = glm::vec3(position.x - (width / 2), position.y, position.z);
	glm::vec3 right = glm::vec3(position.x + (width / 2), position.y, position.z);

	float penetration_x = 0;
	float penetration_y = 0;
	if (map->IsSolid(left, &penetration_x, &penetration_y) && velocity.x < 0) {
		position.x += penetration_x;
		velocity.x = 0;
		collidedLeft = true;
	}

	if (map->IsSolid(right, &penetration_x, &penetration_y) && velocity.x > 0) {
		position.x -= penetration_x;
		velocity.x = 0;
		collidedRight = true;
	}
}

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram *program, int index)
{
    float width = 1.0f / (float)cols;
    float height = 1.0 / (float)rows;
    
    std::vector<float> vertices;
    std::vector<float> texCoords;
        
        float u = (float)(index % cols) / (float)cols;
        float v = (float)(index / cols) / (float)rows;
        
        texCoords.insert(texCoords.end(), {
            u, v,
            u, v + height,
            u + width, v,
            u + width, v + height,
            u + width, v,
            u, v + height,
        });
        vertices.insert(vertices.end(), {
            -0.5f, 0.5f,
            -0.5f, -0.5f,
            0.5f, 0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, -0.5f,
        });
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    program->SetModelMatrix(modelMatrix);
    
    glUseProgram(program->programID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices.data());
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords.data());
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glBindTexture(GL_TEXTURE_2D,  textureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
    
}

void Entity::Jump()
{
	if (collidedBottom)
	{
		velocity.y = 5.0f;
	}
}

void Entity::AIWalker(Entity player) {
	switch (aiState) { //do something different depending on state!
	case IDLE:
		if (glm::distance(position, player.position) < 3.0f) {
			aiState = WALKING;
		}
		break;
	case WALKING:
		if (player.position.x > position.x) {
			velocity.x = 1.0f; //go right
		}
		if (player.position.x < position.x) {
			velocity.x = -1.0f; //go left	
		}
		break;
	}
}

void Entity::AI(Entity player) {
	switch (aiType) {
	case WALKER:
		//call an AI walker function
		AIWalker(player);
		break;
	}

}




void Entity::Update(float deltaTime, Entity* objects, int objectCount, Map* map)
{
	collidedTop = false;
	collidedBottom = false;
	collidedLeft = false;
	collidedRight = false;

	velocity += acceleration * deltaTime;

	position.y += velocity.y * deltaTime; // Move on Y
	CheckCollisionsY(map);
	CheckCollisionsY(objects, objectCount); // Fix if needed

	position.x += velocity.x * deltaTime; // Move on X
	CheckCollisionsX(map);
	CheckCollisionsX(objects, objectCount); // Fix if needed
    
    animTime += deltaTime;
    if (velocity.x > 0) {
        if (animTime >= 0.4) {
            animTime = 0.0f;
            animIndex++;
            if (animIndex >= animFrames/2 + 1) {
                animIndex = 0;
            }
        }
    }
    else if (velocity.x < 0) {
        if (animTime >= 0.4) {
            animTime = 0.0f;
            animIndex++;
            if (animIndex >= animFrames) {
                animIndex = animFrames/2 + 1;
            }
        }
    }
    
	if (entityType == ENEMY) {
		AI(*objects);
	}
	if (entityType == PLAYER) {
		//if you fall off, make it game over
		if (position.y < -8) {
            if (lives > 0) {
                lives-=1;
                position.x -= 1;
                position.y = 0;
            }
		}
		if (lastCollision == ENEMY && (collidedLeft == true || collidedRight == true)) {
            if (lives > 0)  {
                lives-=1;
                position.x -= 0.5;
            }
			velocity = glm::vec3(0, 0, 0);
			acceleration = glm::vec3(0, 0, 0);
		}
		else if (lastCollision == ENEMY && collidedBottom == true && collidedLeft == false && collidedRight == false) {
			objects[0].isActive = false;
			lastCollision = PLATFORM;
			Jump();
		}
	}
}



void Entity::Render(ShaderProgram* program) {
	if (isActive == false) {
		return;
	}

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	program->SetModelMatrix(modelMatrix);
    
    DrawSpriteFromTextureAtlas(program, animIndices.at(animIndex));

//    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
//    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
//
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
//    glEnableVertexAttribArray(program->positionAttribute);
//
//    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
//    glEnableVertexAttribArray(program->texCoordAttribute);
//
//    glDrawArrays(GL_TRIANGLES, 0, 6);
//
//    glDisableVertexAttribArray(program->positionAttribute);
//    glDisableVertexAttribArray(program->texCoordAttribute);
}
