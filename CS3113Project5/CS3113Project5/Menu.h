//
//  Menu.hpp
//  CS3113Project5
//
//  Created by Samantha Waln on 11/8/19.
//  Copyright © 2019 ctg. All rights reserved.
//

#include "Scene.h"
class Menu : public Scene {
    
public:
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render(ShaderProgram *program) override;
};
