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

void Entity::CheckSensors(Map* map)
{
	float penetration_x = 0;
	float penetration_y = 0;
	if (map->IsSolid(sensorLeft, &penetration_x, &penetration_y)) {
		sensorL = true;
	}
	if (map->IsSolid(sensorRight, &penetration_x, &penetration_y)) {
		sensorR = true;
	}
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
		return true;
	}

	return false;
}




void Entity::CheckCollisionsY(Entity* objects, int objectCount)
{
	for (int i = 0; i < objectCount; i++)
	{
		Entity object = objects[i];
        Entity *objectP = objects+i;

		if (CheckCollision(object))
		{
            if (entityType == PLAYER) {
                if (object.entityType == COIN) {
                    if (lives < 3) {
                        objectP->isActive = false;
                        lives++;
                    }
                    break;
                }
            }
			float ydist = fabs(position.y - object.position.y);
			float penetrationY = fabs(ydist - (height / 2) - (object.height / 2));
			if (velocity.y > 0 ) {
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
        Entity *objectP = objects+i;

		if (CheckCollision(object))
		{
            if (entityType == PLAYER) {
                if (object.entityType == COIN) {
                    if (lives < 3) {
                        objectP->isActive = false;
                        lives++;
                    }
                    break;
                }
            }
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
	else if (map->IsSolid(bottom_left, &penetration_x, &penetration_y)) {
		if (velocity.x < 0) {
			position.x += penetration_x;
			velocity.x = 0;
			collidedBottom = true;
		}
	}
	else if (map->IsSolid(bottom_right, &penetration_x, &penetration_y)) {
		if (velocity.x > 0) {
			position.x -= penetration_x;
			velocity.x = 0;
			collidedBottom = true;
		}
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
		velocity.x = 0;
		position.x += penetration_x;
		collidedLeft = true;
	}

	if (map->IsSolid(right, &penetration_x, &penetration_y) && velocity.x > 0) {
		velocity.x = 0;
		position.x -= penetration_x;
		collidedRight = true;
	}
}

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram* program, int index)
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
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8,0.8,1));
	program->SetModelMatrix(modelMatrix);

	glUseProgram(program->programID);

	glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices.data());
	glEnableVertexAttribArray(program->positionAttribute);

	glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords.data());
	glEnableVertexAttribArray(program->texCoordAttribute);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(program->positionAttribute);
	glDisableVertexAttribArray(program->texCoordAttribute);

}

void Entity::DrawLives(ShaderProgram* program, int lifeNumber)
{
    GLuint lifeTextureID = Util::LoadTexture("heart_1.png");
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    
    glm::vec3 loc = glm::vec3(0,0,0);
    if (position.x > 23) {
        if (position.y < -26.75) {
            loc = glm::vec3(27.75, -23.2, 0);
        }
        else if (position.y < -3.75) {
            loc = glm::vec3(27.75, position.y + 3.55, 0);
        }
        else {
            loc = glm::vec3(27.75, -0.2, 0);
        }
    }
    else if (position.x > 5) {
        if (position.y < -26.75) {
            loc = glm::vec3(position.x + 4.75, -23.2, 0);
        }
        else if (position.y < -3.75) {
            loc = glm::vec3(position.x + 4.75, position.y + 3.55, 0);
        }
        else {
            loc = glm::vec3(position.x + 4.75, -0.2, 0);
        }
    } else {
        if (position.y < -26.75) {
            loc = glm::vec3(9.75, -23.2, 0);
        }
        else if (position.y < -3.75) {
            loc = glm::vec3(9.75, position.y + 3.55, 0);
        }
        else {
            loc = glm::vec3(9.75, -0.2, 0);
        }
    }
    
    modelMatrix = glm::translate(modelMatrix, loc);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5,0.5,0.5));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-lifeNumber,0,0));
    program->SetModelMatrix(modelMatrix);
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glBindTexture(GL_TEXTURE_2D, lifeTextureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
    
    if (lives == 3) {
        GLuint fontTextureID = Util::LoadTexture("font.png");
        Util::DrawText(program, fontTextureID, "MAX", 0.3, -0.1, glm::vec3(loc.x-0.4,loc.y-0.3,0));
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
                velocity.x = 1.5f; //go right
            }
            if (player.position.x < position.x) {
                velocity.x = -1.5f; //go left
            }
            break;
        case PATROLING:
            break;
	}
}

//patrol just walks back and force fom walls and pits
void Entity::AIPatrol(Entity player) {
	switch (aiState) { //do something different depending on state!
        case IDLE:
            break;
        case WALKING:
            break;
        case PATROLING:
            if (velocity.x == 0) {
                velocity.x = 1.0f;
            }
            if (collidedRight || !sensorR) {
                velocity.x = -1.0f;
            }
            if (collidedLeft || !sensorL) {
                velocity.x = 1.0f;
            }
	}
}

void Entity::AI(Entity player) {
	switch (aiType) {
	case WALKER:
		//call an AI walker function
		AIWalker(player);
		break;
	case PATROL:
		AIPatrol(player);
		break;
    }
}



void Entity::Update(float deltaTime, Entity* objects, int objectCount, Map* map)
{
	collidedTop = false;
	collidedBottom = false;
	collidedLeft = false;
	collidedRight = false;
	sensorR = false;
	sensorL = false;

	velocity += acceleration * deltaTime;

	position.y += velocity.y * deltaTime; // Move on Y
	CheckCollisionsY(map);
	CheckCollisionsY(objects, objectCount); // Fix if needed
	position.x += velocity.x * deltaTime; // Move on X
	CheckCollisionsX(map);
	CheckCollisionsX(objects, objectCount); // Fix if needed

	animTime += deltaTime;
    if (velocity.x > 0) {
        if (animIndex >= 3 * animFrames / 4 || animIndex < animFrames / 2) {
            animIndex = animFrames / 2;
        }
        if (animTime >= 0.15) {
            animTime = 0.0f;
            animIndex++;
            if (animIndex >= 3 * animFrames / 4) {
                animIndex = animFrames / 2;
            }
        }
    }
    else if (velocity.x < 0) {
        if (animIndex < 3 * animFrames / 4) {
            animIndex = 3 * animFrames / 4;
        }
        if (animTime >= 0.15) {
            animTime = 0.0f;
            animIndex++;
            if (animIndex >= animFrames) {
                animIndex = 3 * animFrames / 4;
            }
        }
    }
	else if (velocity.y > 0) {
        if (animIndex >= animFrames / 4) {
            animIndex = 0;
        }
		if (animTime >= 0.15) {
			animTime = 0.0f;
			animIndex++;
			if (animIndex >= animFrames / 4) {
				animIndex = 0;
			}
		}
	}
	else if (velocity.y < 0) {
        if (animIndex < animFrames / 4 || animIndex >= animFrames / 2) {
            animIndex = animFrames / 4;
        }
		if (animTime >= 0.15) {
			animTime = 0.0f;
			animIndex++;
			if (animIndex >= animFrames / 2) {
				animIndex = animFrames / 4;
			}
		}
	}
	
	if (entityType == ENEMY) {

		sensorRight = glm::vec3(position.x + 0.3f, position.y - 0.7f, 0);
		sensorLeft = glm::vec3(position.x - 0.3f, position.y - 0.7f, 0);
		CheckSensors(map);
		AI(*objects);

		if (lastCollision == PLAYER && (collidedLeft == true || collidedRight == true || collidedBottom == true)) {
			if (objects->lives > 0) {
				objects->lives -= 1;
				objects->position.y = 2;
                objects->position.x -= 1;
				lastCollision = PLATFORM;
			}
		}
	}
	if (entityType == PLAYER) {
		if (lastCollision == ENEMY && (collidedLeft == true || collidedRight == true)) {
            if (lives > 0)  {
                lives-=1;
				position.y = 2;
                position.x -= 1;
				lastCollision = PLATFORM;
            }
		}
		if (lives == 0) {
			velocity = glm::vec3(0, 0, 0);
			acceleration = glm::vec3(0, 0, 0);
            position.y = 100.0;
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
    if (entityType == PLAYER) {
        for (int i = 0; i < lives; i++) {
            DrawLives(program, i);
        }
    }
}
