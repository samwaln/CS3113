//
//  Level2.hpp
//  SDLProject
//
//  Created by Samantha Waln on 10/30/19.
//  Copyright © 2019 ctg. All rights reserved.
//

#include "Scene.h"
class Level2 : public Scene {
    
public:
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render(ShaderProgram *program) override;
};
